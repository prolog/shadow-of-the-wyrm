#pragma once
#include <map>

class TileProperties
{
  public:
    static const std::string TILE_PROPERTY_EXTRA_DESCRIPTION_SID;

    // The next map's map ID - used for linking to the next map when it
    // already exists in the map registry.
    static const std::string TILE_PROPERTY_CUSTOM_MAP_ID;

    // The previous map's map ID - used for linking to previous, permanent
    // maps.
    static const std::string TILE_PROPERTY_PREVIOUS_MAP_ID;

    // The "original" map ID - used for linking back to the original,
    // permanent map.  E.g.: linking to the overworld from the first
    // level of a random, impermanent dungeon complex.
    static const std::string TILE_PROPERTY_ORIGINAL_MAP_ID;

  protected:
    TileProperties();
    ~TileProperties();
};

