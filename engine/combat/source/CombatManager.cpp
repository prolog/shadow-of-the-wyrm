#include "ActionTextKeys.hpp"
#include "AttackScript.hpp"
#include "CombatConstants.hpp"
#include "CombatManager.hpp"
#include "CombatTextKeys.hpp"
#include "Conversion.hpp"
#include "CoordUtils.hpp"
#include "CreatureFactory.hpp"
#include "CreatureSplitCalculator.hpp"
#include "CreatureDescriber.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "DamageText.hpp"
#include "DeathManagerFactory.hpp"
#include "DamageCalculatorFactory.hpp"
#include "EffectTextKeys.hpp"
#include "ExperienceManager.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "HostilityManager.hpp"
#include "IHitTypeFactory.hpp"
#include "ItemProperties.hpp"
#include "ToHitCalculatorFactory.hpp"
#include "CombatTargetNumberCalculatorFactory.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "PhaseOfMoonCalculator.hpp"
#include "PointsTransfer.hpp"
#include "RaceManager.hpp"
#include "SkillManager.hpp"
#include "SkillMarkerFactory.hpp"
#include "StatusEffectFactory.hpp"
#include "SpeedCalculatorFactory.hpp"
#include "StatisticsMarker.hpp"
#include "TertiaryUnarmedCalculator.hpp"
#include "TextKeys.hpp"
#include "TextMessages.hpp"
#include "RNG.hpp"
#include "WeaponManager.hpp"

using namespace std;

const int CombatManager::PCT_CHANCE_MARK_STATISTIC_ON_MISS = 15;

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
    if (creature && adjacent_creature)
    {
      action_cost_value = attack(creature, adjacent_creature);

      // Re-get the adjacent creature - it may have been killed by the
      // first attack.
      adjacent_creature = adjacent_tile->get_creature();

      if (adjacent_creature)
      {
        WeaponPtr off_hand_weapon = dynamic_pointer_cast<Weapon>(creature->get_equipment().get_item(EquipmentWornLocation::EQUIPMENT_WORN_OFF_HAND));

        // Secondary attacks fire only if the creature is wielding a weapon in
        // its off hand.  Shields, potions, etc., don't count!
        if (off_hand_weapon != nullptr)
        {
          action_cost_value += attack(creature, adjacent_creature, AttackType::ATTACK_TYPE_MELEE_SECONDARY);
        }
      }
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

  bool mark_for_weapon_and_combat_skills_and_stat = false;
 
  ToHitCalculatorPtr th_calculator = ToHitCalculatorFactory::create_to_hit_calculator(attacking_creature, attack_type);
  CombatTargetNumberCalculatorPtr ctn_calculator = CombatTargetNumberCalculatorFactory::create_target_number_calculator(attack_type);
  ISpeedCalculatorPtr speed_calculator = SpeedCalculatorFactory::create_speed_calculator(attack_type);

  // Once an attack is made, the creature becomes hostile, and if it was
  // previously not hostile
  if (attacking_creature && attacked_creature)
  {
    handle_hostility_implications(attacking_creature, attacked_creature);
  }

  // Getting attacked has a way of breaking concentration.
  if (attacked_creature != nullptr)
  {
    attacked_creature->get_automatic_movement_ref().set_engaged(false);
  }

  if (th_calculator && ctn_calculator)
  {
    Game& game = Game::instance();
    PhaseOfMoonCalculator pomc;
    PhaseOfMoonType phase = pomc.calculate_phase_of_moon(game.get_current_world()->get_calendar().get_seconds());

    // Ensure that attacks take at least one speed - no free attacks!
    action_cost_value = std::max(1, speed_calculator->calculate(attacking_creature));
    DamageCalculatorPtr damage_calculator = DamageCalculatorFactory::create_damage_calculator(attack_type, phase);
    
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
    else if (is_automatic_hit(d100_roll) || is_hit(total_roll, target_number_value))
    {
      hit(attacking_creature, attacked_creature, d100_roll, damage, attack_type);
      mark_for_weapon_and_combat_skills_and_stat = true;
      destroy_weapon_if_necessary(attacking_creature, attack_type);
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
      mark_appropriately(attacking_creature, attack_type, th_calculator->get_statistic(attacking_creature), mark_for_weapon_and_combat_skills_and_stat);
    }
  }

  send_combat_messages(attacking_creature);
  
  return action_cost_value;
}

