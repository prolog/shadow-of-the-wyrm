#include "gtest/gtest.h"

TEST(SL_World_Tiles_FieldTile, type_is_TILE_TYPE_FIELD)
{
  FieldTile field_tile;

  EXPECT_EQ(TILE_TYPE_FIELD, field_tile.get_tile_type());
}

TEST(SL_World_Tiles_FieldTile, serialization_id)
{
  FieldTile field_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_FIELD_TILE, field_tile.get_class_identifier());
}

