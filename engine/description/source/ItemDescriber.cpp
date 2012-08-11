#include "ItemDescriber.hpp"
#include "StringTable.hpp"

using std::string;

ItemDescriber::ItemDescriber(ItemPtr new_item)
: item(new_item)
{
}

string ItemDescriber::describe() const
{
  string item_description;

  if (item)
  {
    item_description = StringTable::get(item->get_usage_description_sid());
  }

  return item_description;
}

