#include "gtest/gtest.h"
#include "Amulet.hpp"
#include "Scroll.hpp"

TEST(SL_Engine_Items_ReadableItemFilter, passes_filter)
{
  ReadableItemFilter rif;

  ItemPtr no_item;
  ItemPtr amulet = std::make_shared<Amulet>();
  ItemPtr scroll = std::make_shared<Scroll>();

  EXPECT_FALSE(rif.passes_filter(no_item));
  EXPECT_FALSE(rif.passes_filter(amulet));
  EXPECT_TRUE(rif.passes_filter(scroll));
}
