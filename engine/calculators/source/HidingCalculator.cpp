#include "HidingCalculator.hpp"
#include "MapUtils.hpp"

using namespace std;

int HidingCalculator::calculate_pct_chance_hide(CreaturePtr creature, MapPtr map) const
{
  int pct_chance_hide = 0;

  if (creature != nullptr && map != nullptr)
  {
    string creature_id = creature->get_id();

    // Get the creatures that can see the creature trying to hide.
    vector<string> creature_ids = MapUtils::get_creatures_with_creature_in_view(map, creature_id);

    if (creature_ids.empty())
    {
      pct_chance_hide = 100;
    }
    else
    {
      // ...
    }

    // Ensure the value is between 1 and 100.
    pct_chance_hide = std::min<int>(pct_chance_hide, 100);
    pct_chance_hide = std::max<int>(pct_chance_hide, 1);
  }

  return pct_chance_hide;
}

#ifdef UNIT_TESTS
#include "unit_tests/HidingCalculator_test.cpp"
#endif

