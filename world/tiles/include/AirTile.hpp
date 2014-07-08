#pragma once
#include "Tile.hpp"

class AirTile : public Tile
{
  public:
    AirTile();

    TileType get_tile_type() const override;
    TileSuperType get_tile_super_type() const;
    
    std::string get_tile_description_sid() const override;

    bool get_dangerous(CreaturePtr creature) const override;
    std::string get_danger_confirmation_sid() const override;

    virtual Tile* clone() override;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

