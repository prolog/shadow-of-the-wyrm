#include "gtest/gtest.h"
#include "GoodAltar.hpp"
#include "NeutralAltar.hpp"
#include "EvilAltar.hpp"

TEST(SL_World_Tiles_Feature_Altar, deity_id)
{
  EvilAltar altar("test");

  EXPECT_EQ("test", altar.get_deity_id());
}

TEST(SL_World_Tiles_Feature_Altar, symbol)
{
  char sym = '_'; // common for all altars

  GoodAltar good("test1");
  NeutralAltar neutral("test2");
  EvilAltar evil("test3");
  
  EXPECT_EQ(sym, good.get_symbol());
  EXPECT_EQ(sym, neutral.get_symbol());
  EXPECT_EQ(sym, evil.get_symbol());
}

TEST(SL_World_Tiles_Feature_Altar, material)
{
  GoodAltar good("test1");
  NeutralAltar neutral("test2");
  EvilAltar evil("test3");

  EXPECT_EQ(MaterialType::MATERIAL_TYPE_MARBLE, good.get_material_type());
  EXPECT_EQ(MaterialType::MATERIAL_TYPE_STONE, neutral.get_material_type());
  EXPECT_EQ(MaterialType::MATERIAL_TYPE_ONYX, evil.get_material_type());
}

TEST(SL_World_Tiles_Feature_Altar, serialization_id)
{
  GoodAltar good("test1");
  NeutralAltar neutral("test2");
  EvilAltar evil("test3");

  EXPECT_EQ(ClassIdentifier::CLASS_ID_GOOD_ALTAR, good.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_NEUTRAL_ALTAR, neutral.get_class_identifier());
  EXPECT_EQ(ClassIdentifier::CLASS_ID_EVIL_ALTAR, evil.get_class_identifier());
}

