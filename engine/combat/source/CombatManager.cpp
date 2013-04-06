#include "CombatConstants.hpp"
#include "CombatManager.hpp"
#include "CombatTextKeys.hpp"
#include "CoordUtils.hpp"
#include "DeathManagerFactory.hpp"
#include "DamageCalculatorFactory.hpp"
#include "EventFunctions.hpp"
#include "ExperienceManager.hpp"
#include "Game.hpp"
#include "HostilityManager.hpp"
#include "ToHitCalculatorFactory.hpp"
#include "CombatTargetNumberCalculatorFactory.hpp"
#include "MapUtils.hpp"
#include "MessageManager.hpp"
#include "SkillManager.hpp"
#include "SpeedCalculatorFactory.hpp"
#include "TextKeys.hpp"
#include "RNG.hpp"
#include "WeaponManager.hpp"

using std::string;

CombatManager::CombatManager()
{
}

bool CombatManager::operator==(const CombatManager& cm)
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

  // Do the necessary checks here to determine whether to attack...
  CreaturePtr adjacent_creature = adjacent_tile->get_creature();
    
  // Sanity check
  if (adjacent_creature)
  {
    action_cost_value = attack(creature, adjacent_creature);
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
ActionCostValue CombatManager::attack(CreaturePtr attacking_creature, CreaturePtr attacked_creature, const AttackType attack_type)
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
    Damage damage = damage_calculator->calculate_base_damage_with_bonuses_or_penalties(attacking_creature);
        
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

  // If the attack was a PvM type attack, mark the weapon and combat skills of the attacking creature,
  // and add the attacking creature as a threat to the attacked creature.
  if (attacking_creature)
  {
    mark_weapon_and_combat_skills(attacking_creature, attack_type, mark_for_weapon_and_combat_skills);
    
    HostilityManager hm;
    hm.set_hostility_to_creature(attacked_creature, attacking_creature->get_id());
  }

  send_combat_messages();
  
  return action_cost_value;
}

bool CombatManager::hit(CreaturePtr attacking_creature, CreaturePtr attacked_creature, const int d100_roll, const Damage& damage_info, const AttackType attack_type)
{
  string attacked_creature_desc = get_appropriate_creature_description(attacked_creature);
  DamageType damage_type = damage_info.get_damage_type();
  int base_damage = 0;
  float soak_multiplier = 1.0;
  
  string combat_message = CombatTextKeys::get_hit_message(attacking_creature->get_is_player(), damage_type, StringTable::get(attacking_creature->get_description_sid()), attacked_creature_desc);

  // Critical hit: 2x damage, no soak.
  if (is_critical_hit(d100_roll))
  {
    combat_message += " " + StringTable::get(CombatTextKeys::COMBAT_CRITICAL_HIT_MESSAGE);
    base_damage = 2 * (damage_info.max());
    soak_multiplier = 0.0;
  }
  // Mighty blow: full damage, half soak.
  else if (is_mighty_blow(d100_roll))
  {
    combat_message += " " + StringTable::get(CombatTextKeys::COMBAT_MIGHTY_BLOW_MESSAGE);
    base_damage = damage_info.max();
    soak_multiplier = 0.5;
  }
  else // Regular, vanilla hit.  Roll damage, full soak.
  {
    base_damage = RNG::dice(damage_info);
  }
  
  // Deal damage.
  DamageCalculatorPtr damage_calc = DamageCalculatorFactory::create_damage_calculator(attack_type);
  int damage_dealt = damage_calc->calculate(attacked_creature, damage_info, base_damage, soak_multiplier);

  // Add the text so far.
  add_combat_message(combat_message);
  add_any_necessary_damage_messages(damage_dealt);

  if (damage_dealt > 0)
  {
    // Deal the damage, handling death if necessary.
    deal_damage(attacking_creature, attacked_creature, damage_dealt);
  }
  else
  {
    string no_damage_message = CombatTextKeys::get_no_damage_message(attacked_creature->get_is_player(), StringTable::get(attacked_creature->get_description_sid()));
    add_combat_message(no_damage_message);
  }

  return true;
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
      MessageManager& manager = MessageManager::instance();
      manager.add_new_message(StringTable::get(message_sid));
    }
    
    if (current_hp <= CombatConstants::DEATH_THRESHOLD)
    {      
      DeathManagerPtr death_manager = DeathManagerFactory::create_death_manager(attacked_creature, map);

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
  string attacked_creature_desc = get_appropriate_creature_description(attacked_creature);
  string combat_message = CombatTextKeys::get_miss_message(attacking_creature->get_is_player(), StringTable::get(attacking_creature->get_description_sid()), attacked_creature_desc);
  add_combat_message(combat_message);

  return true;
}

