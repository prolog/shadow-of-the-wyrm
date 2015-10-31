#pragma once
#include "Map.hpp"

class MapItemGenerator
{
  public:
    bool generate_items(MapPtr map, const int base_danger_level, const std::pair<bool, int>& creature_details);

  protected:
    static const int OUT_OF_DEPTH_ITEMS_CHANCE;
};

