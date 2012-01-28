#include <sstream>
#include "ItemDumper.hpp"
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
    ss << StringTable::get(item->get_description_sid());
  }

  // This may be empty - that's fine if we've passed in a null ItemPtr.
  return ss.str();
}