bool CombatManager::close_miss(CreaturePtr attacking_creature, CreaturePtr attacked_creature)
{
  string attacked_creature_desc = get_appropriate_creature_description(attacked_creature);
  string combat_message = CombatTextKeys::get_close_miss_message(attacking_creature->get_is_player(), StringTable::get(attacking_creature->get_description_sid()), attacked_creature_desc);
  add_combat_message(combat_message);

  return true;
}

// Add messages if the damage dealt is 0 (unharmed), or negative
// (heals).
// 
// JCD FIXME Need to have the usual player vs. monster checks here
// so that these are only added when the target is not the player.
void CombatManager::add_any_necessary_damage_messages(const int damage)
{
  string additional_message;
  
  if (damage == 0)
  {
    // ...
  }
  else if (damage < 0)
  {
    // ...
  }
  
  if (!additional_message.empty())
  {
    add_combat_message(additional_message);
  }
}

void CombatManager::add_combat_message(const string& combat_message)
{
  // Display combat information.
  // Right now, everything is displayed.  Will need to do LOS checking later.
  MessageManager& manager = MessageManager::instance();
  manager.add_new_message(combat_message);
}

void CombatManager::send_combat_messages()
{
  MessageManager& manager = MessageManager::instance();
  manager.send();
}

// Functions to check hit/miss/critical/etc statuses.
bool CombatManager::is_critical_hit(const int d100_roll)
{
  return (d100_roll == CombatConstants::CRITICAL_DIFFICULTY);
}

bool CombatManager::is_mighty_blow(const int d100_roll)
{
  return (d100_roll >= CombatConstants::MIGHTY_BLOW_DIFFICULTY);
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

string CombatManager::get_appropriate_creature_description(CreaturePtr creature)
{
  string desc;
  
  if (creature->get_is_player())
  {
    desc = StringTable::get(TextKeys::YOU);
  }
  else
  {
    desc = StringTable::get(creature->get_description_sid());
  }
  
  return desc;
}

void CombatManager::mark_weapon_and_combat_skills(CreaturePtr attacking_creature, const AttackType attack_type, const bool attack_success)
{
  WeaponManager wm;
  SkillManager sm;
  
  WeaponStyle ws = wm.get_style(attack_type);
  
  SkillType combat_type_skill_to_mark = SKILL_GENERAL_COMBAT;
  
  if (ws == WEAPON_STYLE_RANGED)
  {
    combat_type_skill_to_mark = SKILL_GENERAL_ARCHERY;
  }
  
  sm.mark_skill(attacking_creature, combat_type_skill_to_mark, attack_success);
  sm.mark_skill(attacking_creature, wm.get_skill_type(attacking_creature, attack_type), attack_success);
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
  string event_function_name = attacked_creature->get_event_function(CreatureEvents::CREATURE_EVENT_DEATH);
  DeathEventFunction death_fn = EventFunctions::get_death_event_function(event_function_name);
  death_fn(attacking_creature, attacked_creature, map);
}

#ifdef UNIT_TESTS
#include "unit_tests/CombatManager_test.cpp"
#endif
