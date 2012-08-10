#include <boost/foreach.hpp>
#include "InventoryDescriber.hpp"
#include "ItemDescriber.hpp"

using std::list;
using std::string;

InventoryDescriber::InventoryDescriber(const Inventory& inv)
: inventory(inv)
{
}

string InventoryDescriber::describe() const
{
  string inventory_description;

  list<ItemPtr> items = inventory.get_items_const();

  BOOST_FOREACH(ItemPtr item, items)
  {
    ItemDescriber id(item);

    inventory_description += id.describe();
  }

  return inventory_description;
}

