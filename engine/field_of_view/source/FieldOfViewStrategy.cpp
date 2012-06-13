#include "FieldOfViewStrategy.hpp"

FieldOfViewStrategy::FieldOfViewStrategy(const bool set_fov_flag)
: set_fov_tile_view_flag(set_fov_flag)
{  
}

void FieldOfViewStrategy::add_point_to_map(const Coordinate& c, MapPtr view_map, MapPtr fov_map)
{
  TilePtr tile = view_map->at(c);
  
  if (tile)
  {
    if (set_fov_tile_view_flag)
    {
      tile->set_viewed(true);      
    }

    fov_map->insert(c.first, c.second, tile);
  }
}

