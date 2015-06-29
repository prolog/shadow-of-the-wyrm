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

TEST(SL_World_Item, matches)
{
  ItemPtr amulet = std::make_shared<Amulet>();
  amulet->set_description_sid("asdf");
  amulet->set_usage_description_sid("aaa");
  amulet->set_quantity(2);
  Weight w(14);
  amulet->set_weight(w);

  ItemPtr amulet2 = std::make_shared<Amulet>();
  *amulet2 = *amulet;

  EXPECT_EQ(2, amulet2->get_quantity());
  EXPECT_TRUE(amulet->matches(amulet2));
}