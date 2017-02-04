#pragma once
#include <string>
#include <vector>
#include "common.hpp"
#include "ISerializable.hpp"
#include "ItemTypes.hpp"

class Shop : public ISerializable
{
  public:
    Shop();
    Shop(const std::string& new_shop_id, const std::string& new_shopkeeper_id, const Coordinate& new_start, const Coordinate& new_end, const std::vector<ItemType>& stocked_item_types);

    bool operator==(const Shop& s) const;

    void set_shop_id(const std::string& new_shop_id);
    std::string get_shop_id() const;

    void set_shopkeeper_id(const std::string& new_shopkeeper_id);
    std::string get_shopkeeper_id()const;

    void set_start(const Coordinate& new_start);
    Coordinate get_start() const;

    void set_end(const Coordinate& new_end);
    Coordinate get_end() const;

    void set_stocked_item_types(const std::vector<ItemType>& new_stocked_item_types);
    std::vector<ItemType> get_stocked_item_types() const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    std::string shop_id;
    std::string shopkeeper_id;
    Coordinate start;
    Coordinate end;
    std::vector<ItemType> stocked_item_types;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

