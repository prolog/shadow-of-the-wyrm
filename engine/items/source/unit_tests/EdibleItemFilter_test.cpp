#include "gtest/gtest.h"
#include "Amulet.hpp"
#include "Food.hpp"
#include "Plant.hpp"

TEST(SL_Engine_Items_EdibleItemFilter, passes_test)
{
  EdibleItemFilter eif;

  ItemPtr no_item;
  ItemPtr amulet = std::make_shared<Amulet>();
  ItemPtr food = std::make_shared<Food>();
  ItemPtr plant = std::make_shared<Plant>();

  EXPECT_FALSE(eif.passes_filter(no_item));
  EXPECT_FALSE(eif.passes_filter(amulet));
  EXPECT_TRUE(eif.passes_filter(food));
  EXPECT_TRUE(eif.passes_filter(plant));
}
