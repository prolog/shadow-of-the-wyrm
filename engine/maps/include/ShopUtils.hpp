#pragma once
#include <string>
#include "Map.hpp"
#include "Shop.hpp"

class ShopUtils
{
  public:
    static std::string generate_shop_id_from_shopkeeper_name(const std::string& shopkeeper_name);
    static bool has_space_for_wares(MapPtr map, const Shop& shop);
    static uint get_max_unpaid_items_for_repop(const Coordinate& start, const Coordinate& end);
    static uint get_num_unpaid_stacks(MapPtr map, const Coordinate& start, const Coordinate& end);

  protected:
    ShopUtils();
    ~ShopUtils();
};