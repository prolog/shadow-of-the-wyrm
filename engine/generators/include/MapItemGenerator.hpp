#pragma once
#include "Map.hpp"
#include "RarityTypes.hpp"

class MapItemGenerator
{
  public:
    bool generate_items(MapPtr map, const int base_danger_level, const std::tuple<bool, int, Rarity>& creature_details);
    bool repop_shop(MapPtr map, const std::string& shop_id);

  protected:
    static const int OUT_OF_DEPTH_ITEMS_CHANCE;
};

