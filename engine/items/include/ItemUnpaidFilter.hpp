#pragma once
#include <list>
#include "IItemFilter.hpp"

// Display an item if it's unpaid.
class ItemUnpaidFilter : public IItemFilter
{
  public:
    ItemUnpaidFilter();
    virtual ~ItemUnpaidFilter() = default;

    bool passes_filter(ItemPtr item) const override;
};