void CombatManager::handle_hostility_implications(CreaturePtr attacking_creature, CreaturePtr attacked_creature)
{
  if (attacking_creature && 
      attacked_creature && 
      (attacking_creature->get_id() != attacked_creature->get_id()) && 
      !attacked_creature->get_is_player())
  {
    HostilityManager hm;
    CurrentCreatureAbilities cca;
    RaceManager rm;
    RacePtr race = rm.get_race(attacked_creature->get_race_id());
    DecisionStrategyPtr d_strat = attacked_creature->get_decision_strategy();

    if (d_strat && 
        d_strat->get_threats().has_threat(attacking_creature->get_id()).first == false &&
        race != nullptr &&
        race->get_has_voice() &&
        cca.can_speak(attacked_creature))
    {
      // The creature cries out for help
      CreatureDescriber cd(attacking_creature, attacked_creature, true);
      string cry_out_message = ActionTextKeys::get_cry_out_message(cd.describe());
      IMessageManager& manager = MM::instance(MessageTransmit::FOV, attacked_creature, attacking_creature->get_is_player());
      manager.add_new_message(cry_out_message);
      manager.send();

      // Nearby creatures friendly to the attacker, seeing which way the
      // wind is blowing, decide that the attacker is not actually all
      // that friendly.
      MapPtr fov_map = d_strat->get_fov_map();

      if (fov_map != nullptr)
      {
        TilesContainer tiles = fov_map->get_tiles();

        for (const auto& t_pair : tiles)
        {
          TilePtr tile = t_pair.second;

          if (tile && tile->has_creature())
          {
            CreaturePtr tile_creature = tile->get_creature();

            if (tile_creature && !tile_creature->get_is_player())
            {
              hm.set_hostility_to_creature(tile_creature, attacking_creature->get_id());
            }
          }
        }
      }
    }

    hm.set_hostility_to_creature(attacked_creature, attacking_creature->get_id());
  }
}

bool CombatManager::destroy_weapon_if_necessary(CreaturePtr attacking_creature, const AttackType attack_type)
{
  bool destroyed_weapon = false;

  if (attacking_creature != nullptr)
  {
    WeaponManager wm;
    WeaponPtr weapon = wm.get_weapon(attacking_creature, attack_type);

    if (weapon != nullptr)
    {
      string destruction_pct_s = weapon->get_additional_property(ItemProperties::ITEM_PROPERTIES_DESTRUCTION_PCT_CHANCE);
      int destruction_pct = destruction_pct_s.empty() ? 0 : String::to_int(destruction_pct_s);

      if (RNG::percent_chance(destruction_pct))
      {
        wm.remove_weapon(attacking_creature, attack_type);
        destroyed_weapon = true;
      }
    }
  }

  return destroyed_weapon;
}

