#pragma once
#include "Tile.hpp"

class EarthTile : public Tile
{
  public:
    EarthTile();

    TileType get_tile_type() const override;
    TileType get_decomposition_tile_type() const override;
    std::vector<std::pair<std::pair<int, int>, std::string>> get_decomposition_item_ids() const override;

    std::string get_tile_description_sid() const override;

    int get_movement_multiplier() const override;

    virtual Tile* clone() override;

  private:
    ClassIdentifier internal_class_identifier() const override;

    static const int EARTH_TILE_HARDNESS;
};

