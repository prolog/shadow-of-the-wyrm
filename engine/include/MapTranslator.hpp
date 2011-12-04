#pragma once
#include "Map.hpp"
#include "DisplayMap.hpp"

class DisplayMap;

// MapTranslator creates a DisplayMap (meant for the various Display
// classes) from a regular map.  A DisplayMap is a simplied map that
// provides the Display with only the information it requires, and
// ensures that selection logic ("What should be displayed?  The tile?
// The sword?  The creature?", etc) is kept to the engine.
class MapTranslator
{
  public:
    static DisplayMap create_display_map(const MapPtr& map, const MapDisplayArea& display_area, const bool centre_on_player = true);

  protected:
    MapTranslator();
    ~MapTranslator();

    static DisplayTile create_display_tile(const TilePtr& engine_tile);
};
