#include "InitialItemSelector.hpp"
#include "RNG.hpp"

using namespace std;

pair<string, uint> InitialItemSelector::get_item_details(const string& race_id, const InitialItem& initial_item) const
{
  string base_id = initial_item.get_item_id();
  uint quantity = RNG::dice(initial_item.get_item_quantity());

  // If there is a random ID, it gets used first:
  pair<string, uint> details = get_random_item_details(initial_item);
  
  if (!details.first.empty())
  {
    return details;
  }

  // If there is a racial ID, it overrides the base ID:
  details = get_racial_item_details(race_id, initial_item);

  if (!details.first.empty())
  {
    return details;
  }

  // There is neither a random ID nor a rcial ID, so return the base ID.
  details = make_pair(base_id, quantity);
  return details;
}

// Pick one of the random IDs, well, at random.
pair<string, uint> InitialItemSelector::get_random_item_details(const InitialItem& initial_item) const
{
  pair<string, uint> random_details;

  vector<pair<string, Dice>> random_iis = initial_item.get_random_item_ids();

  if (!random_iis.empty())
  {
    pair<string, Dice> random_ii = random_iis.at(RNG::range(0, random_iis.size()-1));
    
    random_details.first = random_ii.first;
    random_details.second = RNG::dice(random_ii.second);
  }

  return random_details;
}

// Pick the racial item ID that corresponds to the provided race ID.
// If it doesn't exist, return an empty string.
pair<string, uint> InitialItemSelector::get_racial_item_details(const string& race_id, const InitialItem& initial_item) const
{
  pair<string, uint> race_item_details;

  map<string, pair<string, Dice>> racial_ids = initial_item.get_racial_item_ids();
  map<string, pair<string, Dice>>::const_iterator i_it = racial_ids.find(race_id);

  if (i_it != racial_ids.end())
  {
    race_item_details.first = i_it->second.first;
    race_item_details.second = RNG::dice(i_it->second.second);
  }

  return race_item_details;
}

#ifdef UNIT_TESTS
#include "unit_tests/InitialItemSelector_test.cpp"
#endif
