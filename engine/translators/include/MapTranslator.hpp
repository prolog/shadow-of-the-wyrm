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
    // Create a full display map (used when doing a full redraw)
    static DisplayMap create_display_map(const bool player_blinded, const MapPtr& map, const MapPtr& fov_map, const MapDisplayArea& display_area, const Coordinate& reference_coords, const bool full_redraw_required);

    static DisplayTile create_display_tile(const bool player_blinded, const TilePtr& engine_tile, const TilePtr& fov_tile);
    static DisplayTile create_display_tile_from_creature(const CreaturePtr& creature);
    static DisplayTile create_display_tile_from_feature(const FeaturePtr& feature);
    static DisplayTile create_display_tile_from_item(const ItemPtr& item);
    static DisplayTile create_display_tile_from_tile(const TilePtr& tile);
    static DisplayTile create_display_tile_from_symbol_and_colour(const uchar symbol, const Colour colour);

  protected:
    MapTranslator();
    ~MapTranslator();

    // Translation function used when creating both a display map, and an update map.
    static DisplayTile translate_coordinate_into_display_tile(const bool player_blinded, const MapPtr& map, const MapPtr& fov_map, const int actual_row, const int actual_col);

    // For fields outside of the FOV
    static DisplayTile create_unseen_and_previously_viewed_display_tile(const TilePtr& tile);
    static DisplayTile create_unseen_and_explored_display_tile(const TilePtr& tile);
    static DisplayTile create_unseen_and_unexplored_display_tile();
};
