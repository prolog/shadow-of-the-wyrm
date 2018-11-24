#pragma once
#include <string>

class MapProperties
{
  public:
    // Can be used to override a generator's default permanence value.
    static const std::string MAP_PROPERTIES_PERMANENCE;

    // Used to set the map ID of a generated map, after generation, so
    // that other maps can create the link back as needed.
    static const std::string MAP_PROPERTIES_GENERATED_MAP_ID;

    // This is a string that is actually a serialized vector, and must
    // be deserialized before it can be used!
    static const std::string MAP_PROPERTIES_INITIAL_CREATURES;

    // A CSV containing item IDs to generate before generating by
    // rarity/level/etc
    static const std::string MAP_PROPERTIES_INITIAL_ITEMS;

    // Can be used to determine how to generate certain map features (such as
    // proportion of evergreen vs. broadleaf trees).
    static const std::string MAP_PROPERTIES_WORLD_MAP_LOCATION;
    static const std::string MAP_PROPERTIES_WORLD_MAP_HEIGHT;

    // CSV string of filters used to filter out creatures for a particular
    // tile type.
    static const std::string MAP_PROPERTIES_GENERATOR_FILTERS;

    // Should level checks be ignored when generating creatures?  Some places
    // are just dangerous. (vaults, etc)
    static const std::string MAP_PROPERTIES_IGNORE_CREATURE_LVL_CHECKS;

    // Is the creature danger level equal to the level's danger level?
    // If this is set, and you're on danger level 40, only danger level 40
    // creatures will be generated.
    static const std::string MAP_PROPERTIES_CREATURE_DANGER_LEVEL_FIXED;

    // Is a particular race required when generating creatures?  If so,
    // which one?  A race matches if it matches the given race, or the
    // given race is an ancestor (e.g., humanoid matches dwarf).
    static const std::string MAP_PROPERTIES_GENERATED_CREATURE_RACE_ID;

    // Special messages that should be displayed only once, the very first
    // time the player enters the level.  CSV string.
    static const std::string MAP_PROPERTIES_FEATURE_ENTRY_TEXT_SIDS;

    // Can we dig on this map?
    static const std::string MAP_PROPERTIES_CANNOT_DIG;

    // Can we teleport?
    static const std::string MAP_PROPERTIES_CANNOT_TELEPORT;

    // Are we in another plane of existence where the Nine hold no sway?
    static const std::string MAP_PROPERTIES_CANNOT_PRAY;

    // What is the creature generation rate?
    static const std::string MAP_PROPERTIES_CREATURE_GENERATION_RATE;

    // Should there be the chance of foragables?
    static const std::string MAP_PROPERTIES_PCT_CHANCE_FORAGABLES;

    // Should there be useful healing herbs?
    static const std::string MAP_PROPERTIES_PCT_CHANCE_HERBS;

    // If we're a shrine, what's the item ID of the relic?
    static const std::string MAP_PROPERTIES_RELIC_ID;

    // Are there creature IDs that should be used instead of considering
    // based on danger level and tile type?
    static const std::string MAP_PROPERTIES_CREATURE_IDS;

    static const std::string MAP_PROPERTIES_DEPTH;
    static const std::string MAP_PROPERTIES_MIN_DEPTH;
    static const std::string MAP_PROPERTIES_MAX_DEPTH;

    // Shimmer colours exist on certain maps.  They are a CSV of
    // numbers representing colours: "x,y,z"
    //
    // x = the colour of tiles with non-zero movement multipliers
    // y = the colour of tiles with zero movement multipliers
    // z = a "shimmer" that has a chance to override x and y on any
    //     given turn.
    static const std::string MAP_PROPERTIES_SHIMMER_COLOURS;

    // Generation coordinates are used when a particular map is "more
    // restricted" (e.g., floating tower, which has lots of air tiles
    // that shouldn't be used for generation) and we want to ensure
    // that creatures and items are only generated within a certain
    // range.
    static const std::string MAP_PROPERTIES_GENERATION_COORDINATES;

    // When the map was generated, did the creature that triggered the
    // generation ascend or descend?  For certain maps (dungeons, 
    // sewers, etc) this will trigger on which staircase the creature
    // will be placed.
    static const std::string MAP_PROPERTIES_EXIT_MOVEMENT_TYPE;
    
    // Used when dynamically populating tombs.  Different cultures
    // can have different creatures.
    static const std::string MAP_PROPERTIES_TOMB_GUARDIANS;

  protected:
    MapProperties();
    ~MapProperties();
};
