#pragma once
#include <map>

class TileProperties
{
  public:
    static const std::string TILE_PROPERTY_EXTRA_DESCRIPTION_SID;

    // The next map's map ID - used for linking to the next map when it
    // already exists in the map registry.
    static const std::string TILE_PROPERTY_CUSTOM_MAP_ID;

    // The location on the next map that this tile links to.  Used
    // to maintain map links despite things like warping, etc.
    static const std::string TILE_PROPERTY_LINKED_COORD;

    // The previous map's map ID - used for linking to previous, permanent
    // maps.
    static const std::string TILE_PROPERTY_PREVIOUS_MAP_ID;

    // The "original" map ID - used for linking back to the original,
    // permanent map.  E.g.: linking to the overworld from the first
    // level of a random, impermanent dungeon complex.
    static const std::string TILE_PROPERTY_ORIGINAL_MAP_ID;
    
    // Used to determine if the player should be placed on the up staircase
    // (when descending), or the down staircase (when ascending).  If the
    // increment = "1", the player's going down the stairs.
    static const std::string TILE_PROPERTY_DEPTH_INCREMENT;

    // Used to identify the species of the tree/bush/etc tile.
    static const std::string TILE_PROPERTY_FLORA_TILE_DESCRIPTION_SID;

    // Should the tile be generated ruined, if applicable?
    static const std::string TILE_PROPERTY_RUINED;

    // What type of castle is this?
    static const std::string TILE_PROPERTY_CASTLE_TYPE;

    // What type of settlement is this?
    static const std::string TILE_PROPERTY_SETTLEMENT_TYPE;

    // For certain dungeon tiles, should we avoid overwriting the tile
    // as part of dungeon generation?
    static const std::string TILE_PROPERTY_NO_OVERWRITE;

    // Have we already dug at this tile?
    static const std::string TILE_PROPERTY_PREVIOUSLY_DUG;

    // Has something been planted on this tile?
    static const std::string TILE_PROPERTY_PLANTED;

    // Is there an engraving on this tile?
    static const std::string TILE_PROPERTY_ENGRAVING_SID;

    // What about an inscription?
    static const std::string TILE_PROPERTY_INSCRIPTION_SID;

    // If this is a water tile, is it freshwater?  Saltwater?
    static const std::string TILE_PROPERTY_WATER_TYPE;

    // Are only certain races allowed on this tile?
    static const std::string TILE_PROPERTY_ALLOWED_RACES;

    // Are only certain very specific creatures allowed on this tile?
    static const std::string TILE_PROPERTY_ALLOWED_CREATURE_IDS;

    // Can this tile be dug?
    static const std::string TILE_PROPERTY_CANNOT_DIG;

    // Generates the map key that identifies the custom map ID for
    // a given depth.
    static std::string get_depth_custom_map_id(const int depth);

    static const std::string CUSTOM_MAP_ID_PART;

    // Checks to see if a given string reprensents a depth-based
    // custom map ID.
    static bool is_depth_custom_map_id(const std::string& key);

  protected:
    TileProperties();
    ~TileProperties();
};

