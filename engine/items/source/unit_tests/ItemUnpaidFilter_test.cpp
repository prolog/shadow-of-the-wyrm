#include "gtest/gtest.h"
#include "Amulet.hpp"
#include "Food.hpp"

TEST(SW_Engine_Items_ItemUnpaidFilter, passes_filter)
{
  ItemUnpaidFilter iuf;

  ItemPtr no_item;
  ItemPtr food = std::make_shared<Food>();
  food->set_unpaid(false);

  ItemPtr amulet = std::make_shared<Amulet>();
  amulet->set_unpaid(true);

  EXPECT_FALSE(iuf.passes_filter(no_item));
  EXPECT_FALSE(iuf.passes_filter(food));
  EXPECT_TRUE(iuf.passes_filter(amulet));
}
