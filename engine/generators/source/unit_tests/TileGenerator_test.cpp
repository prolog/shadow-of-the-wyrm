#include "gtest/gtest.h"

TEST(SL_Engine_Generators_TileGenerators, tile_types_correct)
{
  TilePtr tile;

  for (TileType tile_type = TILE_TYPE_FIRST; tile_type < TILE_TYPE_LAST; tile_type++)
  {
    tile = TileGenerator::generate(tile_type);

    EXPECT_EQ(tile_type, tile->get_tile_type());
  }
}
