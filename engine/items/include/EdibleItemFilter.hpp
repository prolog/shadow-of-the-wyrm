#pragma once
#include "IItemFilter.hpp"

// A filter that includes only items whose type is either FOOD or PLANT.
class EdibleItemFilter : public IItemFilter
{
  public:
    virtual ~EdibleItemFilter() = default;

    bool passes_filter(ItemPtr item) const override;
};

