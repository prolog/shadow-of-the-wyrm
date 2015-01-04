#include "gtest/gtest.h"

TEST(SL_World_Tiles_Features_JewelerWorkbench, serialization_id)
{
  JewelerWorkbench j;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_JEWELER_WORKBENCH, j.get_class_identifier());
}

