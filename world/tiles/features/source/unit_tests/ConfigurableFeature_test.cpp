#include "gtest/gtest.h"

TEST(SW_World_Tiles_Features_ConfigurableFeature, serialization_id)
{
  Symbol s('$', Colour::COLOUR_BLUE);
  ConfigurableFeature cf(s);

  EXPECT_EQ(ClassIdentifier::CLASS_ID_CONFIGURABLE_FEATURE, cf.get_class_identifier());
}

TEST(SW_World_Tiles_Features_ConfigurableFeature, saveload)
{
  Symbol s('$', Colour::COLOUR_BLUE);
  Symbol s2('a', Colour::COLOUR_BLUE);
  ConfigurableFeature cf(s, MaterialType::MATERIAL_TYPE_STONE, "asdf");

  ostringstream ss;

  cf.serialize(ss);

  ConfigurableFeature cf2(s2);

  istringstream iss(ss.str());

  cf2.deserialize(iss);

  pair<string, vector<string>> exp_replace = {"asdf", {}};
  EXPECT_EQ(MaterialType::MATERIAL_TYPE_STONE, cf2.get_material_type());
  EXPECT_EQ('$', cf2.get_symbol().get_symbol());
  EXPECT_EQ(Colour::COLOUR_BLUE, cf2.get_colour());
  EXPECT_EQ(exp_replace, cf2.get_description_and_replacement_sids());
}

