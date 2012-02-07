#include "EvadeCalculator.hpp"

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
    int agility = c->get_agility().get_current();
    int valour  = c->get_valour().get_current();

    int agility_bonus = (agility - 10) / 2;
    int valour_bonus = (valour - 50) / 5;
    
    evade += agility_bonus;
    evade -= valour_bonus;
  }
  
  return evade;
}

#ifdef UNIT_TESTS
#include "unit_tests/EvadeCalculator_test.cpp"
#endif
