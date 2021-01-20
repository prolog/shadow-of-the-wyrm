#include <cmath>
#include "FollowerCalculator.hpp"

using namespace std;

const int FollowerCalculator::BASE_X_ADVENTURER = 1;
const int FollowerCalculator::BASE_X_HIRELING = 1;
const int FollowerCalculator::BASE_Y_ADVENTURER = 20;
const int FollowerCalculator::BASE_Y_HIRELING = 10;

pair<int, int> FollowerCalculator::calculate_x_in_y_chance_adventurer(const Depth& d) const
{
  pair<int, int> odds = { BASE_X_ADVENTURER, BASE_Y_ADVENTURER };
  int depth = d.get_current();
  
  // It becomes exponentially unlikely to run into adventurers the lower you go.
  if (depth > 0)
  {
    odds.second = static_cast<int>(pow(odds.second, depth));
  }

  return odds;
}

pair<int, int> FollowerCalculator::calculate_x_in_y_chance_hireling(const Depth& d) const
{
  pair<int, int> odds = { BASE_X_HIRELING, BASE_Y_HIRELING };
  int depth = d.get_current();

  // Hirelings only naturally appear underground.
  if (depth > 0)
  {
    odds.second *= depth;
  }
  else
  {
    odds.second = 0;
  }
  return odds;
}

#ifdef UNIT_TESTS
#include "unit_tests/FollowerCalculator_test.cpp"
#endif