bool CombatManager::hit(CreaturePtr attacking_creature, CreaturePtr attacked_creature, const int d100_roll, const Damage& damage_info, const AttackType attack_type)
{
  WeaponManager wm;
  Game& game = Game::instance();
  MapPtr current_map = game.get_current_map();

  if (wm.is_using_weapon(attacking_creature, attack_type))
  {
    attacking_creature->get_conducts_ref().break_conduct(ConductType::CONDUCT_TYPE_WEAPONLESS);
  }

  string attacked_creature_desc = get_appropriate_creature_description(attacking_creature, attacked_creature);
  DamageType damage_type = damage_info.get_damage_type();
  int effect_bonus = damage_info.get_effect_bonus();
  int base_damage = 0;
  
  bool use_mult_dam_type_msgs = String::to_bool(game.get_settings_ref().get_setting("multiple_damage_type_messages"));
  string combat_message = CombatTextKeys::get_hit_message(attacking_creature->get_is_player(), attacked_creature->get_is_player(), damage_type, StringTable::get(attacking_creature->get_description_sid()), attacked_creature_desc, use_mult_dam_type_msgs);

  HitTypeEnum hit_type_enum = HitTypeEnumConverter::from_successful_to_hit_roll(d100_roll);
  IHitTypeCalculatorPtr hit_calculator = IHitTypeFactory::create_hit_type(hit_type_enum);
  string hit_specific_msg = hit_calculator->get_combat_message();
  
  bool piercing = damage_info.get_piercing();
  bool incorporeal = damage_info.get_incorporeal();

  base_damage = hit_calculator->get_base_damage(damage_info);

  if (!hit_specific_msg.empty())
  {
    combat_message = combat_message + " " + hit_specific_msg;
  }

  // If this is a tertiary unarmed attack (kicking), there is a chance that 
  // the creature is knocked back, given the existence of an open, inhabitable
  // tile.
  knock_back_creature_if_necessary(attack_type, attacking_creature, attacked_creature, game, current_map);

  // Deal damage.
  PhaseOfMoonCalculator pomc;
  PhaseOfMoonType phase = pomc.calculate_phase_of_moon(game.get_current_world()->get_calendar().get_seconds());

  bool slays_race = does_attack_slay_creature_race(attacking_creature, attacked_creature, attack_type);
  DamageCalculatorPtr damage_calc = DamageCalculatorFactory::create_damage_calculator(attack_type, phase);
  float soak_multiplier = hit_calculator->get_soak_multiplier();
  int damage_dealt = damage_calc->calculate(attacked_creature, slays_race, damage_info, base_damage, soak_multiplier);

  // Add the text so far.
  add_combat_message(attacking_creature, attacked_creature, combat_message);
  add_any_necessary_damage_messages(attacking_creature, attacked_creature, damage_dealt, piercing, incorporeal);
  
  int danger_level = attacking_creature ? attacking_creature->get_level().get_current() : 1;

  // Do damage effects if damage was dealt, or if there is a bonus to the
  // effect.
  if (damage_dealt > 0 || effect_bonus > 0)
  {
    // Apply any effects (e.g., poison) that occur as the result of the damage)
    handle_damage_effects(attacked_creature, damage_dealt, damage_type, effect_bonus, damage_info.get_status_ailments(), danger_level);
  }

  if (damage_dealt > 0)
  {
    // If this attack is vorpal and passes the vorpal check, update the damage 
    // to match the creature's remaining HP
    handle_vorpal_if_necessary(attacking_creature, attacked_creature, damage_info, damage_dealt);
    deal_damage(attacking_creature, attacked_creature, damage_dealt, damage_info);
  }
  else
  {
    if (!damage_info.is_always_zero())
    {
      string no_damage_message = CombatTextKeys::get_no_damage_message(attacked_creature->get_is_player(), StringTable::get(attacked_creature->get_description_sid()));
      add_combat_message(attacking_creature, attacked_creature, no_damage_message);
    }
  }

  // If there are any scripts associated with the attack, run them.
  run_attack_script_if_necessary(attacking_creature, attacked_creature);

  return true;
}

void CombatManager::handle_vorpal_if_necessary(CreaturePtr attacking_creature, CreaturePtr attacked_creature, const Damage& damage_info, int& damage_dealt)
{
  if (attacked_creature != nullptr)
  {
    bool vorpal = damage_info.get_vorpal();
    bool attacked_creature_incorporeal = attacked_creature->has_status(StatusIdentifiers::STATUS_ID_INCORPOREAL);

    if ((damage_dealt > 0)
      && vorpal
      && RNG::percent_chance(CombatConstants::PCT_CHANCE_VORPAL)
      && !attacked_creature_incorporeal)
    {
      // Maximize the damage.
      damage_dealt = attacked_creature->get_hit_points().get_current();

      // Add a vorpal message.
      string attacking_creature_desc = (attacking_creature != nullptr) ? StringTable::get(attacking_creature->get_description_sid()) : "";
      string creature_desc = get_appropriate_creature_description(attacking_creature, attacked_creature);
      string vorpal_message = CombatTextKeys::get_vorpal_message(attacking_creature && attacking_creature->get_is_player(), attacked_creature && attacked_creature->get_is_player(), attacking_creature_desc, creature_desc);
      add_combat_message(attacking_creature, attacked_creature, vorpal_message);
    }
  }
}

void CombatManager::handle_draining_if_necessary(CreaturePtr attacking_creature, CreaturePtr attacked_creature, const int damage_dealt, const Damage& damage_info)
{
  if (damage_info.get_draining() && RNG::percent_chance(CombatConstants::PCT_CHANCE_DRAIN))
  {
    PointsTransfer pt;
    int max_drain = std::max<int>(static_cast<int>(damage_dealt * CombatConstants::DRAIN_MULTIPLIER), 1);
    int drain_amt = pt.transfer(attacking_creature, max_drain, PointsTransferType::POINTS_TRANSFER_HP);

    IMessageManager& manager = MM::instance(MessageTransmit::FOV, attacked_creature, attacked_creature && attacked_creature->get_is_player());
    string attacking_creature_desc = (attacking_creature != nullptr) ? StringTable::get(attacking_creature->get_description_sid()) : "";
    string creature_desc = get_appropriate_creature_description(attacking_creature, attacked_creature);
    string drain_message = CombatTextKeys::get_drain_message(attacking_creature && attacking_creature->get_is_player(), attacked_creature && attacked_creature->get_is_player(), attacking_creature_desc, creature_desc);
    manager.add_new_message(drain_message);

    if (drain_amt > 0)
    {
      string healing_message = EffectTextKeys::get_healing_effect_message(attacking_creature_desc, attacking_creature && attacking_creature->get_is_player());
      manager.add_new_message(healing_message);
    }

    manager.send();
  }
}

