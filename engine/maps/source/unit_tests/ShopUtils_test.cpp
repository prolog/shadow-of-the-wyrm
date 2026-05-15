#include "gtest/gtest.h"

TEST(SW_World_Shop, generate_shop_id_from_shopkeeper_id)
{
  string sk_id = "some_shopkeeper";
  EXPECT_EQ("some_shopkeeper_shop", ShopUtils::generate_shop_id_from_shopkeeper_name(sk_id));
}

TEST(SW_World_Shop, get_max_unpaid_items_for_repop)
{
  vector<pair<Coordinate, Coordinate>> coords = { {{0,0}, {3, 3}},
                                                  {{4,15}, {7, 20}} };

  for (const auto& c_pairs : coords)
  {
    uint exp_val = (1 + CoordUtils::get_width(c_pairs.first, c_pairs.second)) * (1 + CoordUtils::get_height(c_pairs.first, c_pairs.second));
    EXPECT_EQ(exp_val, ShopUtils::get_max_unpaid_items_for_repop(c_pairs.first, c_pairs.second));
  }
}
