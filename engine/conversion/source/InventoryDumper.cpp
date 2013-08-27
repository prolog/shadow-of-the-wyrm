#include <boost/foreach.hpp>
#include <sstream>
#include "Conversion.hpp"
#include "InventoryDumper.hpp"
#include "ItemDumper.hpp"
#include "TextKeys.hpp"

using namespace std;

InventoryDumper::InventoryDumper(CreaturePtr new_creature, const uint new_num_cols)
: creature(new_creature), num_cols(new_num_cols)
{
}

string InventoryDumper::str() const
{
  ostringstream ss;
  
  ss << String::centre(StringTable::get(TextKeys::INVENTORY), num_cols) << endl << endl;
  ss << get_inventory() << endl << endl;
  
  return ss.str();
}

string InventoryDumper::get_inventory() const
{
  ostringstream ss;
  bool at_least_one_item = false;
  
  if (creature)
  {
    Inventory inv = creature->get_inventory();
    const list<ItemPtr>& raw_items = inv.get_items_cref();
    
    BOOST_FOREACH(ItemPtr item, raw_items)
    {
      ItemDumper item_dumper(item);
      ss << item_dumper.str() << endl;
      
      if (!at_least_one_item) at_least_one_item = true;
    }
  }
  
  if (!at_least_one_item)
  {
    ss << String::centre("-", num_cols) << endl << endl;
  }
  
  return ss.str();
}
