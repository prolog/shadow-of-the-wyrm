#include "gtest/gtest.h"
#include "Scroll.hpp"

TEST(SW_World_Readable, additional_item_attributes)
{
  ScrollPtr readable1 = std::make_shared<Scroll>();
  ScrollPtr readable2 = std::make_shared<Scroll>();

  readable1->set_text_sid("abc123");
  readable2->set_text_sid("cde432");

  EXPECT_FALSE(readable1->additional_item_attributes_match(readable2));

  readable2->set_text_sid("abc123");

  EXPECT_TRUE(readable1->additional_item_attributes_match(readable2));
}

