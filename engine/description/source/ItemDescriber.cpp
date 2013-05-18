#include "Conversion.hpp"
#include "ItemDescriber.hpp"
#include "ItemIdentifier.hpp"
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
    ItemIdentifier item_id;
    item_description = item_id.get_appropriate_usage_description(item);
    
    uint quantity = item->get_quantity();
    
    if (quantity > 1)
    {
      item_description += " (" + Integer::to_string(quantity) + ")";
    }
  }

  return item_description;
}

