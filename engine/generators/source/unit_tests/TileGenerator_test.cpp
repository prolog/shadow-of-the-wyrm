#include "gtest/gtest.h"

TEST(SL_Engine_Generators_TileGenerators, TileType::TILE_TYPEs_correct)
{
  TilePtr tile;
  TileGenerator tg;

  for (TileType TileType::TILE_TYPE = TileType::TILE_TYPE_FIRST; TileType::TILE_TYPE < TileType::TILE_TYPE_LAST; TileType::TILE_TYPE++)
  {
    tile = tg.generate(TileType::TILE_TYPE);

    EXPECT_EQ(TileType::TILE_TYPE, tile->get_tile_type());
  }
}
