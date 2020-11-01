#pragma once
#include "IDescriber.hpp"
#include "IInventory.hpp"

class InventoryDescriber : public IDescriber
{
  public:
    InventoryDescriber(const bool blind, const IInventoryPtr inv);

    std::string describe_for_tile_selection() const override;
    std::string describe(const bool for_tile_selection) const;
    std::string describe() const override;

  protected:
    const bool blind;
    const IInventoryPtr inventory;
};
