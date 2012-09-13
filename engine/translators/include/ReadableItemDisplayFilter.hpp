#pragma once
#include "IItemDisplayFilter.hpp"

// A filter that includes only items whose "readable" flag is set
// to true.  This should only be books and scrolls.
class ReadableItemDisplayFilter : public IItemDisplayFilter
{
  public:
    bool passes_filter(ItemPtr item) const;
};

