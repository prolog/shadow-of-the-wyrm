#include "ArcanaPointsCalculator.hpp"

ArcanaPointsCalculator::ArcanaPointsCalculator()
{
}

ArcanaPointsCalculator::~ArcanaPointsCalculator()
{
}

// A creature gets +1 to Arcana Points for:
// - Every 2 points of Intelligence over 10
// - Every 4 points of Willpower over 10
int ArcanaPointsCalculator::calculate_arcana_points_bonus(const CreaturePtr& c)
{
  int arcana_points_bonus = 0;

  if (c)
  {
    int intelligence = c->get_intelligence().get_current();
    int willpower    = c->get_willpower().get_current();

    if (intelligence > 10)
    {
      intelligence -= 10;
      arcana_points_bonus += (intelligence / 2);
    }

    if (willpower > 10)
    {
      willpower -= 10;
      arcana_points_bonus += (willpower / 4);
    }
  }

  return arcana_points_bonus;
}

#ifdef UNIT_TESTS
#include "unit_tests/ArcanaPointsCalculator_test.cpp"
#endif
