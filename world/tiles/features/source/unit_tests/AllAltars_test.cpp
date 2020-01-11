#include "gtest/gtest.h"

TEST(SW_World_Tiles_Feature_Altar, deity_id)
{
  Symbol s('_', Colour::COLOUR_WHITE);
  EvilAltar altar(s, "test");

  EXPECT_EQ("test", altar.get_deity_id());
}

TEST(SW_World_Tiles_Feature_Altar, symbol)
{
  char sym = '_'; // common for all altars
  Symbol s('_', Colour::COLOUR_WHITE);

  GoodAltar good(s, "test1");
  NeutralAltar neutral(s, "test2");
  EvilAltar evil(s, "test3");
  
  EXPECT_EQ(sym, good.get_symbol().get_symbol());
  EXPECT_EQ(sym, neutral.get_symbol().get_symbol());
  EXPECT_EQ(sym, evil.get_symbol().get_symbol());
}

TEST(SW_World_Tiles_Feature_Altar, material)
{
  Symbol s('_', Colour::COLOUR_WHITE);

  GoodAltar good(s, "test1");
  NeutralAltar neutral(s, "test2");
  EvilAltar evil(s, "test3");

  EXPECT_EQ(MaterialType::MATERIAL_TYPE_MARBLE, good.get_material_type());
  EXPECT_EQ(MaterialType::MATERIAL_TYPE_STONE, neutral.get_material_type());
  EXPECT_EQ(MaterialType::MATERIAL_TYPE_ONYX, evil.get_material_type());
}

TEST(SW_World_Tiles_Feature_Altar, serialization_id)
{
  Symbol s('_', Colour::COLOUR_WHITE);
  GoodAltar good(s, "test1");
  NeutralAltar neutral(s, "test2");
  EvilAltar evil(s, "test3");

  EXPECT_EQ(ClassIdentifier::CLASS_ID_GOOD_ALTAR, good.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_NEUTRAL_ALTAR, neutral.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_EVIL_ALTAR, evil.get_class_identifier());
}

