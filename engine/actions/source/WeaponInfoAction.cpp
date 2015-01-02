#include "DamageCalculatorFactory.hpp"
#include "EquipmentTextKeys.hpp"
#include "MessageManagerFactory.hpp"
#include "RangedAttackSpeedCalculator.hpp"
#include "WeaponDifficultyCalculator.hpp"
#include "WeaponInfoAction.hpp"
#include "WeaponManager.hpp"

using std::string;
using std::dynamic_pointer_cast;

WeaponInfoAction::WeaponInfoAction()
{
}

// Get the weapon info for the given creature and given weapon style
ActionCostValue WeaponInfoAction::weapon_info(CreaturePtr creature, const WeaponStyle ws) const
{
  ActionCostValue action_cost_value = 0;
  
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
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
  
  if (creature)
  {
    Equipment& eq = creature->get_equipment();
    Damage base_damage = creature->get_base_damage();

    ItemPtr wielded_item = eq.get_item(EquipmentWornLocation::EQUIPMENT_WORN_WIELDED);
    WeaponPtr wielded_weapon = dynamic_pointer_cast<Weapon>(wielded_item);

    ItemPtr off_hand_item = eq.get_item(EquipmentWornLocation::EQUIPMENT_WORN_OFF_HAND);
    WeaponPtr off_hand_weapon = dynamic_pointer_cast<Weapon>(off_hand_item);
    
    string wielded_weapon_text = get_melee_weapon_info(creature, wielded_weapon, AttackType::ATTACK_TYPE_MELEE_PRIMARY, base_damage);
    string off_hand_weapon_text = get_melee_weapon_info(creature, off_hand_weapon, AttackType::ATTACK_TYPE_MELEE_SECONDARY, base_damage);
    
    manager.add_new_message(wielded_weapon_text);
    manager.add_new_message(off_hand_weapon_text);
    manager.send();
  }

  return get_action_cost_value(creature);
}

ActionCostValue WeaponInfoAction::ranged_weapon_info(CreaturePtr creature) const
{
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
  
  if (creature)
  {
    Equipment& eq = creature->get_equipment();
    ItemPtr ranged_item = eq.get_item(EquipmentWornLocation::EQUIPMENT_WORN_RANGED_WEAPON);
    ItemPtr ammunition_item = eq.get_item(EquipmentWornLocation::EQUIPMENT_WORN_AMMUNITION);
    
    WeaponPtr ranged_weapon = dynamic_pointer_cast<Weapon>(ranged_item);
    WeaponPtr ammunition = dynamic_pointer_cast<Weapon>(ammunition_item);
    
    string ranged_weapon_text = get_ranged_weapon_info(creature, ranged_weapon, ammunition);
    
    manager.add_new_message(ranged_weapon_text);
    manager.send();
  }
  
  return get_action_cost_value(creature);
}

// Get the UI string for either the primary or off-hand weapon.
string WeaponInfoAction::get_melee_weapon_info(CreaturePtr creature, WeaponPtr weapon, const AttackType attack_type, const Damage& damage) const
{
  string melee_info;

  // Always display the info for the primary slot (it may not hold a weapon - that's fine, that's considered
  // unarmed).
  if (weapon || (attack_type == AttackType::ATTACK_TYPE_MELEE_PRIMARY))
  {
    DamageCalculatorPtr damage_calc = DamageCalculatorFactory::create_damage_calculator(attack_type);
    WeaponDifficultyCalculator wdc;

    int base_difficulty = wdc.calculate_base_difficulty(creature, attack_type);
    int total_difficulty = wdc.calculate_total_difficulty_for_display(creature, attack_type);

    Damage weapon_damage = damage_calc->calculate_base_damage_with_bonuses_or_penalties(creature);
    
    int speed = 0;
    if (weapon)
    {
      speed = weapon->get_speed();
    }

    melee_info = EquipmentTextKeys::get_melee_weapon_synopsis(attack_type, weapon, base_difficulty, total_difficulty, speed, weapon_damage);
  }
  
  return melee_info;
}

string WeaponInfoAction::get_ranged_weapon_info(CreaturePtr creature, WeaponPtr ranged_weapon, WeaponPtr ammunition) const
{
  string ranged_weapon_synopsis; // The overall message
  string ranged_attack_info; // The message about difficulty, damage, and so on.

  if (ranged_weapon || ammunition)
  {
    DamageCalculatorPtr damage_calculator = DamageCalculatorFactory::create_damage_calculator(AttackType::ATTACK_TYPE_RANGED);
    WeaponDifficultyCalculator wdc;

    int base_difficulty = wdc.calculate_base_difficulty(creature, AttackType::ATTACK_TYPE_RANGED);
    int total_difficulty = wdc.calculate_total_difficulty_for_display(creature, AttackType::ATTACK_TYPE_RANGED);
    Damage ranged_damage = damage_calculator->calculate_base_damage_with_bonuses_or_penalties(creature);
    
    RangedAttackSpeedCalculator rasc;
    int speed = rasc.calculate(creature);
    
    ranged_attack_info = EquipmentTextKeys::get_weapon_difficulty_speed_and_damage_synopsis(base_difficulty, total_difficulty, speed, ranged_damage);
  }
  
  return EquipmentTextKeys::get_ranged_weapon_synopsis(ranged_weapon, ammunition, ranged_attack_info);
}

// Getting weapon info is always no-cost
ActionCostValue WeaponInfoAction::get_action_cost_value(CreaturePtr creature) const
{
  return 0;
}
