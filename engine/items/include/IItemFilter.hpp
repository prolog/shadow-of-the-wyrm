#pragma once
#include "Item.hpp"

class IItemFilter
{
  public:
    virtual ~IItemFilter() = default;
    virtual bool passes_filter(ItemPtr item) const = 0;
};

using IItemFilterPtr = std::shared_ptr<IItemFilter>;

