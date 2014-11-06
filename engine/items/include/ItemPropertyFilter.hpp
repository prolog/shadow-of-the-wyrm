#pragma once
#include "IItemFilter.hpp"

// Used to determine whether an item has a particular property.  If the
// property's value is empty, only the property name is checked.  If the
// property's value is non-empty, the property must be present and the
// property values must match.
class ItemPropertyFilter : public IItemFilter
{
  public:
    ItemPropertyFilter(const std::pair<std::string, std::string>& prop_pair);

    bool passes_filter(ItemPtr item) const override;

  protected:
    std::pair<std::string, std::string> property;
};

