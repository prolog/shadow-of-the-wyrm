#pragma once
#include "IItemFilter.hpp"

// Used to determine whether an item has been identified, using its
// base identifier to check.
class UnidentifiedItemFilter : public IItemFilter
{
  public:
    bool passes_filter(ItemPtr item) const override;
};

