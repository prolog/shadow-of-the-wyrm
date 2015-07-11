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

    // Can be used to determine how to generate certain map features (such as
    // proportion of evergreen vs. broadleaf trees).
    static const std::string MAP_PROPERTIES_WORLD_MAP_LOCATION;
    static const std::string MAP_PROPERTIES_WORLD_MAP_HEIGHT;

    // CSV string of filters used to filter out creatures for a particular
    // tile type.
    static const std::string MAP_PROPERTIES_GENERATOR_FILTERS;

    // Should level checks be ignored when generating creatures?  Some places
    // are just dangerous.
    static const std::string MAP_PROPERTIES_IGNORE_CREATURE_LVL_CHECKS;

    // Special messages that should be displayed only once, the very first
    // time the player enters the level.  CSV string.
    static const std::string MAP_PROPERTIES_FEATURE_ENTRY_TEXT_SIDS;

  protected:
    MapProperties();
    ~MapProperties();
};

// Underworld properties: depth-related, etc.
class UnderworldProperties
{
  public:
    static const std::string UNDERWORLD_STRUCTURE_DEPTH;
    static const std::string UNDERWORLD_STRUCTURE_MAX_DEPTH;

  protected:
    UnderworldProperties();
    ~UnderworldProperties();
};

