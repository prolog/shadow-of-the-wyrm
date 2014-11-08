#pragma once
#include "IItemFilter.hpp"

// Used to determine whether an item is made of a particular material.
class ItemMaterialFilter : public IItemFilter
{
  public:
    ItemMaterialFilter(const MaterialType new_material);

    bool passes_filter(ItemPtr item) const override;

  protected:
    MaterialType material;
};

