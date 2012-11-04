#include "gtest/gtest.h"

TEST(SL_Engine_Commands_SelectTile_TileSelectionKeyboardCommandMap, serialization_id)
{
  TileSelectionKeyboardCommandMap tskcm;

  EXPECT_EQ(CLASS_ID_TILE_SELECTION_KEYBOARD_COMMAND_MAP, tskcm.get_class_identifier());
}

