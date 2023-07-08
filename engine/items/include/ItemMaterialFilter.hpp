#pragma once
#include <vector>
#include "IItemFilter.hpp"

// Used to determine whether an item is made of a particular material.
class ItemMaterialFilter : public IItemFilter
{
  public:
    ItemMaterialFilter(const std::vector<MaterialType>& new_materials);

    bool passes_filter(ItemPtr item) const override;

  protected:
    std::vector<MaterialType> materials;
};

