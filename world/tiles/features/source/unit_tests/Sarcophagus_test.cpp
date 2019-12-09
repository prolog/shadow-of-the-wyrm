#include "gtest/gtest.h"

TEST(SW_World_Tiles_Features_Sarcophagus, serialization_id)
{
  Symbol s('_', Colour::COLOUR_WHITE);
  Sarcophagus sar(s);

  EXPECT_EQ(ClassIdentifier::CLASS_ID_SARCOPHAGUS, sar.get_class_identifier());
}

TEST(SW_World_Tiles_Features_Sarcophagus, saveload)
{
  Symbol s('_', Colour::COLOUR_WHITE);
  Sarcophagus sar(s);
  Sarcophagus sar2(s);

  sar.set_inscription_sid("fdsaasdf");

  ostringstream oss;

  sar.serialize(oss);

  istringstream iss(oss.str());

  sar2.deserialize(iss);

  EXPECT_TRUE(sar == sar2);
}
