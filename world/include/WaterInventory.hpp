#pragma once
#include "Inventory.hpp"
#include "ISerializable.hpp"

class WaterInventory : public Inventory
{
  public:
    bool add_front(ItemPtr new_item) override;
    bool add(ItemPtr new_item) override;    
    void merge_or_add(ItemPtr item, const InventoryAdditionType inv_add_loc) override;
    bool merge(ItemPtr new_item) override;    

    void set_items(const std::list<ItemPtr>& items) override;
    void add_items(const std::list<ItemPtr>& items) override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};
