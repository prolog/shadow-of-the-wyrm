#pragma once
#include "WorldMapTile.hpp"

class VillageTile : public WorldMapLandmarkTile
{
  public:
    // Villages are situated "on" something, and that subtype
    // is the underlying map upon which the village is placed.
    // If no subtype is provided, Field is assumed.
    VillageTile();
    VillageTile(const TileType new_tile_subtype);
    
    virtual bool display_description_on_arrival() const;
    
    TileType get_tile_type() const;
    TileType get_tile_subtype() const;
    
    std::string get_tile_description_sid() const;

  protected:
    TileType tile_subtype;
};

