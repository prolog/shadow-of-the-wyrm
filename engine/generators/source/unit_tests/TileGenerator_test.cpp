#include "gtest/gtest.h"

TEST(SL_Engine_Generators_TileGenerator, tile_types_correct)
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

TEST(SL_Engine_Generators_TileGenerator, get_is_staircase)
{
  TilePtr tile;
  TileGenerator tg;

  for (int tt = static_cast<int>(TileType::TILE_TYPE_FIRST); tt < static_cast<int>(TileType::TILE_TYPE_LAST); tt++)
  {
    TileType tile_type = static_cast<TileType>(tt);
    tile = tg.generate(tile_type);

    bool expect_is_staircase = false;

    if (tile_type == TileType::TILE_TYPE_UP_STAIRCASE || tile_type == TileType::TILE_TYPE_DOWN_STAIRCASE)
    {
      expect_is_staircase = true;
    }

    EXPECT_EQ(expect_is_staircase, tile->get_is_staircase());
  }
}