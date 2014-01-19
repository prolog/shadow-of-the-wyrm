#include "CreatureToHitCalculator.hpp"
#include "Wearable.hpp"

using std::string;
using std::dynamic_pointer_cast;

// Creature to-hit = equipment bonuses/penalties
int CreatureToHitCalculator::calculate_to_hit(CreaturePtr c)
{
  int to_hit = 0;
  
  if (c != nullptr)
  {
    to_hit += get_equipment_bonus(c);
  }
  
  return to_hit;
}

int CreatureToHitCalculator::get_equipment_bonus(const CreaturePtr c)
{
  int equipment_to_hit_bonus = 0;
  
  Equipment& eq = c->get_equipment();
  EquipmentMap equipment = eq.get_equipment();
  
  for(EquipmentMap::value_type& item : equipment)
  {
    WearablePtr equipped = dynamic_pointer_cast<Wearable>(item.second);
    
    if (equipped)
    {
      equipment_to_hit_bonus += equipped->get_to_hit();
    }
  }
  
  return equipment_to_hit_bonus;
}

#ifdef UNIT_TESTS
#include "unit_tests/CreatureToHitCalculator_test.cpp"
#endif

