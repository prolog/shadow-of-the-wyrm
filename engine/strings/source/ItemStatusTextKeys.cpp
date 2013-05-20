#include <boost/algorithm/string/replace.hpp>
#include "ItemStatusTextKeys.hpp"
#include "StringTable.hpp"

using namespace std;

ItemStatusTextKeys::ItemStatusTextKeys()
{
  if (item_status_string_map.empty()) initialize_item_status_string_map();
}

void ItemStatusTextKeys::initialize_item_status_string_map()
{
  item_status_string_map.clear();

  item_status_string_map.insert(make_pair(ITEM_STATUS_BLESSED, ItemStatusTextKeys::STATUS_BLESSED));
  item_status_string_map.insert(make_pair(ITEM_STATUS_UNCURSED, ItemStatusTextKeys::STATUS_UNCURSED));
  item_status_string_map.insert(make_pair(ITEM_STATUS_CURSED, ItemStatusTextKeys::STATUS_CURSED));
}

const string ItemStatusTextKeys::STATUS_BLESSED = "ITEM_STATUS_BLESSED";
const string ItemStatusTextKeys::STATUS_UNCURSED = "ITEM_STATUS_UNCURSED";
const string ItemStatusTextKeys::STATUS_CURSED = "ITEM_STATUS_CURSED";

const string ItemStatusTextKeys::ITEM_STATUS_AND_DESCRIPTION = "ITEM_STATUS_AND_DESCRIPTION";

string ItemStatusTextKeys::get_item_status_and_description(const ItemStatus item_status, const string& item_desc)
{
  string formatted_item_desc = StringTable::get(ItemStatusTextKeys::ITEM_STATUS_AND_DESCRIPTION);
  string status_sid = item_status_string_map[item_status];

  // add the status into the string
  boost::replace_first(formatted_item_desc, "%s1", StringTable::get(status_sid));

  // add the provided description into the string
  boost::replace_first(formatted_item_desc, "%s2", item_desc);

  return formatted_item_desc;
};