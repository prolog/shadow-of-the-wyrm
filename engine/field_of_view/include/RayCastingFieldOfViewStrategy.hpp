#pragma once
#include "FieldOfViewStrategy.hpp"

class RayCastingFieldOfViewStrategy : public FieldOfViewStrategy
{
  public:
    RayCastingFieldOfViewStrategy(const bool set_view_property);
    
    MapPtr calculate(CreaturePtr fov_creature, MapPtr view_map, const Coordinate& creature_coords, const int los_length) override;
    
  protected:
    enum struct PassType
    {
      PASS_NON_CORNER_BLOCKING_TILES = 0,
      PASS_CORNER_BLOCKING_TILES = 1
    };

    void add_points_to_map_as_appropriate(CreaturePtr fov_creature, const std::vector<Coordinate>& coords, MapPtr view_map, MapPtr fov_map);
    void post_process_to_remove_artifacts(CreaturePtr fov_creature, const Coordinate& centre_coord, MapPtr view_map, MapPtr fov_map, const PassType type);
    
    bool does_adjacent_non_blocking_tile_exist_in_fov_map(MapPtr fov_map, const Coordinate& centre_coord, const Direction direction);
    bool does_adjacent_blocking_tile_exist_in_fov_map(MapPtr fov_map, const Coordinate& centre_coord, const Direction direction);
    
    bool is_artifact_nw(MapPtr fov_map, const Coordinate& c, const PassType type);
    bool is_artifact_ne(MapPtr fov_map, const Coordinate& c, const PassType type);
    bool is_artifact_sw(MapPtr fov_map, const Coordinate& c, const PassType type);
    bool is_artifact_se(MapPtr fov_map, const Coordinate& c, const PassType type);
    
    bool is_corner_blocking_tile(MapPtr fov_map, const Coordinate& c, const Direction blocking1, const Direction blocking2, const Direction non_blocking);
    bool is_non_corner_blocking_tile(MapPtr fov_map, const Coordinate& c, const Direction first_direction, const Direction second_direction);    
};
