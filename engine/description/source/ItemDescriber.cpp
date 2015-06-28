#include "Conversion.hpp"
#include "ItemDescriber.hpp"
#include "ItemIdentifier.hpp"
#include "ResistancesTranslator.hpp"
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
    item_description = item_id.get_appropriate_description(item);
    
    uint quantity = item->get_quantity();
    
    // Add quantity as necessary
    if (quantity > 1)
    {
      item_description += " (" + std::to_string(quantity) + ")";
    }

    // Add weight
    item_description += " [" + item->get_total_weight().str() + "]";
  }

  return item_description;
}

string ItemDescriber::describe_usage() const
{
  string item_description;

  if (item)
  {
    ItemIdentifier item_id;
    item_description = item_id.get_appropriate_usage_description(item);

    uint quantity = item->get_quantity();

    // Add quantity
    if (quantity > 1)
    {
      item_description += " (" + std::to_string(quantity) + ")";
    }

    // No need to add weight to the usage description.
  }

  return item_description;
}

string ItemDescriber::describe_additional() const
{
  string addl_desc;

  if (item)
  {
    ItemIdentifier item_id;

    if (item_id.get_item_identified(item->get_base_id()))
    {
      Resistances res = item->get_resistances();

      ResistancesTranslator rt;
      addl_desc = rt.create_description(res);
    }
  }

  return addl_desc;
}
