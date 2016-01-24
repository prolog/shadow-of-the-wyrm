#include "gtest/gtest.h"

TEST(SW_World_Tiles_RoadTile, type_is_TILE_TYPE_ROAD)
{
  RoadTile road_tile;

  EXPECT_EQ(TileType::TILE_TYPE_ROAD, road_tile.get_tile_type());
}

TEST(SW_World_Tiles_RoadTile, serialization_id)
{
  RoadTile road_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_ROAD_TILE, road_tile.get_class_identifier());
}
