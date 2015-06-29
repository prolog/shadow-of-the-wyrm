#include "gtest/gtest.h"
#include "Amulet.hpp"

TEST(SL_World_Item, quantity_weight)
{
  ItemPtr amulet = std::make_shared<Amulet>();

  amulet->set_quantity(2);

  Weight w(10);
  amulet->set_weight(w);

  EXPECT_EQ(20, amulet->get_weight(2).get_weight());

  EXPECT_EQ(30, amulet->get_weight(3).get_weight());
}

TEST(SL_World_Item, total_weight)
{
  ItemPtr amulet = std::make_shared<Amulet>();

  amulet->set_quantity(3);
  Weight w(16);

  amulet->set_weight(w);

  EXPECT_EQ(48, amulet->get_total_weight().get_weight());
}

