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

    ItemPtr right_item = eq.get_item(EQUIPMENT_WORN_RIGHT_HAND);
    WeaponPtr right_weapon = dynamic_pointer_cast<Weapon>(right_item);

    ItemPtr left_item = eq.get_item(EQUIPMENT_WORN_LEFT_HAND);
    WeaponPtr left_weapon = dynamic_pointer_cast<Weapon>(left_item);
    
    string right_hand_weapon_text = get_melee_weapon_info(right_weapon, base_damage);
    string left_hand_weapon_text = get_melee_weapon_info(left_weapon, base_damage);
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

string WeaponInfoManager::get_melee_weapon_info(WeaponPtr weapon, const Damage& damage) const
{
  return "";
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
    Damage ranged_damage = damage_calculator->calculate_base_damage_object(creature);
    
    ranged_attack_info = EquipmentTextKeys::get_weapon_difficulty_and_damage_synopsis(difficulty, ranged_damage);
  }
  
  return EquipmentTextKeys::get_ranged_weapon_synopsis(ranged_weapon, ammunition, ranged_attack_info);
}

// Getting weapon info is always no-cost
ActionCostValue WeaponInfoManager::get_action_cost_value() const
{
  return 0;
}
