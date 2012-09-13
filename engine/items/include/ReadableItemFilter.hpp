#pragma once
#include "IItemFilter.hpp"

// A filter that includes only items whose "readable" flag is set
// to true.  This should only be books and scrolls.
class ReadableItemFilter : public IItemFilter
{
  public:
    bool passes_filter(ItemPtr item) const;
};