void CombatManager::handle_ethereal_if_necessary(CreaturePtr attacking_creature, CreaturePtr attacked_creature, const int damage_dealt, const Damage& damage_info)
{
  if (damage_info.get_ethereal() && RNG::percent_chance(CombatConstants::PCT_CHANCE_ETHEREAL))
  {
    attacked_creature->decrement_arcana_points(damage_dealt);

    PointsTransfer pt;
    int max_eth = std::max<int>(static_cast<int>(damage_dealt * CombatConstants::ETHEREAL_MULTIPLIER), 1);
    int ethereal_amt = pt.transfer(attacking_creature, max_eth, PointsTransferType::POINTS_TRANSFER_AP);

    IMessageManager& manager = MM::instance(MessageTransmit::FOV, attacked_creature, attacked_creature && attacked_creature->get_is_player());
    string attacking_creature_desc = (attacking_creature != nullptr) ? StringTable::get(attacking_creature->get_description_sid()) : "";
    string creature_desc = get_appropriate_creature_description(attacking_creature, attacked_creature);

    string ethereal_message = CombatTextKeys::get_ethereal_message(attacking_creature && attacking_creature->get_is_player(), attacked_creature && attacked_creature->get_is_player(), attacking_creature_desc, creature_desc);
    manager.add_new_message(ethereal_message);

    if (ethereal_amt > 0)
    {
      string ether_message = EffectTextKeys::get_ether_effect_message(attacking_creature_desc, attacking_creature && attacking_creature->get_is_player());
      manager.add_new_message(ether_message);
    }

    manager.send();
  }
}

void CombatManager::handle_split_if_necessary(CreaturePtr attacking_creature, CreaturePtr attacked_creature, RacePtr creature_race, MapPtr current_map)
{
  if (attacked_creature && creature_race)
  {
    CreatureSplitCalculator csc;

    if (RNG::percent_chance(csc.calculate_pct_chance_split(attacked_creature, creature_race, current_map)))
    {
      // Create the new creature, and adjust HP/AP.
      Game& game = Game::instance();
      CreatureFactory cf;
      CreaturePtr split_creature = cf.create_by_creature_id(game.get_action_manager_ref(), attacked_creature->get_original_id());

      if (split_creature != nullptr)
      {
        // Adjust its HP
        split_creature->get_hit_points_ref().set_current(csc.calculate_split_hit_points(attacked_creature));

        // Add it nearby.
        TileDirectionMap adjacent_tiles = MapUtils::get_adjacent_tiles_to_creature(current_map, attacked_creature);

        for (const auto& t_pair : adjacent_tiles)
        {
          if (MapUtils::is_tile_available_for_creature(split_creature, t_pair.second))
          {
            Coordinate adj_coords = CoordUtils::get_new_coordinate(current_map->get_location(attacked_creature->get_id()), t_pair.first);
            GameUtils::add_new_creature_to_map(game, split_creature, current_map, adj_coords);

            break;
          }
        }

        // Add a split message.
        string split_msg = CombatTextKeys::get_split_message(StringTable::get(attacked_creature->get_description_sid()));
        add_combat_message(attacking_creature, attacked_creature, split_msg);
      }
    }
  }
}

