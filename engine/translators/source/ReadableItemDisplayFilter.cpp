#include "ReadableItemDisplayFilter.hpp"

// Check to see if the item is readable
bool ReadableItemDisplayFilter::passes_filter(ItemPtr item) const
{
  return (item && item->get_readable());
}

