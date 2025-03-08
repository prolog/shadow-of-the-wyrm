#pragma once
#include "IItemFilter.hpp"

// This happy little class ensures that everything passes.  It's useful
// for situations where initially there should be no filter (e.g., when
// the player selects "drop".
class NullItemFilter : public IItemFilter
{
  public:
    virtual ~NullItemFilter() = default;

    bool passes_filter(ItemPtr item) const override;
};
