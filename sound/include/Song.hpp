#pragma once
#include <string>
#include "MapTypes.hpp"
#include "tiles.hpp"

class Song
{
  public:
    Song();
    Song(const std::string& event, const std::string& id, const TileType tile_type, const MapType map_type, const std::string& location);

    void set_event(const std::string& new_event);
    std::string get_event() const;

    void set_id(const std::string& new_id);
    std::string get_id() const;

    void set_tile_type(const TileType new_tile_type);
    TileType get_tile_type() const;

    void set_map_type(const MapType new_map_type);
    MapType get_map_type() const;

    void set_location(const std::string& new_location);
    std::string get_location() const;

  protected:
    std::string event;
    std::string id;
    TileType tile_type;
    MapType map_type;
    std::string location;
};

