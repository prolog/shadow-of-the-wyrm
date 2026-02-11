#include "gtest/gtest.h"

TEST(SW_World_Shop, generate_shop_id_from_shopkeeper_id)
{
  string sk_id = "some_shopkeeper";
  EXPECT_EQ("some_shopkeeper_shop", ShopUtils::generate_shop_id_from_shopkeeper_name(sk_id));
}
