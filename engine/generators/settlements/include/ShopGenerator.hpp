#pragma once
#include "Building.hpp"
#include "Map.hpp"

class ShopGenerator
{
  public:
    bool generate_shop(MapPtr map, const Building& building);  
    
  protected:
    std::vector<ItemType> get_random_item_types();
    std::vector<ItemType> get_magical_item_types();
    std::vector<ItemType> get_jewelry_item_types();
    std::vector<ItemType> get_weapons_and_armour_types();
    std::vector<ItemType> get_misc_item_types();
};

