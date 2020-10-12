#include <sstream>
#include "ActionTextKeys.hpp"
#include "ItemDescriberFactory.hpp"
#include "InventoryDescriber.hpp"
#include "ItemDescriber.hpp"
#include "ItemTextKeys.hpp"
#include "StringTable.hpp"

using std::list;
using std::ostringstream;
using std::string;

InventoryDescriber::InventoryDescriber(const bool player_blind, const IInventoryPtr inv)
: blind(player_blind), inventory(inv)
{
}

string InventoryDescriber::describe_for_tile_selection() const
{
  return describe(true);
}

string InventoryDescriber::describe(const bool for_tile_selection) const
{
  string inventory_description;

  const list<ItemPtr>& items = inventory->get_items_cref();
  size_t num_items = items.size();

  // If there's just one item, describe it.
  if (num_items == 1)
  {
    ItemPtr item = *items.begin();
    IDescriberPtr item_id = ItemDescriberFactory::create_item_describer(blind, item);
    inventory_description = item_id->describe_for_tile_selection();
  }
  // Otherwise, the description should be "A number of items."
  else if (num_items > 1)
  {
    ostringstream ss;
    ss << StringTable::get(ItemTextKeys::ITEM_MULTIPLE);

    if (for_tile_selection)
    {
      ss << " " << StringTable::get(ActionTextKeys::ACTION_ITEM_CODEX_COMMAND_FOR_TILE_SELECTION);
    }

    inventory_description = ss.str();
  }

  return inventory_description;
}

string InventoryDescriber::describe() const
{
  return describe(false);
}

