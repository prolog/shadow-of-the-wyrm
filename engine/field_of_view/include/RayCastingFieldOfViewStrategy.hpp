#pragma once
#include "FieldOfViewStrategy.hpp"

class RayCastingFieldOfViewStrategy : public FieldOfViewStrategy
{
  public:
    RayCastingFieldOfViewStrategy(const bool set_view_property);
    
    MapPtr calculate(MapPtr view_map, const Coordinate& creature_coords, const int los_length);
    
  protected:
    void add_points_to_map_as_appropriate(const std::vector<Coordinate>& coords, MapPtr view_map, MapPtr fov_map);
    void post_process_to_remove_artifacts(const Coordinate& centre_coord, MapPtr view_map, MapPtr fov_map);
    bool does_adjacent_non_blocking_tile_exist_in_fov_map(MapPtr fov_map, const Coordinate& centre_coord, const Direction direction);
};
