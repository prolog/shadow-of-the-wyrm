#include <boost/foreach.hpp>
#include "ItemDescriberFactory.hpp"
#include "InventoryDescriber.hpp"
#include "ItemDescriber.hpp"

using std::list;
using std::string;

InventoryDescriber::InventoryDescriber(const bool player_blind, const Inventory& inv)
: inventory(inv), blind(player_blind)
{
}

string InventoryDescriber::describe() const
{
  string inventory_description;

  list<ItemPtr> items = inventory.get_items_const();

  BOOST_FOREACH(ItemPtr item, items)
  {
    IDescriberPtr item_id = ItemDescriberFactory::create_item_describer(blind, item);
    inventory_description += item_id->describe();
  }

  return inventory_description;
}

