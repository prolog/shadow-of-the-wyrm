#include "gtest/gtest.h"

TEST(SW_World_Tiles_CryptTile, type_is_TILE_TYPE_CRYPT)
{
  CryptTile crypt_tile;

  EXPECT_EQ(TileType::TILE_TYPE_CRYPT, crypt_tile.get_tile_type());
}

TEST(SW_World_Tiles_CryptTile, tile_description_sid)
{
  CryptTile crypt_tile;

  EXPECT_EQ(TileTextKeys::TILE_DESC_CRYPT, crypt_tile.get_tile_description_sid());
}

TEST(SW_World_Tiles_CryptTile, serialization_id)
{
  CryptTile crypt_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_CRYPT_TILE, crypt_tile.get_class_identifier());
}

