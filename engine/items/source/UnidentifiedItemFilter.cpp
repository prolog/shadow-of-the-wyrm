#include "UnidentifiedItemFilter.hpp"
#include "ItemIdentifier.hpp"

using namespace std;

// Using the item's base ID, check to see whether the item has been
// identified.
bool UnidentifiedItemFilter::passes_filter(ItemPtr item) const
{
  ItemIdentifier iid;
  return (iid.get_item_identified(item->get_base_id()) == false);
}

