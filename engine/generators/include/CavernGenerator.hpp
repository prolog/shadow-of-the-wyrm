#pragma once
#include "Generator.hpp"
#include "Map.hpp"
#include "MapUtils.hpp"

class CavernGenerator : public Generator
{
  public:
    virtual MapPtr generate(const Dimensions& dimensions, const std::string& map_exit_id);

  protected:
    void generate_cavern(MapPtr map);
    MapComponents get_cavern_components(MapPtr map);
    void connect_cavern_components(MapPtr map, const MapComponents& cc);
    void connect_caverns(MapPtr map, const Coordinate& first, const Coordinate& second);
    void reset_cavern_edges(MapPtr map);
    void generate_staircases(MapPtr map, const std::string& map_exit_id);
    void generate_staircase(MapPtr map, const TileType tile_type, const Direction direction, const std::string& map_exit_id);
};
