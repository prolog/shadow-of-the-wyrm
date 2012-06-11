#pragma once
#include "FieldOfViewStrategy.hpp"

class RayCastingFieldOfViewStrategy : public FieldOfViewStrategy
{
  public:
    MapPtr calculate(MapPtr view_map, const Coordinate& creature_coords, const int los_length);
    
  protected:
    void add_points_to_map_as_appropriate(const std::vector<Coordinate>& coords, MapPtr view_map, MapPtr fov_map);
    void post_process_to_remove_artifacts(MapPtr view_map, MapPtr fov_map);
};
