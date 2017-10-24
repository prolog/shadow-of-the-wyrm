#include "gtest/gtest.h"

TEST(SW_World_Tiles_FloatingTowerTile, type_is_TILE_TYPE_FLOATING_TOWER)
{
  FloatingTowerTile floating_tower_tile;

  EXPECT_EQ(TileType::TILE_TYPE_FLOATING_TOWER, floating_tower_tile.get_tile_type());
}

TEST(SW_World_Tiles_FloatingTowerTile, tile_description_sid)
{
  FloatingTowerTile floating_tower_tile;

  EXPECT_EQ(TileTextKeys::TILE_DESC_FLOATING_TOWER, floating_tower_tile.get_tile_description_sid());
}

TEST(SW_World_Tiles_FloatingTowerTile, serialization_id)
{
  FloatingTowerTile floating_tower_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_FLOATING_TOWER_TILE, floating_tower_tile.get_class_identifier());
}


