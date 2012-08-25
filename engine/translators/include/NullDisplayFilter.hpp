#pragma once
#include "IItemDisplayFilter.hpp"

// This happy little class ensures that everything passes.  It's useful
// for situations where initially there should be no filter (e.g., when
// the player selects "drop".
class NullDisplayFilter : public IItemDisplayFilter
{
  public:
    bool passes_filter(ItemPtr item) const;
};
