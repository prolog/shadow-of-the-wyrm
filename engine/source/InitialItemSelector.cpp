#include "InitialItemSelector.hpp"
#include "RNG.hpp"

using namespace std;

string InitialItemSelector::get_item_id(const string& race_id, const InitialItem& initial_item) const
{
  string base_id = initial_item.get_item_id();

  // If there is a random ID, it gets used first:
  string random_id = get_random_item_id(initial_item);
  
  if (!random_id.empty())
  {
    return random_id;
  }

  // If there is a racial ID, it overrides the base ID:
  string racial_id = get_racial_item_id(race_id, initial_item);

  if (!racial_id.empty())
  {
    return racial_id;
  }

  // There is neither a random ID nor a rcial ID, so return the base ID.
  return base_id;
}

// Pick one of the random IDs, well, at random.
string InitialItemSelector::get_random_item_id(const InitialItem& initial_item) const
{
  string random_id;

  vector<string> random_ids = initial_item.get_random_item_ids();

  if (!random_ids.empty())
  {
    random_id = random_ids.at(RNG::range(0, random_ids.size()-1));
  }

  return random_id;
}

// Pick the racial item ID that corresponds to the provided race ID.
// If it doesn't exist, return an empty string.
string InitialItemSelector::get_racial_item_id(const string& race_id, const InitialItem& initial_item) const
{
  string race_item_id;

  map<string, string> racial_ids = initial_item.get_racial_item_ids();
  map<string, string>::const_iterator i_it = racial_ids.find(race_id);

  if (i_it != racial_ids.end())
  {
    race_item_id = i_it->second;
  }

  return race_item_id;
}

#ifdef UNIT_TESTS
#include "unit_tests/InitialItemSelector_test.cpp"
#endif
