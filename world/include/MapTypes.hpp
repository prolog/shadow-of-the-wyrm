#pragma once
#include <map>
#include <string>
#include "common.hpp"

enum MapType
{
  MAP_TYPE_WORLD = 0
, MAP_TYPE_OVERWORLD = 1
, MAP_TYPE_UNDERWORLD = 2
};

typedef std::map<std::string, Coordinate> NamedMapLocations;

