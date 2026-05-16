#include "gtest/gtest.h"
#include "Amulet.hpp"
#include "FieldGenerator.hpp"

TEST(SW_World_ShopUtils, generate_shop_id_from_shopkeeper_id)
{
  string sk_id = "some_shopkeeper";
  EXPECT_EQ("some_shopkeeper_shop", ShopUtils::generate_shop_id_from_shopkeeper_name(sk_id));
}

TEST(SW_World_ShopUtils, get_max_unpaid_items_for_repop)
{
  vector<pair<Coordinate, Coordinate>> coords = { {{0,0}, {3, 3}},
                                                  {{4,15}, {7, 20}} };

  for (const auto& c_pairs : coords)
  {
    uint exp_val = (1 + CoordUtils::get_width(c_pairs.first, c_pairs.second)) * (1 + CoordUtils::get_height(c_pairs.first, c_pairs.second));
    EXPECT_EQ(exp_val, ShopUtils::get_max_unpaid_items_for_repop(c_pairs.first, c_pairs.second));
  }
}

TEST(SW_World_ShopUtils, get_num_unpaid_stacks)
{
  FieldGenerator fg("fake_exit");
  Dimensions dim;
  MapPtr map = fg.generate(dim);
  Coordinate start = {5, 5};
  Coordinate end   = {8, 8};
  vector<Coordinate> unpaid_coords({ {5, 5}, {5, 5}, {6, 7} });
  uint quantity_counter = 0;

  for (const Coordinate& uc : unpaid_coords)
  {
    ItemPtr unpaid = std::make_shared<Amulet>();
    unpaid->set_unpaid(true);

    // This doesn't make sense from a game standpoint, but it should prevent
    // items from stacking to make the counting easier.
    unpaid->set_codex_description_sid(std::to_string(++quantity_counter));

    map->at(uc)->get_items()->merge_or_add(unpaid);
  }

  EXPECT_EQ(3, ShopUtils::get_num_unpaid_stacks(map, start, end));
}