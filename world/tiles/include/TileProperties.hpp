#pragma once
#include <map>

enum TilePropertyType
{
  TILE_PROPERTY_EXTRA_DESCRIPTION_SID = 0,
  TILE_PROPERTY_CUSTOM_MAP_ID = 1
};

typedef std::map<TilePropertyType, std::string> TileProperties;

