#include "ItemDescriberFactory.hpp"
#include "InventoryDescriber.hpp"
#include "ItemDescriber.hpp"
#include "ItemTextKeys.hpp"
#include "StringTable.hpp"

using std::list;
using std::string;

InventoryDescriber::InventoryDescriber(const bool player_blind, const IInventoryPtr inv)
: inventory(inv), blind(player_blind)
{
}

string InventoryDescriber::describe() const
{
  string inventory_description;

  const list<ItemPtr>& items = inventory->get_items_cref();
  size_t num_items = items.size();

  // If there's just one item, describe it.
  if (num_items == 1)
  {
    ItemPtr item = *items.begin();
    IDescriberPtr item_id = ItemDescriberFactory::create_item_describer(blind, item);
    inventory_description = item_id->describe();
  }
  // Otherwise, the description should be "A number of items."
  else if (num_items > 1)
  {
    inventory_description = StringTable::get(ItemTextKeys::ITEM_MULTIPLE);
  }

  return inventory_description;
}

