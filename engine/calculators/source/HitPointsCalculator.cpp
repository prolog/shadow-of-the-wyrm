#include "HitPointsCalculator.hpp"

HitPointsCalculator::HitPointsCalculator()
{
}

HitPointsCalculator::~HitPointsCalculator()
{
}

// For each point of Health greater than 10, increase HP by 1.
int HitPointsCalculator::calculate_hit_points_bonus(const CreaturePtr& c)
{
  int hit_points_bonus = 0;

  if (c)
  {
    int health = c->get_health().get_current();

    if (health > 10)
    {
      hit_points_bonus = health - 10;
    }
  }

  return hit_points_bonus;
}

#ifdef UNIT_TESTS
#include "unit_tests/HitPointsCalculator_test.cpp"
#endif
