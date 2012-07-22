#include <boost/foreach.hpp>
#include "SoakCalculator.hpp"
#include "Wearable.hpp"

using boost::dynamic_pointer_cast;

SoakCalculator::SoakCalculator()
{
}

SoakCalculator::~SoakCalculator()
{
}

// A creature gets 1 point of Soak for every 4 Health over 10,
// plus any bonuses or penalties from equipment.
int SoakCalculator::calculate_soak(const CreaturePtr& c)
{
  int soak = 0;

  if (c)
  {
    soak = c->get_base_soak().get_current();
    
    int health = c->get_health().get_current();
    int health_bonus = 0;

    if (health > 10)
    {
      health_bonus = (health - 10) / 4;
    }

    soak += get_equipment_bonus(c);
    soak += health_bonus;
  }

  return soak;
}

int SoakCalculator::get_equipment_bonus(const CreaturePtr& c)
{
  int equipment_evade_bonus = 0;
  
  Equipment& eq = c->get_equipment();
  EquipmentMap equipment = eq.get_equipment();
  
  BOOST_FOREACH(EquipmentMap::value_type& item, equipment)
  {
    WearablePtr equipped = dynamic_pointer_cast<Wearable>(item.second);
    
    if (equipped)
    {
      equipment_evade_bonus += equipped->get_soak();
    }
  }
  
  return equipment_evade_bonus;
}

#ifdef UNIT_TESTS
#include "unit_tests/SoakCalculator_test.cpp"
#endif
