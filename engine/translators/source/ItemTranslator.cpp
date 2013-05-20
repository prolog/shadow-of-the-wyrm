#include "Conversion.hpp"
#include "DisplayItem.hpp"
#include "DisplayItemColourTranslator.hpp"
#include "ItemIdentifier.hpp"
#include "ItemTranslator.hpp"
#include "StringTable.hpp"

using namespace std;

ItemTranslator::ItemTranslator()
{
}

ItemTranslator::~ItemTranslator()
{
}

DisplayItem ItemTranslator::create_display_item(const ItemPtr& item)
{
  DisplayItem display_item;
  ostringstream desc_ss;

  if (item)
  {
    ItemIdentifier item_id;
    desc_ss << item_id.get_appropriate_description(item);
    
    uint quantity = item->get_quantity();
    
    if (quantity > 1)
    {
      desc_ss << " (" << Integer::to_string(quantity) << ")";
    }
    
    string id = item->get_id();

    display_item.set_description(desc_ss.str());
    display_item.set_id(id);

    DisplayItemColourTranslator dict;
    display_item.set_colour(dict.create_colour_for_display_item(item));
  }

  return display_item;
}
