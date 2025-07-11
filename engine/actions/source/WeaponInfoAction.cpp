#include "AttackSpeedCalculatorFactory.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "DamageCalculatorFactory.hpp"
#include "EquipmentTextKeys.hpp"
#include "Game.hpp"
#include "MeleeWeaponRangeCalculator.hpp"
#include "MessageManagerFactory.hpp"
#include "PhaseOfMoonCalculator.hpp"
#include "RangedAttackSpeedCalculator.hpp"
#include "WeaponDifficultyCalculator.hpp"
#include "WeaponInfoAction.hpp"
#include "WeaponManager.hpp"

using namespace std;

WeaponInfoAction::WeaponInfoAction()
{
}

// Get the weapon info for the given creature and given weapon style
ActionCostValue WeaponInfoAction::weapon_info(CreaturePtr creature, const WeaponStyle ws) const
{
  ActionCostValue action_cost_value = ActionCostConstants::NO_ACTION;
  
  if (creature)
  {
    switch(ws)
    {
      case WeaponStyle::WEAPON_STYLE_MELEE:
        action_cost_value = melee_weapon_info(creature);
        break;
      case WeaponStyle::WEAPON_STYLE_RANGED:
        action_cost_value = ranged_weapon_info(creature);
        break;
      default:
        break;
    }    
  }
  
  return action_cost_value;
}

// Get the actual melee weapon info.  Output it to the message manager if the
// creature is the player.
ActionCostValue WeaponInfoAction::melee_weapon_info(CreaturePtr creature) const
{
  IMessageManager& manager = MMF::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
  
  if (creature)
  {
    pair<string, string> wielded_offhand_text = get_wielded_and_offhand_text(creature);
    string wielded_text = wielded_offhand_text.first;
    string offhand_text = wielded_offhand_text.second;
        
    manager.add_new_message(wielded_text);
    manager.add_new_message(offhand_text);
    manager.send();
  }

  return get_action_cost_value(creature);
}

ActionCostValue WeaponInfoAction::ranged_weapon_info(CreaturePtr creature) const
{
  IMessageManager& manager = MMF::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
  
  if (creature)
  {
    string ranged_text = get_ranged_text(creature);
    
    manager.add_new_message(ranged_text);
    manager.send();
  }
  
  return get_action_cost_value(creature);
}

pair<string, string> WeaponInfoAction::get_wielded_and_offhand_text(CreaturePtr creature) const
{
  pair<string, string> wo_text;

  if (creature != nullptr)
  {
    WeaponManager wm;

    WeaponPtr wielded_weapon = wm.get_weapon(creature, AttackType::ATTACK_TYPE_MELEE_PRIMARY);
    WeaponPtr off_hand_weapon = wm.get_weapon(creature, AttackType::ATTACK_TYPE_MELEE_SECONDARY);

    wo_text.first = get_melee_weapon_info(creature, wielded_weapon, AttackType::ATTACK_TYPE_MELEE_PRIMARY);
    wo_text.second = get_melee_weapon_info(creature, off_hand_weapon, AttackType::ATTACK_TYPE_MELEE_SECONDARY);
  }

  return wo_text;
}

string WeaponInfoAction::get_ranged_text(CreaturePtr creature) const
{
  string ranged_weapon_text;

  if (creature != nullptr)
  {
    Equipment& eq = creature->get_equipment();
    ItemPtr ranged_item = eq.get_item(EquipmentWornLocation::EQUIPMENT_WORN_RANGED_WEAPON);
    ItemPtr ammunition_item = eq.get_item(EquipmentWornLocation::EQUIPMENT_WORN_AMMUNITION);

    WeaponPtr ranged_weapon = dynamic_pointer_cast<Weapon>(ranged_item);
    WeaponPtr ammunition = dynamic_pointer_cast<Weapon>(ammunition_item);

    ranged_weapon_text = get_ranged_weapon_info(creature, ranged_weapon, ammunition);
  }

  return ranged_weapon_text;
}

