#pragma once
#include <map>
#include <string>
#include "common.hpp"

enum struct MapType
{
  MAP_TYPE_WORLD = 0
, MAP_TYPE_OVERWORLD = 1
, MAP_TYPE_UNDERWORLD = 2
};

class MapID
{
  public:
    static const std::string MAP_ID_OVERWORLD;

  protected:
    MapID();
};

using NamedMapLocations = std::map<std::string, Coordinate>;

