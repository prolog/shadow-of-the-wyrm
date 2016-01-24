#include "gtest/gtest.h"

class SW_Engine_Actions_TileSelectionAction : public ::testing::Test
{
  protected:
    ClassIdentifier get_class_identifier() { return tsa.get_class_identifier(); }

    TileSelectionAction tsa;
};

TEST_F(SW_Engine_Actions_TileSelectionAction, serialization_id)
{
  EXPECT_EQ(ClassIdentifier::CLASS_ID_TILE_SELECTION_ACTION, get_class_identifier());
}

