#include "gtest/gtest.h"

TEST(SL_World_Tiles_SiteOfDeathTile, type_is_TILE_TYPE_SITE_OF_DEATH)
{
  SiteOfDeathTile site_of_death_tile;

  EXPECT_EQ(TILE_TYPE_SITE_OF_DEATH, site_of_death_tile.get_tile_type());
}

TEST(SL_World_Tiles_SiteOfDeathTile, tile_description_sid)
{
  SiteOfDeathTile site_of_death_tile;

  EXPECT_EQ(TileTextKeys::TILE_DESC_SITE_OF_DEATH, site_of_death_tile.get_tile_description_sid());
}

TEST(SL_World_Tiles_SiteOfDeathTile, serialization_id)
{
  SiteOfDeathTile site_of_death_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_SITE_OF_DEATH_TILE, site_of_death_tile.get_class_identifier());
}

