#include "ItemTypeFilter.hpp"

ItemTypeFilter::ItemTypeFilter(const ItemType it)
: item_type(it)
{
}

bool ItemTypeFilter::passes_filter(ItemPtr item) const
{
  bool passes = false;

  if (item)
  {
    passes = (item_type == item->get_type());
  }

  return passes;
}

