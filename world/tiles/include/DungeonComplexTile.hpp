#pragma once
#include "WorldMapTile.hpp"

// The actual dungeon complex
class DungeonComplexTile : public WorldMapLandmarkTile
{
  public:
    TileType get_tile_type() const override;
    
    std::string get_tile_description_sid() const override;
    bool is_interior() const override;

    virtual Tile* clone() override;

  private:
    ClassIdentifier internal_class_identifier() const override;
};
