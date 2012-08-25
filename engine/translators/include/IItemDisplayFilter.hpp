#pragma once
#include "Item.hpp"

class IItemDisplayFilter
{
  public:
    virtual bool passes_filter(ItemPtr item) const = 0;
};

typedef boost::shared_ptr<IItemDisplayFilter> IItemDisplayFilterPtr;