// After attacking, check to see if there is an associated attack script.
// If there is, run it according to the associated probability.
//
// Return true if the script was run, false otherwise.
bool CombatManager::run_attack_script_if_necessary(CreaturePtr attacking_creature, CreaturePtr attacked_creature)
{
  bool result = false;

  if (attacking_creature && attacked_creature)
  {
    ScriptDetails sd = attacking_creature->get_event_script(CreatureEventScripts::CREATURE_EVENT_SCRIPT_ATTACK);

    string script = sd.get_script();
    int chance = sd.get_chance();

    if (!script.empty() && RNG::percent_chance(chance))
    {
      Game& game = Game::instance();
      ScriptEngine& se = game.get_script_engine_ref();

      string attacking_base_id = attacking_creature->get_original_id();
      string attacked_creature_id = attacked_creature->get_id();

      AttackScript as;
      result = as.execute(se, script, attacking_creature, attacked_creature_id);
    }    
  }

  return result;
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
void CombatManager::handle_damage_effects(CreaturePtr creature, const int damage_dealt, const DamageType damage_type, const int effect_bonus, const StatusAilments& status_ailments, const int danger_level)
{
  StatusEffectPtr status_effect;

  if (status_ailments.get_override_defaults())
  {
    set<string> ailments = status_ailments.get_ailments();

    for (const string& ailment : ailments)
    {
      status_effect = StatusEffectFactory::create_status_effect(ailment);
      apply_damage_effect(creature, status_effect, effect_bonus, danger_level);
    }
  }
  else
  {
    status_effect = StatusEffectFactory::create_effect_for_damage_type(damage_type);
    apply_damage_effect(creature, status_effect, effect_bonus, danger_level);
  }
}

void CombatManager::apply_damage_effect(CreaturePtr creature, StatusEffectPtr status_effect, const int effect_bonus, const int danger_level)
{
  if (status_effect && status_effect->should_apply_change(creature, effect_bonus))
  {
    status_effect->apply_change(creature, danger_level);
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
void CombatManager::deal_damage(CreaturePtr attacking_creature, CreaturePtr attacked_creature, const int damage_dealt, const Damage& damage_info, const string message_sid)
{
  Game& game = Game::instance();
  MapPtr map = game.get_current_map();
  
  if (map && attacked_creature)
  {
    PointsTransfer pt;
    int hp_trans = pt.get_points_for_transfer(attacked_creature, damage_dealt, PointsTransferType::POINTS_TRANSFER_HP);
    int ap_trans = pt.get_points_for_transfer(attacked_creature, damage_dealt, PointsTransferType::POINTS_TRANSFER_AP);
    
    int current_hp = attacked_creature->decrement_hit_points(damage_dealt);
    
    if (!message_sid.empty())
    {
      IMessageManager& manager = MM::instance(MessageTransmit::FOV, attacked_creature, GameUtils::is_player_among_creatures(attacking_creature, attacked_creature));
      manager.add_new_message(StringTable::get(message_sid));
    }

    if (attacking_creature)
    {
      handle_draining_if_necessary(attacking_creature, attacked_creature, hp_trans, damage_info);
      handle_ethereal_if_necessary(attacking_creature, attacked_creature, ap_trans, damage_info);
    }

    if (current_hp <= CombatConstants::DEATH_THRESHOLD)
    {      
      DeathManagerPtr death_manager = DeathManagerFactory::create_death_manager(attacking_creature, attacked_creature, map);

      // Kill the creature, and run the death event function, if necessary.
      update_mortuaries(attacking_creature, attacked_creature->get_original_id());
      death_manager->die();

      // Sometimes there will be no attacking creature, eg., when drowning, falling off mountains, etc.
      if (attacking_creature)
      {
        ExperienceManager em;
        uint experience_value = attacked_creature->get_experience_value();
        em.gain_experience(attacking_creature, experience_value);
      }
    }
    else
    {
      // Does the creature split, potentially?
      RaceManager rm;
      RacePtr creature_race = rm.get_race(attacked_creature->get_race_id());
      handle_split_if_necessary(attacking_creature, attacked_creature, creature_race, map);
    }
  }
}

bool CombatManager::miss(CreaturePtr attacking_creature, CreaturePtr attacked_creature)
{
  StatisticsMarker sm;

  if (RNG::percent_chance(PCT_CHANCE_MARK_STATISTIC_ON_MISS))
  {
    sm.mark_agility(attacked_creature);
  }

  string attacked_creature_desc = get_appropriate_creature_description(attacking_creature, attacked_creature);
  string combat_message = CombatTextKeys::get_miss_message(attacking_creature->get_is_player(), attacked_creature->get_is_player(), StringTable::get(attacking_creature->get_description_sid()), attacked_creature_desc);
  add_combat_message(attacking_creature, attacked_creature, combat_message);

  return true;
}

bool CombatManager::close_miss(CreaturePtr attacking_creature, CreaturePtr attacked_creature)
{
  StatisticsMarker sm;

  // Close misses are considered misses that the creature narrowly avoided
  // due to quick reflexes - always mark Agility.
  sm.mark_agility(attacked_creature);
  
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
void CombatManager::add_any_necessary_damage_messages(CreaturePtr creature, CreaturePtr attacked_creature, const int damage, const bool piercing, const bool incorporeal)
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

  string attacked_creature_desc = get_appropriate_creature_description(creature, attacked_creature);

  if (creature && attacked_creature && (creature->get_id() != attacked_creature->get_id()))
  {
    if (piercing)
    {
      additional_messages.push_back(CombatTextKeys::get_pierce_message(creature && creature->get_is_player(), attacked_creature && attacked_creature->get_is_player(), StringTable::get(creature->get_description_sid()), attacked_creature_desc));
    }

    if (incorporeal)
    {
      additional_messages.push_back(CombatTextKeys::get_incorporeal_attack_message(creature && creature->get_is_player(), attacked_creature && attacked_creature->get_is_player(), StringTable::get(creature->get_description_sid()), attacked_creature_desc));
    }
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
  IMessageManager& manager = MM::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());
  manager.add_new_message(combat_message, dt.get_colour(attacked_creature));
}

void CombatManager::send_combat_messages(CreaturePtr creature)
{
  IMessageManager& manager = MM::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());
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

bool CombatManager::is_automatic_hit(const int d100_roll)
{
  return (d100_roll >= CombatConstants::AUTOMATIC_HIT_THRESHOLD);
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
    if (creature && creature->get_is_player())
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
void CombatManager::mark_appropriately(CreaturePtr attacking_creature, const AttackType attack_type, Statistic& marked_statistic, const bool attack_success)
{
  SkillManager sm;  
  ISkillMarkerPtr skill_marker = SkillMarkerFactory::create_skill_marker(attack_type);

  StatisticsMarker stat_marker;
  stat_marker.mark_statistic(marked_statistic);

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
  // Get whether the creature is a unique or not.
  Game& game = Game::instance();
  bool is_unique = (game.get_creature_generation_values_ref()[killed_creature_id].get_maximum() == 1);

  // Update the game's and creature's mortuary with the kill info.
  Mortuary& game_mortuary = Game::instance().get_mortuary_ref();
  game_mortuary.add_creature_kill(killed_creature_id, is_unique);

  if (attacking_creature)
  {
    Mortuary& creature_mortuary = attacking_creature->get_mortuary_ref();
    creature_mortuary.add_creature_kill(killed_creature_id, is_unique);
  }
}

bool CombatManager::knock_back_creature_if_necessary(const AttackType attack_type, CreaturePtr attacking_creature, CreaturePtr attacked_creature, Game& game, MapPtr current_map)
{
  bool knocked_back = false;

  if (attacking_creature && attacked_creature && attack_type == AttackType::ATTACK_TYPE_MELEE_TERTIARY_UNARMED)
  {
    // Check to see if the knock-back succeeded.
    TertiaryUnarmedCalculator tuc;
    int kb_chance = tuc.calculate_knock_back_pct_chance(attacking_creature);

    if (RNG::percent_chance(kb_chance))
    {
      Direction kick_dir = CoordUtils::get_direction(current_map->get_location(attacking_creature->get_id()), current_map->get_location(attacked_creature->get_id()));
      TilePtr tile = MapUtils::get_adjacent_tile(current_map, attacking_creature, kick_dir, 2);
      TilePtr next_tile = MapUtils::get_adjacent_tile(current_map, attacking_creature, kick_dir, 3);
      ActionManager& am = game.get_action_manager_ref();

      if (MapUtils::is_tile_available_for_creature(attacked_creature, tile))
      {
        am.move(attacked_creature, kick_dir);
        knocked_back = true;

        if (MapUtils::is_tile_available_for_creature(attacked_creature, next_tile))
        {
          am.move(attacked_creature, kick_dir);
        }
      }
    }
  }

  // If the creature was knocked back, and if it is appropriate to do so,
  // add a message.
  CurrentCreatureAbilities cca;

  // Show a message if the player is in the field of view of either creature.
  if (knocked_back && cca.can_see(attacking_creature))
  {
    IMessageManager& manager = MM::instance(MessageTransmit::FOV, attacking_creature, GameUtils::is_player_among_creatures(attacking_creature, attacked_creature));
    string knock_back_msg = ActionTextKeys::get_knock_back_message(attacked_creature->get_description_sid(), attacked_creature->get_is_player());

    manager.add_new_message(knock_back_msg);
    manager.send();
  }

  return knocked_back;
}
#ifdef UNIT_TESTS
#include "unit_tests/CombatManager_test.cpp"
#endif
