#pragma once
#include <list>
#include "IItemFilter.hpp"

// Display an item based on whether its item type matches a particular
// item type.
class ItemTypeFilter : public IItemFilter
{
  public:
    ItemTypeFilter(const ItemType it);
    ItemTypeFilter(const std::list<ItemType>& it_list);
    bool passes_filter(ItemPtr item) const override;

  protected:
    std::list<ItemType> item_types;
};
