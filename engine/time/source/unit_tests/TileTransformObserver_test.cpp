#include "gtest/gtest.h"

TEST(SL_Engine_Time_TileTransformObserver, serialization_id)
{
  TileTransformObserver tt;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_TILE_TRANSFORM_OBSERVER, tt.get_class_identifier());
}

