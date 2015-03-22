#include "CombatConstants.hpp"
#include "CombatManager.hpp"
#include "CombatTextKeys.hpp"
#include "CoordUtils.hpp"
#include "DamageText.hpp"
#include "DeathManagerFactory.hpp"
#include "DamageCalculatorFactory.hpp"
#include "ExperienceManager.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "HostilityManager.hpp"
#include "IHitTypeFactory.hpp"
#include "ToHitCalculatorFactory.hpp"
#include "CombatTargetNumberCalculatorFactory.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "RaceManager.hpp"
#include "SkillManager.hpp"
#include "SkillMarkerFactory.hpp"
#include "StatusEffectFactory.hpp"
#include "SpeedCalculatorFactory.hpp"
#include "TextKeys.hpp"
#include "TextMessages.hpp"
#include "RNG.hpp"
#include "WeaponManager.hpp"

using namespace std;

CombatManager::CombatManager()
{
}

bool CombatManager::operator==(const CombatManager& cm) const
{
  return true;
}

ActionCostValue CombatManager::attack(CreaturePtr creature, const Direction d)
{
  ActionCostValue action_cost_value = 0;
  
  Game& game = Game::instance();

  MapPtr map = game.get_current_map();
    
  Coordinate creature_location = map->get_location(creature->get_id());
  Coordinate new_coords = CoordUtils::get_new_coordinate(creature_location, d);
  TilePtr adjacent_tile = map->at(new_coords.first, new_coords.second);

  if (adjacent_tile)
  {
    // Do the necessary checks here to determine whether to attack...
    CreaturePtr adjacent_creature = adjacent_tile->get_creature();
    
    // Sanity check
    if (adjacent_creature)
    {
      action_cost_value = attack(creature, adjacent_creature);
    }
  }
  else
  {
    // Couldn't get the tile.  This could be because the creature is
    // stunned and picked a direction without a tile (e.g., north at
    // row 0)
    action_cost_value = 1;
  }
  
  return action_cost_value;
}

// Attempt to attack.
//
// An attack is successful if:
//
// The generated to-hit value is 100 (ignore Soak, 2x max damage, any resistance is min 100%)
// The generated to-hit value is >= 96 (ignore Soak, max damage, any resistance is min 100%)
// The generated to-hit value is >= the target number (regular damage)
ActionCostValue CombatManager::attack(CreaturePtr attacking_creature, CreaturePtr attacked_creature, const AttackType attack_type, const bool mark_skills, DamagePtr predefined_damage)
{
  ActionCostValue action_cost_value = 0;

  bool mark_for_weapon_and_combat_skills = false;
 
  ToHitCalculatorPtr th_calculator = ToHitCalculatorFactory::create_to_hit_calculator(attacking_creature, attack_type);
  CombatTargetNumberCalculatorPtr ctn_calculator = CombatTargetNumberCalculatorFactory::create_target_number_calculator(attack_type);
  ISpeedCalculatorPtr speed_calculator = SpeedCalculatorFactory::create_speed_calculator(attack_type);
  
  if (th_calculator && ctn_calculator)
  {
    action_cost_value = speed_calculator->calculate(attacking_creature);
    DamageCalculatorPtr damage_calculator = DamageCalculatorFactory::create_damage_calculator(attack_type);
    
    int d100_roll = RNG::range(1, 100);
    int to_hit_value = th_calculator->calculate(attacking_creature);
    int total_roll = d100_roll + to_hit_value;
    int target_number_value = ctn_calculator->calculate(attacking_creature, attacked_creature);

    Damage damage;

    if (predefined_damage)
    {
      damage = *predefined_damage;
    }
    else
    {
      damage = damage_calculator->calculate_base_damage_with_bonuses_or_penalties(attacking_creature);
    }
        
    // Automatic miss is checked first
    if (is_automatic_miss(d100_roll))
    {
      miss(attacking_creature, attacked_creature);
    }
    // Hit
    else if (is_hit(total_roll, target_number_value))
    {
      hit(attacking_creature, attacked_creature, d100_roll, damage, attack_type);
      mark_for_weapon_and_combat_skills = true;
    }
    // Close miss (flavour text only.)
    else if (is_close_miss(total_roll, target_number_value))
    {
      close_miss(attacking_creature, attacked_creature);
    }
    // Miss
    else if (is_miss(total_roll, target_number_value))
    {
      miss(attacking_creature, attacked_creature);
    }    
  }

  // If the attack was a PvM type attack, mark the weapon/spell-category and 
  // combat/magic skills of the attacking creature, and add the attacking 
  // creature as a threat to the attacked creature.
  if (attacking_creature)
  {
    if (mark_skills)
    {
      mark_appropriate_skills(attacking_creature, attack_type, mark_for_weapon_and_combat_skills);
    }

    HostilityManager hm;
    hm.set_hostility_to_creature(attacked_creature, attacking_creature->get_id());
  }

  send_combat_messages(attacking_creature);
  
  return action_cost_value;
}

