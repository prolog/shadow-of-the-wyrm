#include "gtest/gtest.h"

TEST(SL_World_Tiles_GraveyardTile, type_is_TILE_TYPE_GRAVEYARD)
{
  GraveyardTile graveyard_tile;

  EXPECT_EQ(TILE_TYPE_GRAVEYARD, graveyard_tile.get_tile_type());
}

TEST(SL_World_Tiles_GraveyardTile, tile_description_sid)
{
  GraveyardTile graveyard_tile;

  EXPECT_EQ(TileTextKeys::TILE_DESC_GRAVEYARD, graveyard_tile.get_tile_description_sid());
}

