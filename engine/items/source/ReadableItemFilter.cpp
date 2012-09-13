#include "ReadableItemFilter.hpp"

// Check to see if the item is readable
bool ReadableItemFilter::passes_filter(ItemPtr item) const
{
  return (item && item->get_readable());
}

