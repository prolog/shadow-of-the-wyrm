#include "ItemBreakageCalculator.hpp"
#include "Conversion.hpp"
#include "ItemProperties.hpp"

using namespace std;

const int ItemBreakageCalculator::BASE_PCT_CHANCE_DIGGING_BREAKAGE = 50;

int ItemBreakageCalculator::calculate_pct_chance_digging_breakage(ItemPtr item)
{
  int result = BASE_PCT_CHANCE_DIGGING_BREAKAGE;

  if (item != nullptr)
  {
    string breakage_pct_chance = item->get_additional_property(ItemProperties::ITEM_PROPERTIES_DIG_BREAKAGE_PCT_CHANCE);

    if (!breakage_pct_chance.empty())
    {
      result = String::to_int(breakage_pct_chance);
    }
  }

  pair<bool, int> override = get_override_pct_chance_breakage(item);

  if (override.first == true)
  {
    result = override.second;
  }

  return result;
}

pair<bool, int> ItemBreakageCalculator::get_override_pct_chance_breakage(ItemPtr item)
{
  pair<bool, int> result = make_pair(false, 0);

  if (item != nullptr)
  {
    if (item->get_artifact())
    {
      // Artifacts can't be broken!
      result = make_pair(true, 0);
    }
  }

  return result;
}
