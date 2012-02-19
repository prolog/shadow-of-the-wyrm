#include "DisplayItem.hpp"
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
    string item_description_sid = item->get_description_sid();
    string display_item_description = StringTable::get(item_description_sid);
    display_item.set_description(display_item_description);
  }

  return display_item;
}
