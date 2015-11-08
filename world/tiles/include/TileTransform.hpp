#pragma once
#include <map>
#include "ISerializable.hpp"
#include "tiles.hpp"

class TileTransform : public ISerializable
{
  public:
    TileTransform();
    TileTransform(const double new_time, const TileType new_tt, const TileType new_tst, const std::map<std::string, std::string>& new_props);
    bool operator==(const TileTransform& tt) const;

    void set_min_transform_time(const double new_transform_time);
    double get_min_transform_time() const;

    void set_tile_type(const TileType new_tile_type);
    TileType get_tile_type() const;

    void set_tile_subtype(const TileType new_tile_subtype);
    TileType get_tile_subtype() const;

    void set_properties(const std::map<std::string, std::string>& new_properties);
    std::map<std::string, std::string> get_properties() const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    // The minimum time at which the transformation can occur.
    double min_transform_time;

    // Tile details.
    TileType tile_type;
    TileType tile_subtype;
    std::map<std::string, std::string> properties;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

