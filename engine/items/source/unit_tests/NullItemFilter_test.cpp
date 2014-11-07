#include "gtest/gtest.h"
#include "Amulet.hpp"

TEST(SL_Engine_Items_NullItemFilter, passes_test)
{
  NullFilter nif;

  ItemPtr no_item;
  ItemPtr amulet = std::make_shared<Amulet>();

  EXPECT_TRUE(nif.passes_filter(no_item));
  EXPECT_TRUE(nif.passes_filter(amulet));
}

