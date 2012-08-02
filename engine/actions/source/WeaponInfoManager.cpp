#include "DamageCalculatorFactory.hpp"
#include "MessageManager.hpp"
#include "StringConstants.hpp"
#include "WeaponDifficultyCalculator.hpp"
#include "WeaponInfoManager.hpp"
#include "WeaponManager.hpp"

using std::string;
using boost::dynamic_pointer_cast;

WeaponInfoManager::WeaponInfoManager()
{
}

// Get the actual melee weapon info.  Output it to the message manager if the
// creature is the player.
ActionCostValue WeaponInfoManager::melee_weapon_info(CreaturePtr creature) const
{
  MessageManager* manager = MessageManager::instance();
  
  if (creature && manager)
  {
    Equipment& eq = creature->get_equipment();
    Damage base_damage = creature->get_base_damage();

    ItemPtr wielded_item = eq.get_item(EQUIPMENT_WORN_WIELDED);
    WeaponPtr wielded_weapon = dynamic_pointer_cast<Weapon>(wielded_item);

    ItemPtr off_hand_item = eq.get_item(EQUIPMENT_WORN_OFF_HAND);
    WeaponPtr off_hand_weapon = dynamic_pointer_cast<Weapon>(off_hand_item);
    
    string wielded_weapon_text = get_melee_weapon_info(creature, wielded_weapon, ATTACK_TYPE_MELEE_PRIMARY, base_damage);
    string off_hand_weapon_text = get_melee_weapon_info(creature, off_hand_weapon, ATTACK_TYPE_MELEE_SECONDARY, base_damage);
    
    // JCD FIXME: Do something here to get them on separate lines, if necessary.
    // Test...
    manager->add_new_message(wielded_weapon_text);
    manager->add_new_message(off_hand_weapon_text);
    manager->send();
  }

  return get_action_cost_value();
}

ActionCostValue WeaponInfoManager::ranged_weapon_info(CreaturePtr creature) const
{
  MessageManager* manager = MessageManager::instance();
  
  if (creature && manager)
  {
    Equipment& eq = creature->get_equipment();
    ItemPtr ranged_item = eq.get_item(EQUIPMENT_WORN_RANGED_WEAPON);
    ItemPtr ammunition_item = eq.get_item(EQUIPMENT_WORN_AMMUNITION);
    
    WeaponPtr ranged_weapon = dynamic_pointer_cast<Weapon>(ranged_item);
    WeaponPtr ammunition = dynamic_pointer_cast<Weapon>(ammunition_item);
    
    string ranged_weapon_text = get_ranged_weapon_info(creature, ranged_weapon, ammunition);
    
    manager->add_new_message(ranged_weapon_text);
    manager->send();
  }
  
  return get_action_cost_value();
}

// Get the UI string for either the primary or off-hand weapon.
string WeaponInfoManager::get_melee_weapon_info(CreaturePtr creature, WeaponPtr weapon, const AttackType attack_type, const Damage& damage) const
{
  string melee_info;

  // Always display the info for the primary slot (it may not hold a weapon - that's fine, that's considered
  // unarmed).
  if (weapon || (attack_type == ATTACK_TYPE_MELEE_PRIMARY))
  {
    DamageCalculatorPtr damage_calc = DamageCalculatorFactory::create_damage_calculator(attack_type);
    WeaponDifficultyCalculator wdc;
    
    int difficulty = wdc.calculate(creature, attack_type);
    Damage weapon_damage = damage_calc->calculate_base_damage_with_bonuses_or_penalties(creature);

    melee_info = EquipmentTextKeys::get_melee_weapon_synopsis(attack_type, weapon, difficulty, weapon_damage);
  }
  
  return melee_info;
}

string WeaponInfoManager::get_ranged_weapon_info(CreaturePtr creature, WeaponPtr ranged_weapon, WeaponPtr ammunition) const
{
  string ranged_weapon_synopsis; // The overall message
  string ranged_attack_info; // The message about difficulty, damage, and so on.

  if (ranged_weapon || ammunition)
  {
    DamageCalculatorPtr damage_calculator = DamageCalculatorFactory::create_damage_calculator(ATTACK_TYPE_RANGED);
    WeaponDifficultyCalculator wdc;

    int difficulty = wdc.calculate(creature, ATTACK_TYPE_RANGED);
    Damage ranged_damage = damage_calculator->calculate_base_damage_with_bonuses_or_penalties(creature);
    
    ranged_attack_info = EquipmentTextKeys::get_weapon_difficulty_and_damage_synopsis(difficulty, ranged_damage);
  }
  
  return EquipmentTextKeys::get_ranged_weapon_synopsis(ranged_weapon, ammunition, ranged_attack_info);
}

// Getting weapon info is always no-cost
ActionCostValue WeaponInfoManager::get_action_cost_value() const
{
  return 0;
}
