#include "gtest/gtest.h"

TEST(SL_World_Seasons_Autumn, serialization_id)
{
  Autumn autumn;

  EXPECT_EQ(CLASS_ID_AUTUMN, autumn.get_class_identifier());
}

