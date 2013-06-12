#pragma once
#include <string>

class MapProperties
{
  public:
    // Can be used to override a generator's default permanence value.
    static const std::string MAP_PROPERTIES_PERMANENCE;

    // Can be used to determine how to generate certain map features (such as
    // proportion of evergreen vs. broadleaf trees).
    static const std::string MAP_PROPERTIES_WORLD_MAP_LOCATION;

  protected:
    MapProperties();
    ~MapProperties();
};

