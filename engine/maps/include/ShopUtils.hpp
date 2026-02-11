#pragma once
#include <string>
#include "Map.hpp"
#include "Shop.hpp"

class ShopUtils
{
  public:
    static std::string generate_shop_id_from_shopkeeper_name(const std::string& shopkeeper_name);
    static bool has_space_for_wares(MapPtr map, const Shop& shop);

  protected:
    ShopUtils();
    ~ShopUtils();
};