#include "gtest/gtest.h"

TEST(SW_Engine_MapExit, serialization_id)
{
  MapExit map_exit;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_MAP_EXIT, map_exit.get_class_identifier());
}

