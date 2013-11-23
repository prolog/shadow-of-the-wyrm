#pragma once
#include "Item.hpp"

class IItemFilter
{
  public:
    virtual bool passes_filter(ItemPtr item) const = 0;
};

typedef std::shared_ptr<IItemFilter> IItemFilterPtr;