bool CombatManager::hit(CreaturePtr attacking_creature, CreaturePtr attacked_creature, const int d100_roll, const Damage& damage_info, const AttackType attack_type)
{
  WeaponManager wm;
  if (wm.is_using_weapon(attacking_creature, attack_type))
  {
    attacking_creature->get_conducts_ref().break_conduct(ConductType::CONDUCT_TYPE_WEAPONLESS);
  }

  string attacked_creature_desc = get_appropriate_creature_description(attacking_creature, attacked_creature);
  DamageType damage_type = damage_info.get_damage_type();
  int effect_bonus = damage_info.get_effect_bonus();
  int base_damage = 0;
  float soak_multiplier = 1.0;
  
  string combat_message = CombatTextKeys::get_hit_message(attacking_creature->get_is_player(), attacked_creature->get_is_player(), damage_type, StringTable::get(attacking_creature->get_description_sid()), attacked_creature_desc);

  HitTypeEnum hit_type_enum = HitTypeEnumConverter::from_successful_to_hit_roll(d100_roll);
  IHitTypeCalculatorPtr hit_calculator = IHitTypeFactory::create_hit_type(hit_type_enum);
  string hit_specific_msg = hit_calculator->get_combat_message();
  bool piercing = damage_info.get_piercing();

  base_damage = hit_calculator->get_base_damage(damage_info);

  if (!hit_specific_msg.empty())
  {
    combat_message = combat_message + " " + hit_specific_msg;
  }

  // Deal damage.
  bool slays_race = does_attack_slay_creature_race(attacking_creature, attacked_creature, attack_type);
  DamageCalculatorPtr damage_calc = DamageCalculatorFactory::create_damage_calculator(attack_type);
  int damage_dealt = damage_calc->calculate(attacked_creature, slays_race, damage_info, base_damage, soak_multiplier);

  // Add the text so far.
  add_combat_message(attacking_creature, attacked_creature, combat_message);
  add_any_necessary_damage_messages(attacking_creature, attacked_creature, damage_dealt, piercing);

  // Do damage effects if damage was dealt, or if there is a bonus to the
  // effect.
  if (damage_dealt > 0 || effect_bonus > 0)
  {
    // Apply any effects (e.g., poison) that occur as the result of the damage)
    handle_damage_effects(attacked_creature, damage_dealt, damage_type, effect_bonus, damage_info.get_status_ailments());
  }

  if (damage_dealt > 0)
  {
    // Deal the damage, handling death if necessary.
    deal_damage(attacking_creature, attacked_creature, damage_dealt);
  }
  else
  {
    if (!damage_info.is_always_zero())
    {
      string no_damage_message = CombatTextKeys::get_no_damage_message(attacked_creature->get_is_player(), StringTable::get(attacked_creature->get_description_sid()));
      add_combat_message(attacking_creature, attacked_creature, no_damage_message);
    }
  }

  return true;
}

bool CombatManager::does_attack_slay_creature_race(CreaturePtr attacking_creature, CreaturePtr attacked_creature, const AttackType attack_type)
{
  WeaponManager wm;
  RaceManager rm;
  string creature_race = attacked_creature->get_race_id();
  vector<string> slay_races = wm.get_slays_races(attacking_creature, attack_type);

  for(const string& slay_race : slay_races)
  {
    // Check to see if the slay-race is related to the creature's race.
    // If the slay race is "*", the attack slays - this slays everything.
    if (rm.is_race_or_descendent(creature_race, slay_race) || slay_race == "*")
    {
      return true;
    }
  }

  return false;
}

