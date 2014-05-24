#pragma once
#include "Map.hpp"

// Class responsible for generating creatures (either a pre-set list, or a list
// built up based on danger level/terrain type/etc) on to a given map.
class MapCreatureGenerator
{
  public:
    // Generate the creatures.  Returns true if creatures were created, false otherwise.
    virtual bool generate_creatures(MapPtr map, const int danger_level, const std::map<std::string, std::string>& additional_properties);
    virtual bool generate_initial_set_creatures(MapPtr map, const std::map<std::string, std::string>& additional_properties);
    virtual bool generate_random_creatures(MapPtr map, const int danger_level, const std::map<std::string, std::string>& additional_properties);
};

