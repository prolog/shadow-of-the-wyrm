#pragma once
#include <memory>
#include "Map.hpp"

class FieldOfViewStrategy
{
  public:
    FieldOfViewStrategy(const bool set_view_property);
    
    virtual MapPtr calculate(CreaturePtr fov_creaure, MapPtr view_map, const Coordinate& centre_coordinate, const int los_length) = 0;
    
  protected:
    void add_point_to_map(CreaturePtr fov_creature, const Coordinate& c, MapPtr view_map, MapPtr fov_map);
    
    // The "view" flag is the flag that causes the tile to be displayed when
    // redrawing the screen.  This should only be set for the player, or else
    // the screen will be updated as creatures move about.
    bool set_fov_tile_view_flag;
};

using FieldOfViewStrategyPtr = std::shared_ptr<FieldOfViewStrategy>;
