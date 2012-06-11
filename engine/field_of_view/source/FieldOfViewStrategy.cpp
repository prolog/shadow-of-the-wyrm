#include "FieldOfViewStrategy.hpp"

void FieldOfViewStrategy::add_point_to_map(const Coordinate& c, MapPtr view_map, MapPtr fov_map)
{
  TilePtr tile = view_map->at(c);
  
  if (tile)
  {
    tile->set_viewed(true);
    fov_map->insert(c.first, c.second, tile);
  }
}

