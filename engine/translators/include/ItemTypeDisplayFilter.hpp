#pragma once
#include "IItemDisplayFilter.hpp"

// Display an item based on whether its item type matches a particular
// item type.
class ItemTypeDisplayFilter : public IItemDisplayFilter
{
  public:
    ItemTypeDisplayFilter(const ItemType it);
    bool passes_filter(ItemPtr item) const;

  protected:
    ItemType item_type;
};
