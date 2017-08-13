#include "gtest/gtest.h"

TEST(SW_World_Tiles_Features_BasicFeature, serialization_id)
{
  BasicFeature bf;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_BASIC_FEATURE, bf.get_class_identifier());
}

TEST(SW_World_Tiles_Features_BasicFeature, saveload)
{
  BasicFeature bf(MaterialType::MATERIAL_TYPE_STONE, '$', Colour::COLOUR_BLUE, "asdf");

  ostringstream ss;

  bf.serialize(ss);

  BasicFeature bf2;

  istringstream iss(ss.str());

  bf2.deserialize(iss);

  pair<string, vector<string>> exp_replace = {"asdf", {}};
  EXPECT_EQ(MaterialType::MATERIAL_TYPE_STONE, bf2.get_material_type());
  EXPECT_EQ('$', bf2.get_symbol());
  EXPECT_EQ(Colour::COLOUR_BLUE, bf2.get_colour());
  EXPECT_EQ(exp_replace, bf2.get_description_and_replacement_sids());
}

