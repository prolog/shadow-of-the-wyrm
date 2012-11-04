#include "gtest/gtest.h"

class SL_Engine_Actions_TileSelectionManager : public ::testing::Test
{
  protected:
    ClassIdentifier get_class_identifier() { return tsm.get_class_identifier(); }

    TileSelectionManager tsm;
};

TEST_F(SL_Engine_Actions_TileSelectionManager, serialization_id)
{
  EXPECT_EQ(CLASS_ID_TILE_SELECTION_MANAGER, get_class_identifier());
}

