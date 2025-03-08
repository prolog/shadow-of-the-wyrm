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
    bool generate_ivory_on_shopkeeper(MapPtr map, const Shop& shop);
    std::vector<ItemPtr> generate_dead_adventurer_items(const int danger_level, const int danger_upper, const Rarity rarity);

    static const int OUT_OF_DEPTH_ITEMS_CHANCE;
    static const int PCT_CHANCE_ADVENTURER_SKELETON_TRAP;
    static const int PCT_CHANCE_ADVENTURER_CORPSE;
    static const std::pair<int, int> X_IN_Y_CHANCE_ARTIFACT;
    static const int PCT_CHANCE_ADVENTURER_ITEMS;
    static const int SHOPKEEPER_ADDITIONAL_IVORY_THRESOLD;
    static const int MIN_REPOP_IVORY;
    static const int MAX_REPOP_IVORY;
};

