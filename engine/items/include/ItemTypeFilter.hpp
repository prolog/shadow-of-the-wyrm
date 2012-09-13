#pragma once
#include "IItemFilter.hpp"

// Display an item based on whether its item type matches a particular
// item type.
class ItemTypeFilter : public IItemFilter
{
  public:
    ItemTypeFilter(const ItemType it);
    bool passes_filter(ItemPtr item) const;

  protected:
    ItemType item_type;
};
