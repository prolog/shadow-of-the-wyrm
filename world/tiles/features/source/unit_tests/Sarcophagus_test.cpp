#include "gtest/gtest.h"

TEST(SL_World_Tiles_Features_Sarcophagus, serialization_id)
{
  Sarcophagus sar;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_SARCOPHAGUS, sar.get_class_identifier());
}

TEST(SL_World_Tiles_Features_Sarcophagus, saveload)
{
  Sarcophagus sar, sar2;

  sar.set_inscription_sid("fdsaasdf");

  ostringstream oss;

  sar.serialize(oss);

  istringstream iss(oss.str());

  sar2.deserialize(iss);

  EXPECT_TRUE(sar == sar2);
}
