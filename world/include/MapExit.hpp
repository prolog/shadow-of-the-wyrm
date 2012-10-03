#pragma once
#include <boost/shared_ptr.hpp>
#include <string>
#include "tiles.hpp"

class MapExit
{
  public:
    MapExit();
    ~MapExit();

    void set_map_id(const std::string& map_id);
    std::string get_map_id() const;

    void set_terrain_type(const TileType new_tile_type);
    TileType get_terrain_type() const;

    bool is_using_map_id() const;
    bool is_using_terrain_type() const;

  protected:
    std::string map_id;
    TileType terrain_type;
};

typedef boost::shared_ptr<MapExit> MapExitPtr;
