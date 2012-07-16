#include "SoakCalculator.hpp"

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

    soak += health_bonus;
  }

  return soak;
}

#ifdef UNIT_TESTS
#include "unit_tests/SoakCalculator_test.cpp"
#endif
