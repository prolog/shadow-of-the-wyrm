#pragma once
#include "IInventory.hpp"

class InventoryFactory
{
  public:
    static IInventoryPtr create_inventory(const ClassIdentifier cl_id);
};

