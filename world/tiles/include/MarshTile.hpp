#pragma once
#include "WorldMapTile.hpp"

class MarshTile : public WorldMapTile
{
  public:
    TileType get_tile_type() const override;
    
    std::string get_tile_description_sid() const override;    
    int get_movement_multiplier() const override;
    SkillType get_treasure_skill() const override;

    virtual Tile* clone() override;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

