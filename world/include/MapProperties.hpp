#pragma once
#include <string>

class MapProperties
{
  public:
    // Can be used to override a generator's default permanence value.
    static const std::string MAP_PROPERTIES_PERMANENCE;

  protected:
    MapProperties();
    ~MapProperties();
};