// Apply any effects as the result of damage.  This can include incurring blindness,
// poison, etc.  Take into account whether or not the damage has overridden the status
// effects.  If so, get the set of ailments off the status ailments, and use those
// instead.
void CombatManager::handle_damage_effects(CreaturePtr creature, const int damage_dealt, const DamageType damage_type, const int effect_bonus, const StatusAilments& status_ailments)
{
  StatusEffectPtr status_effect;

  if (status_ailments.get_override_defaults())
  {
    set<string> ailments = status_ailments.get_ailments();

    for (const string& ailment : ailments)
    {
      status_effect = StatusEffectFactory::create_status_effect(ailment);
      apply_damage_effect(creature, status_effect, effect_bonus);
    }
  }
  else
  {
    status_effect = StatusEffectFactory::create_effect_for_damage_type(damage_type);
    apply_damage_effect(creature, status_effect, effect_bonus);
  }
}

void CombatManager::apply_damage_effect(CreaturePtr creature, StatusEffectPtr status_effect, const int effect_bonus)
{
  if (status_effect && status_effect->should_apply_change(creature, effect_bonus))
  {
    status_effect->apply_change(creature);
  }
}

// Deal damage to the creature, or heal it, depending on whether the damage dealt is
// positive or negative.
//
// Healing is for extreme resistance cases, like casting fireball on a fire elemental.
//
// Once damage is dealt, check for death.  If the attack has lowered the attacked creature's
// HP to 0, kill it, and award the dead creature's experience value to the attacking
// creature.
void CombatManager::deal_damage(CreaturePtr attacking_creature, CreaturePtr attacked_creature, const int damage_dealt, const string message_sid)
{
  Game& game = Game::instance();
  MapPtr map = game.get_current_map();
  
  if (map && attacked_creature)
  {
    int current_hp = attacked_creature->decrement_hit_points(damage_dealt);
    
    if (!message_sid.empty())
    {
      IMessageManager& manager = MessageManagerFactory::instance(attacked_creature, GameUtils::is_player_among_creatures(attacking_creature, attacked_creature));
      manager.add_new_message(StringTable::get(message_sid));
    }
    
    if (current_hp <= CombatConstants::DEATH_THRESHOLD)
    {      
      DeathManagerPtr death_manager = DeathManagerFactory::create_death_manager(attacking_creature, attacked_creature, map);

      // Kill the creature, and run the death event function, if necessary.
      death_manager->die();
      update_mortuaries(attacking_creature, attacked_creature->get_original_id());
      run_death_event(attacking_creature, attacked_creature, map);

      // Sometimes there will be no attacking creature, eg., when drowning, falling off mountains, etc.
      if (attacking_creature)
      {
        ExperienceManager em;
        uint experience_value = attacked_creature->get_experience_value();
        em.gain_experience(attacking_creature, experience_value);
      }
    }
  }
}

bool CombatManager::miss(CreaturePtr attacking_creature, CreaturePtr attacked_creature)
{
  string attacked_creature_desc = get_appropriate_creature_description(attacking_creature, attacked_creature);
  string combat_message = CombatTextKeys::get_miss_message(attacking_creature->get_is_player(), attacked_creature->get_is_player(), StringTable::get(attacking_creature->get_description_sid()), attacked_creature_desc);
  add_combat_message(attacking_creature, attacked_creature, combat_message);

  return true;
}

bool CombatManager::close_miss(CreaturePtr attacking_creature, CreaturePtr attacked_creature)
{
  string attacked_creature_desc = get_appropriate_creature_description(attacking_creature, attacked_creature);
  string combat_message = CombatTextKeys::get_close_miss_message(attacking_creature->get_is_player(), attacked_creature->get_is_player(), StringTable::get(attacking_creature->get_description_sid()), attacked_creature_desc);
  add_combat_message(attacking_creature, attacked_creature, combat_message);

  return true;
}

