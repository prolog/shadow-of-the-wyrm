#include "gtest/gtest.h"

TEST(SL_Engine_MapExit, serialization_id)
{
  MapExit map_exit;

  EXPECT_EQ(CLASS_ID_MAP_EXIT, map_exit.get_class_identifier());
}

