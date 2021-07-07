#include "ActionTextKeys.hpp"
#include "AnimationTranslator.hpp"
#include "AttackScript.hpp"
#include "AttackSpeedCalculatorFactory.hpp"
#include "BallShapeProcessor.hpp"
#include "ClassManager.hpp"
#include "CombatConstants.hpp"
#include "CombatEffectsCalculator.hpp"
#include "CombatManager.hpp"
#include "CombatTargetNumberCalculatorFactory.hpp"
#include "CombatTextKeys.hpp"
#include "Conversion.hpp"
#include "CoordUtils.hpp"
#include "CreatureCalculator.hpp"
#include "CreatureFactory.hpp"
#include "CreatureSplitCalculator.hpp"
#include "CreatureDescriber.hpp"
#include "CreatureProperties.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "DamageText.hpp"
#include "DeathManagerFactory.hpp"
#include "EffectTextKeys.hpp"
#include "EngineConversion.hpp"
#include "ExperienceManager.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "HidingCalculator.hpp"
#include "HostilityManager.hpp"
#include "IntimidationCalculator.hpp"
#include "IHitTypeFactory.hpp"
#include "ItemIdentifier.hpp"
#include "ItemProperties.hpp"
#include "KillScript.hpp"
#include "ToHitCalculatorFactory.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "PacificationCalculator.hpp"
#include "PhaseOfMoonCalculator.hpp"
#include "PointsTransfer.hpp"
#include "RaceManager.hpp"
#include "RNG.hpp"
#include "ScythingCalculator.hpp"
#include "Setting.hpp"
#include "SkillManager.hpp"
#include "SkillMarkerFactory.hpp"
#include "StatusEffectFactory.hpp"
#include "StealthCalculator.hpp"
#include "StatisticsMarker.hpp"
#include "TextKeys.hpp"
#include "TextMessages.hpp"
#include "UnarmedCombatCalculator.hpp"
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
  ActionCostValue action_cost_value = ActionCostConstants::NO_ACTION;
  
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
      AttackType attack_type = AttackType::ATTACK_TYPE_MELEE_PRIMARY;
      action_cost_value = attack(creature, adjacent_creature, attack_type);

      // Re-get the adjacent creature - it may have been killed by the
      // first attack, or knocked back.
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

        // A secondary attack may have killed the creature, or the creature
        // may have been knocked back.
        adjacent_creature = adjacent_tile->get_creature();

        // If we're doing unarmed melee, there is a chance as well to kick.
        UnarmedCombatCalculator ucc;

        if (adjacent_creature != nullptr)
        {
          Coordinate attack_c = map->get_location(creature->get_id());
          Coordinate defend_c = map->get_location(adjacent_creature->get_id());

          if (CoordUtils::are_coordinates_adjacent(attack_c, defend_c) &&
              RNG::percent_chance(ucc.calculate_pct_chance_free_kick(creature)))
          {
            IMessageManager& manager = MM::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());
            manager.add_new_message(ActionTextKeys::get_kick_message(creature->get_description_sid(), creature->get_is_player()));
                    
            // The kick is free - it's considered part of the primary attack -
            // so we ignore its action_cost_value.
            attack(creature, adjacent_creature, AttackType::ATTACK_TYPE_MELEE_TERTIARY_UNARMED);
          }
        }
      }
    }
  }
  else
  {
    // Couldn't get the tile.  This could be because the creature is
    // stunned and picked a direction without a tile (e.g., north at
    // row 0)
    action_cost_value = ActionCostConstants::DEFAULT;
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
ActionCostValue CombatManager::attack(CreaturePtr attacking_creature, CreaturePtr attacked_creature, const AttackType attack_type, const AttackSequenceType ast, const bool mark_skills, DamagePtr predefined_damage)
{
  ActionCostValue action_cost_value = ActionCostConstants::NO_ACTION;

  bool mark_for_weapon_and_combat_skills_and_stat = false;
  int damage_dealt = 0;

  ToHitCalculatorPtr th_calculator = ToHitCalculatorFactory::create_to_hit_calculator(attacking_creature, attack_type);
  CombatTargetNumberCalculatorPtr ctn_calculator = CombatTargetNumberCalculatorFactory::create_target_number_calculator(attack_type);
  AttackSpeedCalculatorPtr speed_calculator = AttackSpeedCalculatorFactory::create_speed_calculator(attack_type);

  // Once an attack is made, the creature becomes hostile, and if it was
  // previously not hostile
  if (attacking_creature && attacked_creature && !attacked_creature->is_dead())
  {
    handle_hostility_implications(attacking_creature, attacked_creature);
  }

  // Getting attacked has a way of breaking concentration.
  if (attacked_creature != nullptr)
  {
    attacked_creature->get_automatic_movement_ref().set_engaged(false);
  }

  if (th_calculator && ctn_calculator && attacked_creature && !attacked_creature->is_dead())
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

    Damage damage = determine_damage(attacking_creature, predefined_damage.get(), damage_calculator.get());
        
    // Automatic miss is checked first
    if (is_automatic_miss(d100_roll))
    {
      miss(attacking_creature, attacked_creature);
    }
    else if (!attacked_creature->has_status(StatusIdentifiers::STATUS_ID_HIDE) && is_intimidate(attacking_creature, attacked_creature, attack_type))
    {
      intimidate(attacking_creature, attacked_creature);
    }
    // Hit
    else if (is_automatic_hit(d100_roll) || is_hit(total_roll, target_number_value))
    {
      damage_dealt = hit(attacking_creature, attacked_creature, d100_roll, damage, attack_type, ast);
      mark_for_weapon_and_combat_skills_and_stat = (damage_dealt > 0);
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

    counter_strike_if_necessary(attacking_creature, attacked_creature, ast);
  }

  // If the attack was a successful PvM type attack (damage was dealt), 
  // mark the weapon/spell-category and combat/magic skills of the 
  // attacking creature, and add the attacking creature as a threat to the attacked creature.
  //
  // Don't improve stats if the attacking creature is dead (as a result of a
  // counter-strike, etc).
  if (attacking_creature && !attacking_creature->is_dead())
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
      (attacking_creature->get_id() != attacked_creature->get_id()))
  {
    HostilityManager hm;
    CurrentCreatureAbilities cca;
    RaceManager rm;
    Race* race = rm.get_race(attacked_creature->get_race_id());
    DecisionStrategy* d_strat = attacked_creature->get_decision_strategy();

    if (d_strat && 
        d_strat->get_threats().has_threat(attacking_creature->get_id()).first == false &&
        race != nullptr &&
        race->get_has_voice() &&
        attacked_creature != nullptr &&
        cca.can_speak(attacked_creature))
    {
      // The creature cries out for help if not the player
      if (!attacked_creature->get_is_player())
      {
        string cry_out_message = ActionTextKeys::get_cry_out_message(StringTable::get(attacked_creature->get_description_sid()));
        IMessageManager& manager = MM::instance(MessageTransmit::FOV, attacked_creature, attacking_creature->get_is_player());
        manager.add_new_message(cry_out_message);
        manager.send();
      }

      // Nearby creatures friendly to the attacker, seeing which way the
      // wind is blowing, decide that the attacker is not actually all
      // that friendly.
      MapPtr fov_map = d_strat->get_fov_map();
      CreatureCalculator cc;

      if (fov_map != nullptr)
      {
        TilesContainer tiles = fov_map->get_tiles();

        for (const auto& t_pair : tiles)
        {
          TilePtr tile = t_pair.second;

          if (tile && tile->has_creature())
          {
            CreaturePtr tile_creature = tile->get_creature();

            if (tile_creature && 
               !tile_creature->get_is_player() && 
                RNG::percent_chance(cc.get_combat_assist_pct(tile_creature)) &&
               !tile_creature->is_allied_to(attacking_creature->get_original_id()))
            {
              // Make them co-hostile to avoid hostility cascades.
              hm.set_hostility_to_creature(tile_creature, attacking_creature->get_id());
              hm.set_hostility_to_creature(attacking_creature, tile_creature->get_id());
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

bool CombatManager::counter_strike_if_necessary(CreaturePtr attacking_creature, CreaturePtr attacked_creature, const AttackSequenceType ast)
{
  bool attack_countered = false;
  MapPtr current_map = Game::instance().get_current_map();

  if (current_map && 
      attacking_creature && 
      attacked_creature && 
      !attacked_creature->has_status(StatusIdentifiers::STATUS_ID_HIDE) &&
      attacking_creature->get_id() != attacked_creature->get_id() &&
      ast == AttackSequenceType::ATTACK_SEQUENCE_INITIAL &&
      MapUtils::are_creatures_adjacent(current_map, attacking_creature, attacked_creature))
  {
    CombatEffectsCalculator cec;

    if (RNG::percent_chance(cec.calc_pct_chance_counter_strike(attacked_creature)))
    {
      add_counter_strike_message(attacking_creature, attacked_creature);

      // Mark Combat and Dex from the successful counter.
      StatisticsMarker sm;
      attacked_creature->get_skills().mark(SkillType::SKILL_GENERAL_COMBAT);
      sm.mark_dexterity(attacked_creature);

      // Deal the damage, flipping the attack sequence (the counter cannot be
      // countered).
      attack(attacked_creature, attacking_creature, AttackType::ATTACK_TYPE_MELEE_PRIMARY, AttackSequenceType::ATTACK_SEQUENCE_COUNTER);
      attack_countered = true;
    }
  }

  return attack_countered;
}

void CombatManager::add_counter_strike_message(CreaturePtr attacking_creature, CreaturePtr attacked_creature)
{
  if (attacking_creature && attacked_creature)
  {
    CreatureDescriber cd(attacking_creature, attacked_creature, true);
    string desc = cd.describe();
    string counter_message = CombatTextKeys::get_counter_message(attacked_creature->get_is_player(), desc);
    IMessageManager& manager = MM::instance(MessageTransmit::FOV, attacked_creature, (attacking_creature->get_is_player() || attacked_creature->get_is_player()));

    manager.add_new_message(counter_message);
    manager.send();
  }
}

bool CombatManager::handle_scything_if_necessary(CreaturePtr attacking_creature, CreaturePtr attacked_creature, const AttackType attack_type, const AttackSequenceType ast, const Damage& damage_info)
{
  bool scythed = false;
  set<string> visited_creature_ids;
  MapPtr current_map = Game::instance().get_current_map();

  if (current_map && 
      attacking_creature && 
      attacked_creature && 
      ast == AttackSequenceType::ATTACK_SEQUENCE_INITIAL &&
      damage_info.get_scything())
  {
    Coordinate attack_creature_coord = current_map->get_location(attacking_creature->get_id());
    Coordinate attacked_creature_coord = current_map->get_location(attacked_creature->get_id());
    int radius = CoordUtils::chebyshev_distance(attack_creature_coord, attacked_creature_coord);

    // Get the rotation direction based on the attacking creature's handedness.
    RotationDirection rd = HandednessEnum::to_rotation_direction(attacking_creature->get_handedness());

    // Generate the scything coordinates in a square (since SotW uses square
    // LOS) around the attacking creature, based on the distance between the
    // attacker and the current target.
    vector<Coordinate> scythe_coords = CoordUtils::get_square_coordinates(attack_creature_coord.first, attack_creature_coord.second, radius, rd);

    // Rotate the elements, using the attacked creature's coordinate as the
    // pivot.  Remove the attacked creature's coordinates from the scything
    // list so that it's not attacked twice.
    if (!scythe_coords.empty())
    {
      std::rotate(scythe_coords.begin(), std::find(scythe_coords.begin(), scythe_coords.end(), attacked_creature_coord), scythe_coords.end());
      auto sc_it = std::find(scythe_coords.begin(), scythe_coords.end(), attacked_creature_coord);

      if (sc_it != scythe_coords.end())
      {
        scythe_coords.erase(sc_it);
      }
    }
    
    bool message_shown = false;
    ScythingCalculator sc;
    WeaponManager wm;
    SkillType scything_skill = wm.get_appropriate_trained_skill(wm.get_weapon(attacking_creature, attack_type), attack_type);
    int total_attacks = 1;

    // Attack any hostile creatures in the scything sequence.
    for (const Coordinate& c : scythe_coords)
    {
      TilePtr tile = current_map->at(c);

      if (tile != nullptr)
      {
        CreaturePtr creature = tile->get_creature();

        int pct_chance_continue = sc.calc_pct_chance_scything_continues(attacking_creature, scything_skill, total_attacks);

        if (!RNG::percent_chance(pct_chance_continue))
        {
          break;
        }

        if (creature != nullptr && creature->get_decision_strategy()->get_threats_ref().has_threat(attacking_creature->get_id()).first)
        {
          // Show a "You/monster follow through!" message, but only once.
          if (message_shown == false)
          {
            IMessageManager& manager = MM::instance(MessageTransmit::SELF, attacking_creature, attacking_creature->get_is_player());
            manager.add_new_message(CombatTextKeys::get_scything_message(attacking_creature->get_is_player(), attacking_creature->get_description_sid()));
            manager.send();

            message_shown = true;
          }

          // Mark that the attack is a follow through to avoid the joy of
          // infinite recursion.
          attack(attacking_creature, creature, attack_type, AttackSequenceType::ATTACK_SEQUENCE_FOLLOW_THROUGH);
          total_attacks++;
        }
      }
    }
  }

  return scythed;
}

int CombatManager::hit(CreaturePtr attacking_creature, CreaturePtr attacked_creature, const int d100_roll, const Damage& damage_info, const AttackType attack_type, const AttackSequenceType ast)
{
  WeaponManager wm;
  Game& game = Game::instance();
  MapPtr current_map = game.get_current_map();
  ostringstream combat_message;

  if (wm.is_using_weapon(attacking_creature, attack_type))
  {
    attacking_creature->get_conducts_ref().break_conduct(ConductType::CONDUCT_TYPE_WEAPONLESS);
  }

  StealthCalculator sc;
  bool sneak_attack = RNG::percent_chance(sc.calculate_pct_chance_sneak_attack(attacking_creature, attacked_creature));
  string attacked_creature_desc = get_appropriate_creature_description(attacking_creature, attacked_creature);
  DamageType damage_type = damage_info.get_damage_type();
  int effect_bonus = damage_info.get_effect_bonus();
  int base_damage = 0;

  Damage combat_damage_fixed = damage_info;

  if (combat_damage_fixed.get_chaotic())
  {
    combat_damage_fixed.set_chaotic(false);
    combat_damage_fixed.set_damage_type(damage_type);
  }
  
  bool use_mult_dam_type_msgs = String::to_bool(game.get_settings_ref().get_setting(Setting::MULTIPLE_DAMAGE_TYPE_MESSAGES));

  if (sneak_attack)
  {
    combat_message << StringTable::get(CombatTextKeys::COMBAT_SNEAK_ATTACK) << " ";
    
    if (attacked_creature)
    {
      attacked_creature->set_additional_property(CreatureProperties::CREATURE_PROPERTIES_BACKSTABBED, to_string(true));
    }
  }

  combat_message << CombatTextKeys::get_hit_message(attacking_creature->get_is_player(), attacked_creature->get_is_player(), damage_type, StringTable::get(attacking_creature->get_description_sid()), attacked_creature_desc, use_mult_dam_type_msgs);

  HitTypeEnum hit_type_enum = HitTypeEnumConverter::from_successful_to_hit_roll(d100_roll);
  IHitTypeCalculatorPtr hit_calculator = IHitTypeFactory::create_hit_type(hit_type_enum);
  string hit_specific_msg = hit_calculator->get_combat_message();
  
  bool piercing = combat_damage_fixed.get_piercing();
  bool incorporeal = combat_damage_fixed.get_incorporeal();

  base_damage = hit_calculator->get_base_damage(combat_damage_fixed);

  if (!hit_specific_msg.empty())
  {
    combat_message << " " << hit_specific_msg;
  }

  // If this is a tertiary unarmed attack (kicking), there is a chance that 
  // the creature is knocked back, given the existence of an open tile.
  int damage_dealt = 0;
  knock_back_creature_if_necessary(attack_type, attacking_creature, attacked_creature, game, current_map);

  // This may have killed the creature due to traps present and triggered on
  // the new tile.  If so, be sure not to do the rest of the damage 
  // application.
  if (attacked_creature != nullptr && attacked_creature->is_dead())
  {
    return damage_dealt;
  }

  // Deal damage.
  PhaseOfMoonCalculator pomc;
  PhaseOfMoonType phase = pomc.calculate_phase_of_moon(game.get_current_world()->get_calendar().get_seconds());

  bool slays_race = does_attack_slay_creature_race(attacking_creature, attacked_creature, attack_type);
  DamageCalculatorPtr damage_calc = DamageCalculatorFactory::create_damage_calculator(attack_type, phase);
  float soak_multiplier = hit_calculator->get_soak_multiplier();
  damage_dealt = damage_calc->calculate(attacked_creature, sneak_attack, slays_race, combat_damage_fixed, base_damage, soak_multiplier);

  bool highlight_damage_msg = check_highlight_damage(attacked_creature, hit_type_enum, damage_dealt);

  // Add the text so far.
  add_combat_message(attacking_creature, attacked_creature, combat_message.str(), highlight_damage_msg);
  add_any_necessary_damage_messages(attacking_creature, attacked_creature, damage_dealt, piercing, incorporeal);
  
  // Do damage effects if damage was dealt, or if there is a bonus to the
  // effect.
  if (damage_dealt > 0 || effect_bonus > 0)
  {
    int danger_level = attacking_creature ? attacking_creature->get_level().get_current() : 1;

    // Apply any effects (e.g., poison) that occur as the result of the damage)
    handle_damage_effects(attacking_creature, attacked_creature, damage_dealt, damage_type, effect_bonus, combat_damage_fixed.get_status_ailments(), danger_level);

    // If the creature is hidden, see if they remain hidden
    handle_attacker_hidden_after_damage(attacking_creature);
  }

  if (damage_dealt > 0)
  {
    // If this attack is vorpal and passes the vorpal check, update the damage 
    // to match the creature's remaining HP
    string source_id = attacking_creature != nullptr ? attacking_creature->get_id() : "";

    handle_vorpal_if_necessary(attacking_creature, attacked_creature, combat_damage_fixed, damage_dealt); 
    handle_explosive_if_necessary(attacking_creature, attacked_creature, current_map, damage_dealt, combat_damage_fixed, attack_type);
    deal_damage(attacking_creature, attacked_creature, attack_type, source_id, damage_dealt, combat_damage_fixed);

    if (!attacked_creature->is_dead())
    {
      mark_health_for_damage_taken(attacking_creature, attacked_creature);
    }
  }
  else
  {
    if (!combat_damage_fixed.is_always_zero())
    {
      string no_damage_message = CombatTextKeys::get_no_damage_message(attacked_creature->get_is_player(), StringTable::get(attacked_creature->get_description_sid()));
      add_combat_message(attacking_creature, attacked_creature, no_damage_message);
    }
  }

  // If there are any scripts associated with the attack, run them.
  run_attack_script_if_necessary(attacking_creature, attacked_creature);

  // If the attack is scything, continue the attack on nearby creatures.
  handle_scything_if_necessary(attacking_creature, attacked_creature, attack_type, ast, combat_damage_fixed);

  return damage_dealt;
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
    string creature_desc = get_appropriate_creature_description(attacking_creature, attacked_creature, false);

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
    string creature_desc = get_appropriate_creature_description(attacking_creature, attacked_creature, false);

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

void CombatManager::handle_explosive_if_necessary(CreaturePtr attacking_creature, CreaturePtr attacked_creature, MapPtr map, const int damage_dealt, const Damage& damage_info, const AttackType attack_type)
{
  if (damage_info.get_explosive() && attacked_creature != nullptr && map)
  {
    // Add a message about the explosion.
    IMessageManager& manager = MM::instance(MessageTransmit::FOV, attacked_creature, attacked_creature && attacked_creature->get_is_player());
    string attacking_creature_desc = (attacking_creature != nullptr) ? StringTable::get(attacking_creature->get_description_sid()) : "";
    string creature_desc = get_appropriate_creature_description(attacking_creature, attacked_creature, false);

    string explosion_msg = CombatTextKeys::get_explosive_message(attacking_creature && attacking_creature->get_is_player(), attacked_creature && attacked_creature->get_is_player(), attacking_creature_desc, creature_desc);
    manager.add_new_message(explosion_msg);
    manager.send();

    // Deal the additional damage to the attacked creature, as well as those
    // around it that are not the attacker.  Explosive damage is half the
    // original.
    DamagePtr explosive_damage = std::make_shared<Damage>();
    explosive_damage->set_num_dice(std::max(1, damage_dealt/2));
    explosive_damage->set_dice_sides(1);
    explosive_damage->set_damage_type(DamageType::DAMAGE_TYPE_HEAT);
    
    BallShapeProcessor bsp;
    Spell expl;
    expl.set_colour(Colour::COLOUR_RED);
    expl.set_range(1);

    auto t_anim = bsp.get_affected_tiles_and_animation_for_spell(map, map->get_location(attacked_creature->get_id()), Direction::DIRECTION_NULL, expl);
    auto expl_tiles = t_anim.first;

    // Show the explosion animation
    Game& game = Game::instance();
    CreaturePtr player = game.get_current_player();
    MapPtr player_fov_map = player->get_decision_strategy()->get_fov_map();
    game.get_display()->draw_animation(t_anim.second, player_fov_map);

    vector<CreaturePtr> aff_creatures = MapUtils::get_adjacent_creatures_unsorted(map, attacked_creature);

    for (auto expl_tile_ct : expl_tiles)
    {
      TilePtr expl_tile = expl_tile_ct.second;

      if (expl_tile && expl_tile->has_creature())
      {
        CreaturePtr aff_creature = expl_tile->get_creature();
        if (aff_creature && (!attacking_creature || (aff_creature->get_id() != attacking_creature->get_id())))
        {
          attack(attacking_creature, aff_creature, attack_type, AttackSequenceType::ATTACK_SEQUENCE_FOLLOW_THROUGH, true, explosive_damage);
        }
      }
    }
  }
}

void CombatManager::handle_split_if_necessary(CreaturePtr attacking_creature, CreaturePtr attacked_creature, Race* creature_race, MapPtr current_map)
{
  if (attacked_creature && creature_race)
  {
    CreatureSplitCalculator csc;

    if (RNG::percent_chance(csc.calculate_pct_chance_split(attacked_creature, creature_race, current_map)))
    {
      // Create the new creature, and adjust HP/AP.
      Game& game = Game::instance();
      CreatureFactory cf;
      CreaturePtr split_creature = cf.create_by_creature_id(game.get_action_manager_ref(), attacked_creature->get_original_id(), current_map);

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
      MapPtr map = game.get_current_map();
      bool adjacent = false;

      string attacking_base_id = attacking_creature->get_original_id();
      string attacked_creature_id = attacked_creature->get_id();

      if (map != nullptr)
      {
        Coordinate c = map->get_location(attacking_creature->get_id());
        Coordinate c2 = map->get_location(attacked_creature_id);

        adjacent = CoordUtils::are_coordinates_adjacent(c, c2);
      }

      AttackScript as;
      result = as.execute(se, script, attacking_creature, attacked_creature_id, adjacent);
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
void CombatManager::handle_damage_effects(CreaturePtr attacking_creature, CreaturePtr creature, const int damage_dealt, const DamageType damage_type, const int effect_bonus, const StatusAilments& status_ailments, const int danger_level)
{
  StatusEffectPtr status_effect;
  string source_id;

  if (attacking_creature != nullptr)
  {
    source_id = attacking_creature->get_id();
  }

  if (status_ailments.get_override_defaults())
  {
    set<string> ailments = status_ailments.get_ailments();

    for (const string& ailment : ailments)
    {
      status_effect = StatusEffectFactory::create_status_effect(ailment, source_id);
      apply_damage_effect(creature, status_effect, effect_bonus, danger_level);
    }
  }
  else
  {
    status_effect = StatusEffectFactory::create_effect_for_damage_type(damage_type, source_id);
    apply_damage_effect(creature, status_effect, effect_bonus, danger_level);
  }
}

void CombatManager::record_death_info_for_dump(CreaturePtr attacking_creature, CreaturePtr attacked_creature, const AttackType attack_type, const string& dmg_source_id, const string& death_source_sid, MapPtr map)
{
  if (map != nullptr && attacked_creature != nullptr && attacked_creature->get_is_player())
  {
    CreaturePtr source_creature = attacking_creature;
    string killed_by_sid;
    bool secondary_creature_check = false;

    // Dump the death source details.
    if (!death_source_sid.empty())
    {
      killed_by_sid = death_source_sid;
      secondary_creature_check = true;
    }
    else if (source_creature != nullptr)
    {
      killed_by_sid = source_creature->get_description_sid();
    }

    ostringstream kbc_ss;
    kbc_ss << StringTable::get(killed_by_sid);

    if (secondary_creature_check && !dmg_source_id.empty())
    {
      CreaturePtr indirect_creature = map->get_creature(dmg_source_id);
      string screature_desc_sid;

      if (indirect_creature != nullptr)
      {
        screature_desc_sid = source_creature->get_description_sid();
        source_creature = indirect_creature;
      }
      else if (attacking_creature != nullptr)
      {
        screature_desc_sid = attacking_creature->get_description_sid();
      }

      if (!screature_desc_sid.empty())
      {
        kbc_ss << " (" << StringTable::get(screature_desc_sid) << ")";
      }
    }

    WeaponPtr weapon;
    WeaponManager wm;
    weapon = wm.get_weapon(source_creature, attack_type);

    if (source_creature != nullptr)
    {
      if (weapon != nullptr)
      {
        ItemIdentifier iid;
        kbc_ss << " [" << iid.get_appropriate_description(weapon, false) << "]";
      }
      if (attack_type == AttackType::ATTACK_TYPE_MAGICAL)
      {
        string spell_id = source_creature->get_additional_property(CreatureProperties::CREATURE_PROPERTIES_SPELL_IN_PROGRESS);
        const SpellMap& spells = Game::instance().get_spells_ref();

        auto s_it = spells.find(spell_id);

        if (s_it != spells.end())
        {
          kbc_ss << " [" << StringTable::get(s_it->second.get_spell_name_sid()) << "]";
        }
        else
        {
          string item_id = source_creature->get_additional_property(CreatureProperties::CREATURE_PROPERTIES_ITEM_IN_USE);
          ItemPtr used_item = source_creature->get_inventory()->get_from_id(item_id);

          if (used_item != nullptr)
          {
            // Identify the item before dumping it.
            ItemIdentifier iid;
            iid.set_item_identified(attacked_creature, used_item, used_item->get_base_id(), true);

            kbc_ss << " [" << iid.get_appropriate_description(used_item, false) << "]";
          }
        }
      }
    }

    if (killed_by_sid.empty())
    {
      kbc_ss << "?";
    }

    attacked_creature->set_additional_property(CreatureProperties::CREATURE_PROPERTIES_KILLED_BY_SOURCE, kbc_ss.str());

    // Dump the death depth and location details.
    string depth = map->size().depth().str(true);
    attacked_creature->set_additional_property(CreatureProperties::CREATURE_PROPERTIES_KILLED_BY_DEPTH, depth);

    string map_desc = MapUtils::get_map_description(map);
    attacked_creature->set_additional_property(CreatureProperties::CREATURE_PROPERTIES_KILLED_BY_MAP, map_desc);
  }
}

void CombatManager::handle_attacker_hidden_after_damage(CreaturePtr attacking_creature)
{
  if (attacking_creature != nullptr)
  {
    HidingCalculator hc;
    
    if (!RNG::percent_chance(hc.calculate_pct_chance_hidden_after_attacking(attacking_creature)))
    {
      attacking_creature->set_free_hidden_actions(0);
    }
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
void CombatManager::deal_damage(CreaturePtr combat_attacking_creature, CreaturePtr attacked_creature, const AttackType attack_type, const string& source_id, const int damage_dealt, const Damage& damage_info, const string& message_sid, const string& death_source_sid)
{
  Game& game = Game::instance();
  MapPtr map = game.get_current_map();
  
  if (map && attacked_creature)
  {
    CreaturePtr attacking_creature = combat_attacking_creature;

    if (attacking_creature == nullptr && !source_id.empty())
    {
      attacking_creature = map->get_creature(source_id);
    }

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
      // Run any kill scripts before the DeathManager is invoked, to ensure
      // that the killed creature is still present on the map.
      if (attacking_creature != nullptr)
      {
        ClassManager cm;
        Class* cr_class = cm.get_class(attacking_creature->get_class_id());

        if (cr_class != nullptr)
        {
          ScriptEngine& se = Game::instance().get_script_engine_ref();
          KillScript ks;
          string kill_script_name = cr_class->get_kill_script();

          ks.execute(se, kill_script_name, attacked_creature, attacking_creature);
        }
      }

      // If this is the player, record the necessary death info for the
      // character dump.
      record_death_info_for_dump(attacking_creature, attacked_creature, attack_type, source_id, death_source_sid, map);

      DeathManagerPtr death_manager = DeathManagerFactory::create_death_manager(attacking_creature, attacked_creature, map);

      // Record the first kill if necessary.
      if (attacking_creature && !attacking_creature->has_additional_property(CreatureProperties::CREATURE_PROPERTIES_FIRST_KILL_ID))
      {
        attacking_creature->set_additional_property(CreatureProperties::CREATURE_PROPERTIES_FIRST_KILL_ID, attacked_creature->get_original_id());
      }

      bool no_exp = String::to_bool(attacked_creature->get_additional_property(CreatureProperties::CREATURE_PROPERTIES_NO_EXP));

      // Kill the creature, and run the death event function, if necessary.
      update_mortuaries(attacking_creature, attacked_creature);

      // Break the pacifist conduct on the attacker before killing the creature.
      if (attacking_creature)
      {
        attacking_creature->get_conducts_ref().break_conduct(ConductType::CONDUCT_TYPE_PACIFIST);
      }

      death_manager->die();

      // Sometimes there will be no attacking creature, eg., when drowning, falling off mountains, etc.
      if (attacking_creature)
      {
        if (no_exp)
        {
          // Add no-exp kill msg.
          IMessageManager& manager = MM::instance(MessageTransmit::SELF, attacking_creature, attacking_creature->get_is_player());
          manager.add_new_message(StringTable::get(CombatTextKeys::COMBAT_NO_EXP_KILL));
        }
        else
        {
          gain_experience(attacking_creature, attacked_creature, map);
        }
      }
    }
    else
    {
      // Does the creature split, potentially?
      RaceManager rm;
      Race* creature_race = rm.get_race(attacked_creature->get_race_id());
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

bool CombatManager::intimidate(CreaturePtr attacking_creature, CreaturePtr attacked_creature)
{
  StatisticsMarker sm;

  if (RNG::percent_chance(50))
  {
    sm.mark_charisma(attacked_creature);
  }

  string attacked_creature_desc = get_appropriate_creature_description(attacking_creature, attacked_creature);
  string intim_message = CombatTextKeys::get_intimidate_message(attacking_creature->get_is_player(), attacked_creature->get_is_player(), StringTable::get(attacking_creature->get_description_sid()), attacked_creature_desc);
  add_combat_message(attacking_creature, attacked_creature, intim_message);

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

void CombatManager::add_combat_message(CreaturePtr creature, CreaturePtr attacked_creature, const string& combat_message, const bool highlight)
{
  DamageText dt;

  // Display combat information.
  IMessageManager& manager = MM::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());
  Colour colour = highlight ? Colour::COLOUR_RED : dt.get_colour(attacked_creature);

  manager.add_new_message(combat_message, colour);
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

bool CombatManager::is_intimidate(CreaturePtr attacking_creature, CreaturePtr attacked_creature, const AttackType attack_type)
{
  bool intim = false;

  if (attacking_creature != nullptr && attacked_creature != nullptr)
  {
    IntimidationCalculator ic;

    if (RNG::percent_chance(ic.calculate_pct_chance_intimidated(attacking_creature, attacked_creature)))
    {
      // Only melee attacks are subject to intimidation.
      switch (attack_type)
      {
        case AttackType::ATTACK_TYPE_MELEE_PRIMARY:
        case AttackType::ATTACK_TYPE_MELEE_SECONDARY:
        case AttackType::ATTACK_TYPE_MELEE_TERTIARY_UNARMED:
        {
          intim = true;
          break;
        }
        case AttackType::ATTACK_TYPE_MAGICAL:
        case AttackType::ATTACK_TYPE_RANGED:
        case AttackType::ATTACK_TYPE_UNDEFINED:
          break;
      }
    }
  }

  return intim;
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
string CombatManager::get_appropriate_creature_description(CreaturePtr attacking_creature, CreaturePtr creature, const bool use_reflexive_when_same)
{
  string desc;

  if (attacking_creature && 
      creature && 
     (attacking_creature->get_id() == creature->get_id()) && 
     (use_reflexive_when_same || creature->get_is_player()))
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

// Seeking out dangerous creatures (those at your level or higher) and getting
// hurt by them trains health.
void CombatManager::mark_health_for_damage_taken(CreaturePtr attacking_creature, CreaturePtr attacked_creature)
{
  if (attacking_creature != nullptr && attacked_creature != nullptr)
  {
    if (attacking_creature->get_level().get_current() >= attacked_creature->get_level().get_current())
    {
      StatisticsMarker sm;
      sm.mark_health(attacked_creature);
    }
  }
}

// Update the Game's and the attacking creature's mortuary with the kill.
void CombatManager::update_mortuaries(CreaturePtr attacking_creature, CreaturePtr attacked_creature)
{
  // Get whether the creature is a unique or not.
  Game& game = Game::instance();

  if (attacked_creature)
  {
    string killed_creature_id = attacked_creature->get_original_id();
    bool is_unique = false;

    // Some procedurally generated creatures, like ancient beasts, won't
    // exist in the main game map.  In this case, assume they are not
    // unique.
    CreatureGenerationValuesMap& cgvm = game.get_creature_generation_values_ref();
    auto c_it = cgvm.find(killed_creature_id);
    int attacked_lvl = attacked_creature->get_level().get_current();

    if (c_it != cgvm.end())
    {
      CreatureGenerationValues cgv = game.get_creature_generation_values_ref()[killed_creature_id];
      is_unique = (cgv.get_maximum() == 1);
      attacked_lvl = cgv.get_danger_level();
    }

    string short_desc_sid = attacked_creature->get_short_description_sid();

    // Update the game's and creature's mortuary with the kill info.
    Mortuary& game_mortuary = Game::instance().get_mortuary_ref();
    game_mortuary.add_creature_kill(killed_creature_id, short_desc_sid, is_unique);

    if (attacking_creature)
    {
      Mortuary& creature_mortuary = attacking_creature->get_mortuary_ref();
      creature_mortuary.add_creature_kill(killed_creature_id, short_desc_sid, is_unique);

      int level_diff = attacked_lvl - attacking_creature->get_level().get_current();
      pair<int, string> max_diff = creature_mortuary.get_max_level_difference();

      if (level_diff > max_diff.first)
      {
        creature_mortuary.set_max_level_difference(make_pair(level_diff, killed_creature_id));
      }
    }
  }
}

bool CombatManager::knock_back_creature_if_necessary(const AttackType attack_type, CreaturePtr attacking_creature, CreaturePtr attacked_creature, Game& game, MapPtr current_map)
{
  bool knocked_back = false;
  CombatEffectsCalculator cec;

  if (attacking_creature && 
      attacked_creature && 
      RNG::percent_chance(cec.calculate_knock_back_pct_chance(attack_type, attacking_creature, attacked_creature)))
  {
    Direction knockback_dir = CoordUtils::get_direction(current_map->get_location(attacking_creature->get_id()), current_map->get_location(attacked_creature->get_id()));
    TilePtr tile = MapUtils::get_adjacent_tile(current_map, attacking_creature, knockback_dir, 2);
    TilePtr next_tile = MapUtils::get_adjacent_tile(current_map, attacking_creature, knockback_dir, 3);
    ActionManager& am = game.get_action_manager_ref();

    if (MapUtils::is_tile_available_for_creature(attacked_creature, tile))
    {
      // If the creature was knocked back, and if it is appropriate to do so,
      // add a message.
      IMessageManager& manager = MM::instance(MessageTransmit::FOV, attacking_creature, GameUtils::is_player_among_creatures(attacking_creature, attacked_creature));
      string knock_back_msg = ActionTextKeys::get_knock_back_message(attacked_creature->get_description_sid(), attacked_creature->get_is_player());

      manager.add_new_message(knock_back_msg);
      manager.send();

      am.move(attacked_creature, knockback_dir, false);
      knocked_back = true;

      if (!attacked_creature->is_dead() && MapUtils::is_tile_available_for_creature(attacked_creature, next_tile))
      {
        am.move(attacked_creature, knockback_dir);
      }

      vector<string> statuses = { StatusIdentifiers::STATUS_ID_STUNNED, StatusIdentifiers::STATUS_ID_EXPOSED };

      for (const string& status_id : statuses)
      {
        string source_id = attacking_creature->get_id();
        StatusEffectPtr status_effect = StatusEffectFactory::create_status_effect(status_id, source_id);

        apply_damage_effect(attacked_creature, status_effect, 0, attacking_creature->get_level().get_current());
      }
    }
  }

  return knocked_back;
}

void CombatManager::gain_experience(CreaturePtr attacking_creature, CreaturePtr attacked_creature, MapPtr map)
{
  if (attacking_creature != nullptr && attacked_creature != nullptr)
  {
    ExperienceManager em;
    uint experience_value = attacked_creature->get_experience_value();
    em.gain_experience(attacking_creature, experience_value);

    string leader_id = attacking_creature->get_additional_property(CreatureProperties::CREATURE_PROPERTIES_LEADER_ID);

    if (!leader_id.empty())
    {
      CreaturePtr leader = map->get_creature(leader_id);

      if (leader != nullptr)
      {
        PacificationCalculator pc;
        double leader_proportion = pc.calculate_exp_proportion_follower_kill(leader);
        uint leader_exp = static_cast<uint>(experience_value * leader_proportion);

        if (leader_exp > 0)
        {
          em.gain_experience(leader, leader_exp);
        }
      }
    }
  }
}

Damage CombatManager::determine_damage(CreaturePtr attacking_creature, Damage* predefined_damage, DamageCalculator* damage_calculator)
{
  Damage damage;

  if (attacking_creature != nullptr)
  {
    if (predefined_damage)
    {
      damage = *predefined_damage;
    }
    else
    {
      damage = damage_calculator->calculate_base_damage_with_bonuses_or_penalties(attacking_creature);
    }

    string leader_id = attacking_creature->get_additional_property(CreatureProperties::CREATURE_PROPERTIES_LEADER_ID);

    if (!leader_id.empty())
    {
      DecisionStrategy* dec = attacking_creature->get_decision_strategy();

      if (dec != nullptr)
      {
        MapPtr fov_map = dec->get_fov_map();

        if (fov_map != nullptr)
        {
          CreaturePtr leader = fov_map->get_creature(leader_id);

          if (leader != nullptr)
          {
            PacificationCalculator pc;
            Damage leader_bonus = pc.calculate_follower_damage_bonus(leader);

            damage.set_modifier(damage.get_modifier() + leader_bonus.get_modifier());
          }
        }
      }
    }
  }

  return damage;
}

bool CombatManager::check_highlight_damage(CreaturePtr creature, const HitTypeEnum hit_type, const int damage_dealt)
{
  if (creature != nullptr && creature->get_is_player())
  {
    float f_dd = static_cast<float>(damage_dealt);
    Settings& settings = Game::instance().get_settings_ref();
    bool pause_on_crit = settings.get_setting_as_bool(Setting::HIGHLIGHT_ON_PC_CRITICAL_HIT);

    if (pause_on_crit && hit_type == HitTypeEnum::HIT_TYPE_CRITICAL && damage_dealt > 0)
    {
      return true;
    }

    int max_hp_dmg_pct = String::to_int(settings.get_setting(Setting::HIGHLIGHT_ON_PC_MAX_DAMAGE_PCT));
    Statistic hp = creature->get_hit_points();
    int hp_max = hp.get_base();

    if (max_hp_dmg_pct > 0)
    {
      int dmg_pct = static_cast<int>((f_dd / hp_max) * 100);

      if (dmg_pct >= max_hp_dmg_pct)
      {
        return true;
      }
    }

    int hp_below_pct = String::to_int(settings.get_setting(Setting::HIGHLIGHT_ON_PC_HP_BELOW_PCT));

    if (hp_below_pct > 0)
    {
      int cur_after_dmg = hp.get_current() - damage_dealt;
      int pct_after_dmg = static_cast<int>((static_cast<float>(cur_after_dmg) / hp_max) * 100);

      if (pct_after_dmg < hp_below_pct)
      {
        return true;
      }
    }
  }

  return false;
}

#ifdef UNIT_TESTS
#include "unit_tests/CombatManager_test.cpp"
#endif