// Get the UI string for either the primary or off-hand weapon.
string WeaponInfoAction::get_melee_weapon_info(CreaturePtr creature, WeaponPtr weapon, const AttackType attack_type) const
{
  string melee_info;

  CurrentCreatureAbilities cca;
  bool blind = !cca.can_see(creature);
  
  if (blind && (weapon && !weapon->get_glowing()))
  {
    melee_info = StringTable::get(EquipmentTextKeys::EQUIPMENT_WIELDED_UNSURE);
  }
  else
  {
    // Always display the info for the primary slot (it may not hold a weapon - that's fine, that's considered
    // unarmed).
    if (weapon || (attack_type == AttackType::ATTACK_TYPE_MELEE_PRIMARY))
    {
      Game& game = Game::instance();
      PhaseOfMoonCalculator pomc;
      PhaseOfMoonType phase = pomc.calculate_phase_of_moon(game.get_current_world()->get_calendar().get_seconds());
      DamageCalculatorPtr damage_calc = DamageCalculatorFactory::create_damage_calculator(attack_type, phase);
      WeaponDifficultyCalculator wdc;

      int base_difficulty = wdc.calculate_base_difficulty(creature, attack_type);
      int total_difficulty = wdc.calculate_total_difficulty_for_display(creature, attack_type);

      Damage weapon_damage = damage_calc->calculate_base_damage_with_bonuses_or_penalties(creature);

      int speed = 0;
      int range = 1;

      if (creature)
      {
        MeleeWeaponRangeCalculator mwrc;
        range = mwrc.get_primary_melee_range(creature);
      }
      
      if (weapon)
      {
        AttackSpeedCalculatorPtr sc = AttackSpeedCalculatorFactory::create_speed_calculator(attack_type);
        speed = sc->calculate(creature);
      }

      melee_info = EquipmentTextKeys::get_melee_weapon_synopsis(attack_type, weapon, base_difficulty, total_difficulty, speed, weapon_damage, range);
    }
  }

  return melee_info;
}

string WeaponInfoAction::get_ranged_weapon_info(CreaturePtr creature, WeaponPtr ranged_weapon, WeaponPtr ammunition) const
{
  string ranged_weapon_synopsis; // The overall message
  string ranged_attack_info; // The message about difficulty, damage, and so on.

  CurrentCreatureAbilities cca;
  bool blind = !cca.can_see(creature);

  if (blind && ((ranged_weapon && !ranged_weapon->get_glowing()) || (ammunition && !ammunition->get_glowing())))
  {
    ranged_attack_info = StringTable::get(EquipmentTextKeys::EQUIPMENT_WIELDED_UNSURE);
  }
  else
  {
    if (ranged_weapon || ammunition)
    {
      Game& game = Game::instance();
      PhaseOfMoonCalculator pomc;
      PhaseOfMoonType phase = pomc.calculate_phase_of_moon(game.get_current_world()->get_calendar().get_seconds());

      DamageCalculatorPtr damage_calculator = DamageCalculatorFactory::create_damage_calculator(AttackType::ATTACK_TYPE_RANGED, phase);
      WeaponDifficultyCalculator wdc;

      int base_difficulty = wdc.calculate_base_difficulty(creature, AttackType::ATTACK_TYPE_RANGED);
      int total_difficulty = wdc.calculate_total_difficulty_for_display(creature, AttackType::ATTACK_TYPE_RANGED);
      Damage ranged_damage = damage_calculator->calculate_base_damage_with_bonuses_or_penalties(creature);

      RangedAttackSpeedCalculator rasc;
      int speed = rasc.calculate(creature);

      ranged_attack_info = EquipmentTextKeys::get_weapon_difficulty_speed_and_damage_synopsis(base_difficulty, total_difficulty, speed, ranged_damage);
    }

    ranged_attack_info = EquipmentTextKeys::get_ranged_weapon_synopsis(ranged_weapon, ammunition, ranged_attack_info);
  }

  return ranged_attack_info;
}

// Getting weapon info is always no-cost
ActionCostValue WeaponInfoAction::get_action_cost_value(CreaturePtr /* creature */) const
{
  return 0;
}
