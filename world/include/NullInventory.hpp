#pragma once
#include "IInventory.hpp"
#include "ISerializable.hpp"

class NullInventory : public IInventory
{
  public:
    bool operator==(const IInventoryPtr inv) const override;

    bool add_front(ItemPtr new_item) override;
    bool add(ItemPtr new_item) override;
    void merge_or_add(ItemPtr item, const InventoryAdditionType inv_add_loc) override;
    bool merge(ItemPtr new_item) override;

    bool remove(const std::string& id) override;
    bool remove_by_base_id(const std::string& base_id) override;

    bool clear() override;

    bool has_items() const override;
    ItemPtr at(const uint index) override;
    ItemPtr get_from_id(const std::string& id) override;
    ItemPtr get_from_base_id(const std::string& base_id) override;

    bool empty() const override;

    uint size() const override;

    bool has_item_type(const ItemType type) const override;

    std::list<ItemPtr>& get_items_ref() override;
    const std::list<ItemPtr>& get_items_cref() const override;

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

  protected:
    std::list<ItemPtr> items;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};
