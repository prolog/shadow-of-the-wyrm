#include "gtest/gtest.h"
#include "Amulet.hpp"

TEST(SW_Engine_Items_ItemBaseIdFilter, passes_test)
{
  ItemBaseIdFilter imf("gleaming_amulet");
  
  ItemPtr no_item;
  ItemPtr amulet = std::make_shared<Amulet>();
  amulet->set_base_id("glinting_amulet");

  EXPECT_FALSE(imf.passes_filter(no_item));
  EXPECT_FALSE(imf.passes_filter(amulet));

  amulet->set_base_id("gleaming_amulet");

  EXPECT_TRUE(imf.passes_filter(amulet));
}

