#include "gtest/gtest.h"

TEST(SL_World_Tiles_Features_Fountain, serialization_id)
{
  Fountain fountain;

  EXPECT_EQ(CLASS_ID_FOUNTAIN, fountain.get_class_identifier());
}

