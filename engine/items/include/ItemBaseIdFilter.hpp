#pragma once
#include <string>
#include "IItemFilter.hpp"

// Used to determine whether an item matches a given id
class ItemBaseIdFilter : public IItemFilter
{
  public:
    ItemBaseIdFilter(const std::string& new_base_id);
    virtual ~ItemBaseIdFilter() = default;

    bool passes_filter(ItemPtr item) const override;

  protected:
    std::string base_id;
};

