#include "gtest/gtest.h"

TEST(SW_Engine_Commands_SelectTile_TileSelectionCommandFactory, serialization_id)
{
  TileSelectionCommandFactory tscf;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_TILE_SELECTION_COMMAND_FACTORY, tscf.get_class_identifier());
}

