#include "Conversion.hpp"
#include "DisplayItem.hpp"
#include "DisplayItemColourTranslator.hpp"
#include "ItemDescriberFactory.hpp"
#include "ItemTextKeys.hpp"
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
    ItemDescriberPtr item_describer = ItemDescriberFactory::create_item_describer(blind, item);
    string desc = item_describer->describe();
    string additional_desc = item_describer->describe_additional();
    
    string id = item->get_id();

    display_item.set_description(desc);
    display_item.set_additional_description(additional_desc);
    display_item.set_id(id);

    DisplayItemColourTranslator dict;
    display_item.set_colour(dict.create_colour_for_display_item(item));

    vector<TextColour> flags;
    bool glow = item->get_glowing();

    if (glow)
    {
      flags.push_back(make_pair(StringTable::get(ItemTextKeys::ITEM_GLOW), COLOUR_BOLD_YELLOW));
    }

    display_item.set_flags(flags);
  }

  return display_item;
}
