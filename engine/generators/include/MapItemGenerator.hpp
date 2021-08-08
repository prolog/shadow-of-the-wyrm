#pragma once
#include "Map.hpp"
#include "RarityTypes.hpp"

class MapItemGenerator
{
  public:
    bool generate_items(MapPtr map, const int base_danger_level, const std::tuple<bool, int, Rarity>& creature_details);
    bool generate_initial_set_items(MapPtr map, const std::map<std::string, std::string>& properties);
    bool repop_shop(MapPtr map, const std::string& shop_id);

  protected:
    bool generate_dead_adventurer(MapPtr map, const int danger_level);

    static const int OUT_OF_DEPTH_ITEMS_CHANCE;
    static const int PCT_CHANCE_ADVENTURER_SKELETON_TRAP;
    static const int PCT_CHANCE_ADVENTURER_CORPSE;
};

