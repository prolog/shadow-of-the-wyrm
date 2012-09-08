#include <sstream>
#include "ItemDumper.hpp"
#include "ItemIdentifier.hpp"
#include "StringTable.hpp"

using namespace std;

ItemDumper::ItemDumper(ItemPtr new_item)
: item(new_item)
{
}

string ItemDumper::str() const
{
  ostringstream ss;

  if (item)
  {
    ItemIdentifier item_id;
    ss << StringTable::get(item_id.get_appropriate_description_sid(item->get_base_id()));
  }

  // This may be empty - that's fine if we've passed in a null ItemPtr.
  return ss.str();
}
