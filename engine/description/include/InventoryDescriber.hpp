#pragma once
#include "IDescriber.hpp"
#include "IInventory.hpp"

class InventoryDescriber : public IDescriber
{
  public:
    InventoryDescriber(const bool blind, const IInventoryPtr inv);

    std::string describe() const override;

  protected:
    const bool blind;
    const IInventoryPtr inventory;
};
