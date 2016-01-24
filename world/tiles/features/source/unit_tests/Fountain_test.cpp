#include "gtest/gtest.h"

TEST(SW_World_Tiles_Features_Fountain, serialization_id)
{
  Fountain fountain;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_FOUNTAIN, fountain.get_class_identifier());
}

