#include "Conversion.hpp"
#include "DisplayItem.hpp"
#include "DisplayItemColourTranslator.hpp"
#include "ItemDescriberFactory.hpp"
#include "ItemTranslator.hpp"
#include "StringTable.hpp"

using namespace std;

ItemTranslator::ItemTranslator()
{
}

ItemTranslator::~ItemTranslator()
{
}

DisplayItem ItemTranslator::create_display_item(const bool blind, const ItemPtr& item)
{
  DisplayItem display_item;
  ostringstream desc_ss;

  if (item)
  {
    IDescriberPtr item_describer = ItemDescriberFactory::create_item_describer(blind, item);
    string desc = item_describer->describe();
    
    string id = item->get_id();

    display_item.set_description(desc);
    display_item.set_id(id);

    DisplayItemColourTranslator dict;
    display_item.set_colour(dict.create_colour_for_display_item(item));
  }

  return display_item;
}
