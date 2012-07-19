#include <boost/foreach.hpp>
#include "EvadeCalculator.hpp"
#include "Wearable.hpp"

using boost::dynamic_pointer_cast;

EvadeCalculator::EvadeCalculator()
{
}

EvadeCalculator::~EvadeCalculator()
{
}

// Evade = equipment bonuses/penalties
//       + 1 point for every two points of Agility over 10
//       - 1 point for every two points of Agility under 10
//       + 1 point for every 5 points of Valour under 50
//       - 1 point for every 5 points of Valour over 50
int EvadeCalculator::calculate_evade(const CreaturePtr& c)
{
  int evade = 0;
  
  if (c)
  {
    evade = c->get_base_evade().get_current();
    
    int agility = c->get_agility().get_current();
    int valour  = c->get_valour().get_current();

    int agility_bonus = (agility - 10) / 2;
    int valour_bonus = (valour - 50) / 5;
    
    evade += get_equipment_bonus(c);
    evade += agility_bonus;
    evade -= valour_bonus;
  }
  
  return evade;
}

int EvadeCalculator::get_equipment_bonus(const CreaturePtr& c)
{
  int equipment_evade_bonus = 0;
  
  Equipment& eq = c->get_equipment();
  EquipmentMap equipment = eq.get_equipment();
  
  BOOST_FOREACH(EquipmentMap::value_type& item, equipment)
  {
    WearablePtr equipped = dynamic_pointer_cast<Wearable>(item.second);
    
    if (equipped)
    {
      equipment_evade_bonus += equipped->get_evade();
    }
  }
  
  return equipment_evade_bonus;
}

#ifdef UNIT_TESTS
#include "unit_tests/EvadeCalculator_test.cpp"
#endif
