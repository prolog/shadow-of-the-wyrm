#include <algorithm>
#include <tuple>
#include "ItemDescriptionRandomizer.hpp"
#include "ItemIdentifier.hpp"
#include "RNG.hpp"

using namespace std;

typedef tuple<string, string, Colour> details_tuple;
typedef map<ItemType, vector<details_tuple>> RandomizedDescriptionMap;

ItemDescriptionRandomizer::ItemDescriptionRandomizer(const vector<ItemType>& randomize_types)
: types_to_randomize(randomize_types)
{
}

void ItemDescriptionRandomizer::randomize(ItemMap& items)
{
  bool type_inclusion[static_cast<int>(ItemType::ITEM_TYPE_LAST)] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  RandomizedDescriptionMap randomized_entries;

  // For each type to randomize, mark the appropriate location in the lookup
  // array as true, and add an entry to the map of randomized entries.
  for(const ItemType random_type : types_to_randomize)
  {
    type_inclusion[static_cast<int>(random_type)] = true;

    vector<details_tuple> randomized_item_descriptions;
    randomized_entries.insert(make_pair(random_type, randomized_item_descriptions));
  }

  ItemIdentifier ii;

  // First pass through ItemMap:
  // For each item in the item map, check its item type.  If the item type
  // is in the inclusion list for randomization, add the appropriate details
  // to the randomized entries.
  for (const ItemMap::value_type& item_pair : items)
  {
    ItemPtr item = item_pair.second;

    if (item)
    {
      ItemType item_type = item->get_type();
      int i_item_type = static_cast<int>(item_type);

      if ((type_inclusion[i_item_type] == true) && (!ii.get_item_identified(item->get_base_id())))
      {
        details_tuple unidentified_desc_sids_and_colour = make_tuple(item->get_unidentified_description_sid(), item->get_unidentified_usage_description_sid(), item->get_colour());
        vector<details_tuple>& item_type_descs = randomized_entries[item_type];
        item_type_descs.push_back(unidentified_desc_sids_and_colour);
      }
    }
  }

  // Now that each type to be randomized has a vector of unidentified string
  // IDs, shuffle them to get a random order.
  for (RandomizedDescriptionMap::value_type& rmap_pair : randomized_entries)
  {
    vector<details_tuple>& randomized_descs = rmap_pair.second;
    
    shuffle(randomized_descs.begin(), randomized_descs.end(), RNG::get_engine());
  }

  // Second pass through ItemMap:
  // If the item's type is in the inclusion set, grab the appropriate
  // randomized vector, select and remove the last element, and apply it to
  // the current item.
  for (const ItemMap::value_type& item_pair : items)
  {
    ItemPtr item = item_pair.second;

    if (item)
    {
      ItemType item_type = item->get_type();
      int i_item_type = static_cast<int>(item_type);

      if ((type_inclusion[i_item_type] == true) && (!ii.get_item_identified(item->get_base_id())))
      {
        vector<details_tuple>& item_type_descs_and_colour = randomized_entries[item_type];
        details_tuple item_descs_and_colour = item_type_descs_and_colour.back();
        item->set_unidentified_description_sid(get<0>(item_descs_and_colour));
        item->set_unidentified_usage_description_sid(get<1>(item_descs_and_colour));
        item->set_colour(get<2>(item_descs_and_colour));

        item_type_descs_and_colour.pop_back();
      }
    }
  }
}

