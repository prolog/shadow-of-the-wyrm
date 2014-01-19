#include "CreatureAdditionalDamageCalculator.hpp"
#include "Wearable.hpp"

using std::string;
using std::dynamic_pointer_cast;

// Creature add'l daamge = equipment bonuses/penalties
int CreatureAdditionalDamageCalculator::calculate_additional_damage(CreaturePtr c)
{
  int addl_damage = 0;
  
  if (c)
  {
    addl_damage += get_equipment_bonus(c);
  }
  
  return addl_damage;
}

int CreatureAdditionalDamageCalculator::get_equipment_bonus(CreaturePtr c)
{
  int equipment_addl_damage_bonus = 0;
  
  Equipment& eq = c->get_equipment();
  EquipmentMap equipment = eq.get_equipment();
  
  for(EquipmentMap::value_type& item : equipment)
  {
    WearablePtr equipped = dynamic_pointer_cast<Wearable>(item.second);
    
    if (equipped)
    {
      equipment_addl_damage_bonus += equipped->get_addl_damage();
    }
  }
  
  return equipment_addl_damage_bonus;
}

#ifdef UNIT_TESTS
#include "unit_tests/CreatureAdditionalDamageCalculator_test.cpp"
#endif
