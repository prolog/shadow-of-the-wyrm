#include "NullItemFilter.hpp"

bool NullFilter::passes_filter(ItemPtr item) const
{
  return true;
}

