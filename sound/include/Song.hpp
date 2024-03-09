#pragma once
#include <string>
#include "MapTypes.hpp"

class Song
{
  public:
    Song();
    Song(const std::string& id, const MapType map_type, const std::string& location);

    void set_id(const std::string& new_id);
    std::string get_id() const;

    void set_map_type(const MapType new_map_type);
    MapType get_map_type() const;

    void set_location(const std::string& new_location);
    std::string get_location() const;

  protected:
    std::string id;
    MapType map_type;
    std::string location;
};

