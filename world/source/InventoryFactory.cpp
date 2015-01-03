#include "InventoryFactory.hpp"
#include "Inventory.hpp"
#include "NullInventory.hpp"

IInventoryPtr InventoryFactory::create_inventory(ClassIdentifier cl_id)
{
  IInventoryPtr inv;

  if (cl_id == ClassIdentifier::CLASS_ID_INVENTORY)
  {
    inv = std::make_shared<Inventory>();
  }
  else if (cl_id == ClassIdentifier::CLASS_ID_NULL_INVENTORY)
  {
    inv = std::make_shared<NullInventory>();
  }
  else
  {
    static_assert(true, "Attempted to create an inventory with an unrecognized class identifier!");
  }

  return inv;
}