#pragma once
#include <string>

class MapProperties
{
  public:
    // Can be used to override a generator's default permanence value.
    static const std::string MAP_PROPERTIES_PERMANENCE;

    // This is a string that is actually a serialized vector, and must
    // be deserialized before it can be used!
    static const std::string MAP_PROPERTIES_INITIAL_CREATURES;

    // Can be used to determine how to generate certain map features (such as
    // proportion of evergreen vs. broadleaf trees).
    static const std::string MAP_PROPERTIES_WORLD_MAP_LOCATION;
    static const std::string MAP_PROPERTIES_WORLD_MAP_HEIGHT;

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

