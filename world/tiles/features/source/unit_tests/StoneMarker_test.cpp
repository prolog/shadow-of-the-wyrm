#include "gtest/gtest.h"

TEST(SW_World_Tiles_Features_StoneMarker, serialization_id)
{
  StoneMarker st;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_STONE_MARKER, st.get_class_identifier());
}

