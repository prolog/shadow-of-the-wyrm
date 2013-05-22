#include <algorithm>
#include <boost/foreach.hpp>
#include "ItemDescriptionRandomizer.hpp"
#include "RNG.hpp"

using namespace std;

typedef map<ItemType, vector<pair<string, string>>> RandomizedDescriptionMap;

ItemDescriptionRandomizer::ItemDescriptionRandomizer(const vector<ItemType>& randomize_types)
: types_to_randomize(randomize_types)
{
}

void ItemDescriptionRandomizer::randomize(ItemMap& items)
{
  bool type_inclusion[ITEM_TYPE_LAST] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  RandomizedDescriptionMap randomized_entries;

  // For each type to randomize, mark the appropriate location in the lookup
  // array as true, and add an entry to the map of randomized entries.
  BOOST_FOREACH(ItemType random_type, types_to_randomize)
  {
    type_inclusion[random_type] = true;

    vector<pair<string, string>> randomized_item_descriptions;
    randomized_entries.insert(make_pair(random_type, randomized_item_descriptions));
  }

  // First pass through ItemMap:
  // For each item in the item map, check its item type.  If the item type
  // is in the inclusion list for randomization, add the appropriate details
  // to the randomized entries.
  BOOST_FOREACH(ItemMap::value_type& item_pair, items)
  {
    ItemPtr item = item_pair.second;

    if (item)
    {
      ItemType item_type = item->get_type();
      
      if (type_inclusion[item_type] == true)
      {
        pair<string,string> unidentified_desc_sids(item->get_unidentified_description_sid(), item->get_unidentified_usage_description_sid());
        vector<pair<string,string>>& item_type_descs = randomized_entries[item_type];
        item_type_descs.push_back(unidentified_desc_sids);
      }
    }
  }

  // Now that each type to be randomized has a vector of unidentified string
  // IDs, shuffle them to get a random order.
  BOOST_FOREACH(RandomizedDescriptionMap::value_type& rmap_pair, randomized_entries)
  {
    vector<pair<string,string>>& randomized_descs = rmap_pair.second;
    
    random_shuffle(randomized_descs.begin(), randomized_descs.end(), RNG::get_generator());
  }

  // Second pass through ItemMap:
  // If the item's type is in the inclusion set, grab the appropriate
  // randomized vector, select and remove the last element, and apply it to
  // the current item.
  BOOST_FOREACH(ItemMap::value_type& item_pair, items)
  {
    ItemPtr item = item_pair.second;

    if (item)
    {
      ItemType item_type = item->get_type();

      if (type_inclusion[item_type] == true)
      {
        vector<pair<string,string>>& item_type_descs = randomized_entries[item_type];
        pair<string,string> item_descs = item_type_descs.back();
        item->set_unidentified_description_sid(item_descs.first);
        item->set_unidentified_usage_description_sid(item_descs.second);

        item_type_descs.pop_back();
      }
    }
  }
}

