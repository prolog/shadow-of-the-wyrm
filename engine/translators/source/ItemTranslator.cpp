#include "Conversion.hpp"
#include "DisplayItem.hpp"
#include "ItemIdentifier.hpp"
#include "ItemTranslator.hpp"
#include "StringTable.hpp"

using std::string;

ItemTranslator::ItemTranslator()
{
}

ItemTranslator::~ItemTranslator()
{
}

DisplayItem ItemTranslator::create_display_item(const ItemPtr& item)
{
  DisplayItem display_item;

  if (item)
  {
    ItemIdentifier item_id;
    string item_description_sid = item_id.get_appropriate_description_sid(item->get_base_id());
    string display_item_description = StringTable::get(item_description_sid);
    
    uint quantity = item->get_quantity();
    
    if (quantity > 1)
    {
      display_item_description += " (" + Integer::to_string(quantity) + ")";
    }
    
    string id = item->get_id();

    display_item.set_description(display_item_description);
    display_item.set_id(id);
  }

  return display_item;
}
