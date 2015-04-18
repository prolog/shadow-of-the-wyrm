#pragma once
#include "IInventory.hpp"
#include "ISerializable.hpp"

class Inventory : public IInventory
{
  public:
    bool operator==(const IInventory& inv) const override;
    
    bool add_front(ItemPtr new_item) override;
    bool add(ItemPtr new_item) override;    
    void merge_or_add(ItemPtr item, const InventoryAdditionType inv_add_loc) override;
    bool merge(ItemPtr new_item) override;
    
    bool remove(const std::string& id) override;
    ItemPtr remove_and_return(const std::string& id) override;
    std::pair<bool, std::vector<ItemPtr>> remove_by_base_id(const std::string& base_id, const int quantity = 1) override;
    
    bool clear() override;
    
    bool has_items() const override;
    ItemPtr at(const uint index) override;
    ItemPtr get_from_id(const std::string& id) override;
    ItemPtr get_from_base_id(const std::string& base_id) override;
    
    bool empty() const override;
    
    uint size() const override;
    
    bool has_item_type(const ItemType type) const override;
    bool has_item_with_property(const std::string& additional_property_name) const override;
    int count_items_with_property(const std::string& additional_property_name) const override;
    int count_items(const std::string& item_base_id) const override;

    std::list<ItemPtr>& get_items_ref() override;
    const std::list<ItemPtr>& get_items_cref() const override;

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;
    
  protected:
    std::list<ItemPtr> items;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};
