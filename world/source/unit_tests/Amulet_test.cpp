#include "gtest/gtest.h"

TEST(SW_World_Amulet, enchanting_increments_status)
{
  Amulet a;
  a.set_status(ItemStatus::ITEM_STATUS_CURSED);

  a.enchant(0, 1);
  EXPECT_TRUE(a.get_status() == ItemStatus::ITEM_STATUS_UNCURSED);

  a.enchant(0, 1);
  EXPECT_TRUE(a.get_status() == ItemStatus::ITEM_STATUS_BLESSED);

  a.enchant(0, 1);
  EXPECT_TRUE(a.get_status() == ItemStatus::ITEM_STATUS_BLESSED);
}

TEST(SW_World_Amulet, enchantment_value_progression)
{
  Amulet a;
  a.set_value(1);

  vector<int> new_values = { 41, 81, 121, 161 };

  for (int i = 0; i < 4; i++)
  {
    a.enchant(10, 1);

    EXPECT_EQ(new_values[i], a.get_value());
  }

  Amulet a2;
  a2.set_value(1);
  a2.enchant(10, 4);

  EXPECT_EQ(new_values[3], a2.get_value());
}

TEST(SW_World_Amulet, smithing_value_progression)
{
  Amulet a;

  a.set_value(300);

  vector<int> new_values = { 340, 380, 420, 462 /* last one becomes 10% */ };

  for (int i = 0; i < 4; i++)
  {
    a.enchant(10, 1);

    EXPECT_EQ(new_values[i], a.get_value());
  }

  Amulet a2;
  a2.set_value(300);
  a2.smith(4);

  EXPECT_EQ(new_values[3], a2.get_value());
}

TEST(SW_World_Amulet, floats)
{
  Amulet a;
  a.set_material_type(MaterialType::MATERIAL_TYPE_GOLD);

  EXPECT_FALSE(a.get_floats());

  a.set_floats(false);

  EXPECT_FALSE(a.get_floats());

  a.set_floats(true);

  EXPECT_TRUE(a.get_floats());
}

TEST(SW_World_Amulet, serialization_id)
{
  Amulet amulet;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_AMULET, amulet.get_class_identifier());
}

TEST(SW_World_Amulet, saveload)
{
  Amulet am, am2;

  ostringstream ss;

  am.set_soak(13);
  am.set_codex_description_sid("test!");

  am.serialize(ss);

  istringstream iss(ss.str());

  am2.deserialize(iss);

  EXPECT_TRUE(am == am2);
  EXPECT_EQ("test!", am2.get_codex_description_sid());
}
