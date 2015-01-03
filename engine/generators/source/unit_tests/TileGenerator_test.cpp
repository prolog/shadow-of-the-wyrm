#include "gtest/gtest.h"

TEST(SL_Engine_Generators_TileGenerators, tile_types_correct)
{
  TilePtr tile;
  TileGenerator tg;

  for (int tt = static_cast<int>(TileType::TILE_TYPE_FIRST); tt < static_cast<int>(TileType::TILE_TYPE_LAST); tt++)
  {
    TileType tile_type = static_cast<TileType>(tt);
    tile = tg.generate(tile_type);

    EXPECT_EQ(tile_type, tile->get_tile_type());
  }
}
