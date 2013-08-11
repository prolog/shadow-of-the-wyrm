#pragma once
#include "IDescriber.hpp"
#include "Inventory.hpp"

class InventoryDescriber : public IDescriber
{
  public:
    InventoryDescriber(const bool blind, const Inventory& inv);

    std::string describe() const;

  protected:
    const bool blind;
    const Inventory& inventory;
};
