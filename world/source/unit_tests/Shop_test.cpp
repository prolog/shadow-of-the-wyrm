#include "gtest/gtest.h"

TEST(SW_World_Shop, serialization_id)
{
  Shop s;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_SHOP, s.get_class_identifier());
}

TEST(SW_World_Shop, saveload)
{
  Shop s("abc123", "foo", {12,3}, {14,5}, {ItemType::ITEM_TYPE_ARMOUR, ItemType::ITEM_TYPE_SCROLL});

  Shop s2;

  ostringstream ss;

  s.serialize(ss);

  istringstream iss(ss.str());

  s2.deserialize(iss);

  EXPECT_TRUE(s == s2);
}

