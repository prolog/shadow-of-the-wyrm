#pragma once
#include <string>
#include "ISerializable.hpp"
#include "tiles.hpp"
#include "common.hpp"

class TileItemTransform : public ISerializable
{
  public:
    TileItemTransform();
    TileItemTransform(const Coordinate& new_coord, const std::string& new_item_id, const int new_min_quantity, const int new_max_quantity);
    bool operator==(const TileItemTransform& tt) const;

    void set_coordinate(const Coordinate& new_coord);
    Coordinate get_coordinate() const;

    void set_item_id(const std::string& new_item_id);
    std::string get_item_id() const;

    void set_min_quantity(const int new_min_quantity);
    int get_min_quantity() const;

    void set_max_quantity(const int new_max_quantity);
    int get_max_quantity() const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    // The coordinate to add the items at.
    Coordinate coord;

    // Item details
    std::string item_id;
    int min_quantity;
    int max_quantity;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

