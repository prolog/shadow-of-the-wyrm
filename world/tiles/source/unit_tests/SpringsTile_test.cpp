#include "gtest/gtest.h"

TEST(SW_World_Tiles_SpringsTile, type_is_TILE_TYPE_SPRINGS)
{
  SpringsTile springs_tile;

  EXPECT_EQ(TileType::TILE_TYPE_SPRINGS, springs_tile.get_tile_type());
}

TEST(SW_World_Tiles_SpringsTile, different_description_SID_for_hot_springs)
{
  SpringsTile springs;
  SpringsTile hot_springs;

  hot_springs.set_temperature(static_cast<int>(SpringsTemperature::SPRINGS_TEMPERATURE_HOT));

  EXPECT_FALSE(springs.get_tile_description_sid() == hot_springs.get_tile_description_sid());
}

TEST(SW_World_Tiles_SpringsTile, serialization_id)
{
  SpringsTile springs_tile;

  EXPECT_EQ(ClassIdentifier::CLASS_ID_SPRINGS_TILE, springs_tile.get_class_identifier());
}

TEST(SW_World_Tiles_SpringsTile, saveload)
{
  SpringsTile springs;
  SpringsTile hot_springs, hot_springs2;
  hot_springs.set_temperature(75);

  ostringstream oss;

  hot_springs.serialize(oss);

  istringstream iss(oss.str());

  hot_springs2.deserialize(iss);

  EXPECT_TRUE(hot_springs == hot_springs2);
  EXPECT_FALSE(hot_springs == springs);
}