// Add messages if the damage dealt is 0 (unharmed), or negative
// (heals), or piercing, etc.
// 
// JCD FIXME Need to have the usual player vs. monster checks here
// so that these are only added when the target is not the player.
void CombatManager::add_any_necessary_damage_messages(CreaturePtr creature, CreaturePtr attacked_creature, const int damage, const bool piercing)
{
  vector<string> additional_messages;
  
  if (damage == 0)
  {
    // ...
  }
  else if (damage < 0)
  {
    // ...
  }

  if (piercing)
  {
    string attacked_creature_desc = get_appropriate_creature_description(creature, attacked_creature);
    additional_messages.push_back(CombatTextKeys::get_pierce_message(creature && creature->get_is_player(), attacked_creature && attacked_creature->get_is_player(), StringTable::get(creature->get_description_sid()), attacked_creature_desc));
  }
  
  if (!additional_messages.empty())
  {
    for (const string& msg : additional_messages)
    {
      add_combat_message(creature, attacked_creature, msg);
    }
  }
}

void CombatManager::add_combat_message(CreaturePtr creature, CreaturePtr attacked_creature, const string& combat_message)
{
  DamageText dt;

  // Display combat information.
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
  manager.add_new_message(combat_message, dt.get_colour(attacked_creature));
}

void CombatManager::send_combat_messages(CreaturePtr creature)
{
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
  manager.send();
}

bool CombatManager::is_hit(const int total_roll, const int target_number_value)
{
  return (total_roll > target_number_value);
}

bool CombatManager::is_miss(const int total_roll, const int target_number_value)
{
  return (total_roll <= target_number_value);
}

bool CombatManager::is_close_miss(const int total_roll, const int target_number_value)
{
  return (is_miss(total_roll, target_number_value) && ((target_number_value - total_roll) < CombatConstants::CLOSE_MISS_THRESHOLD));
}

bool CombatManager::is_automatic_miss(const int d100_roll)
{
  return (d100_roll <= CombatConstants::AUTOMATIC_MISS_THRESHOLD);
}

// Get the appropriate description for the attacked creature.
//
// If it is the player, it will be "you", unless the attackING creature is
// also the player, in which case it will be "yourself".
//
// If it is not the player, it will just be the creature's description.
string CombatManager::get_appropriate_creature_description(CreaturePtr attacking_creature, CreaturePtr creature)
{
  string desc;

  if (attacking_creature && creature && (attacking_creature->get_id() == creature->get_id()))
  {
    desc = TextMessages::get_reflexive_pronoun(creature);
  }
  else
  {
    if (creature->get_is_player())
    {
      desc = StringTable::get(TextKeys::YOU);
    }
    else
    {
      desc = desc + StringTable::get(creature->get_description_sid());
    }
  }
  
  return desc;
}

// Create an appropriate ISkillMarker for the attack type, and get the list of
// skills that should be marked, based on the successful attack.  Then, mark
// each of them.
void CombatManager::mark_appropriate_skills(CreaturePtr attacking_creature, const AttackType attack_type, const bool attack_success)
{
  SkillManager sm;  
  ISkillMarkerPtr skill_marker = SkillMarkerFactory::create_skill_marker(attack_type);

  if (skill_marker)
  {
    vector<SkillType> skills_to_mark = skill_marker->get_marked_skills(attacking_creature);

    for (const SkillType& skill_type : skills_to_mark)
    {
      sm.mark_skill(attacking_creature, skill_type, attack_success);
    }
  }
}

// Update the Game's and the attacking creature's mortuary with the kill.
void CombatManager::update_mortuaries(CreaturePtr attacking_creature, const string& killed_creature_id)
{
  Mortuary& game_mortuary = Game::instance().get_mortuary_ref();
  game_mortuary.add_creature_kill(killed_creature_id);

  if (attacking_creature)
  {
    Mortuary& creature_mortuary = attacking_creature->get_mortuary_ref();
    creature_mortuary.add_creature_kill(killed_creature_id);
  }
}

// Run the death event.  By default, this will be the null death function,
// which does nothing and is always safe to call.
void CombatManager::run_death_event(CreaturePtr attacking_creature, CreaturePtr attacked_creature, MapPtr map)
{
  string event_script_name = attacked_creature->get_event_script(CreatureEventScripts::CREATURE_EVENT_SCRIPT_DEATH);

  if (!event_script_name.empty())
  {
    ScriptEngine& se = Game::instance().get_script_engine_ref();
    se.execute(event_script_name);
  }
}

#ifdef UNIT_TESTS
#include "unit_tests/CombatManager_test.cpp"
#endif
