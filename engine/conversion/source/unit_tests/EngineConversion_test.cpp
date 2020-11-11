#include "gtest/gtest.h"
#include "Amulet.hpp"

TEST(SW_Engine_EngineConversionRoutines, direction_to_string)
{
  EXPECT_EQ(CommandKeys::MOVE_SOUTHEAST, DirectionEnum::to_string(Direction::DIRECTION_SOUTH_EAST));
  EXPECT_EQ(CommandKeys::MOVE_SOUTH, DirectionEnum::to_string(Direction::DIRECTION_SOUTH));
  EXPECT_EQ(CommandKeys::MOVE_SOUTHWEST, DirectionEnum::to_string(Direction::DIRECTION_SOUTH_WEST));
  EXPECT_EQ(CommandKeys::MOVE_EAST, DirectionEnum::to_string(Direction::DIRECTION_EAST));
  EXPECT_EQ(CommandKeys::MOVE_WEST, DirectionEnum::to_string(Direction::DIRECTION_WEST));
  EXPECT_EQ(CommandKeys::MOVE_NORTHWEST, DirectionEnum::to_string(Direction::DIRECTION_NORTH_WEST));
  EXPECT_EQ(CommandKeys::MOVE_NORTH, DirectionEnum::to_string(Direction::DIRECTION_NORTH));
  EXPECT_EQ(CommandKeys::MOVE_NORTHEAST, DirectionEnum::to_string(Direction::DIRECTION_NORTH_EAST));
}

TEST(SW_Engine_EngineConversionRoutines, handedness_to_rotation_direction)
{
  EXPECT_EQ(RotationDirection::ROTATION_DIRECTION_CLOCKWISE, HandednessEnum::to_rotation_direction(Handedness::LEFT_HANDED));
  EXPECT_EQ(RotationDirection::ROTATION_DIRECTION_COUNTERCLOCKWISE, HandednessEnum::to_rotation_direction(Handedness::RIGHT_HANDED));
}

TEST(SW_Engine_EngineConversionRoutines, raw_hunger_to_hunger_level)
{
  EXPECT_EQ(HungerLevel::HUNGER_LEVEL_STUFFED, HungerLevelConverter::to_hunger_level(HungerLevelConverter::INT_HUNGER_LEVEL_STUFFED));
  EXPECT_EQ(HungerLevel::HUNGER_LEVEL_FULL, HungerLevelConverter::to_hunger_level(HungerLevelConverter::INT_HUNGER_LEVEL_FULL));
  EXPECT_EQ(HungerLevel::HUNGER_LEVEL_NORMAL, HungerLevelConverter::to_hunger_level(HungerLevelConverter::INT_HUNGER_LEVEL_NORMAL));
  EXPECT_EQ(HungerLevel::HUNGER_LEVEL_HUNGRY, HungerLevelConverter::to_hunger_level(HungerLevelConverter::INT_HUNGER_LEVEL_HUNGRY));
  EXPECT_EQ(HungerLevel::HUNGER_LEVEL_STARVING, HungerLevelConverter::to_hunger_level(HungerLevelConverter::INT_HUNGER_LEVEL_STARVING));
  EXPECT_EQ(HungerLevel::HUNGER_LEVEL_DYING, HungerLevelConverter::to_hunger_level(HungerLevelConverter::INT_HUNGER_LEVEL_DYING));
}

TEST(SW_Engine_EngineConversionRoutines, grams_per_standard_drink)
{
  EXPECT_FLOAT_EQ(13.6f, AlcoholConverter::standard_drinks_to_grams(1.0f));
  EXPECT_FLOAT_EQ(27.2f, AlcoholConverter::standard_drinks_to_grams(2.0f));
  EXPECT_FLOAT_EQ(34.0f, AlcoholConverter::standard_drinks_to_grams(2.5f));
}

TEST(SW_Engine_EngineConversionRoutines, weight_to_burden_level)
{
  CreaturePtr c = std::make_shared<Creature>();
  Statistic strength(10);
  c->set_strength(10);
  c->set_size(CreatureSize::CREATURE_SIZE_MEDIUM);

  ItemPtr amulet = std::make_shared<Amulet>();
  Weight amulet_weight;
  amulet_weight.set_weight(16); // 1 lb
  amulet->set_weight(amulet_weight);

  c->get_inventory()->add_front(amulet);

  EXPECT_EQ(BurdenLevel::BURDEN_LEVEL_UNBURDENED, BurdenLevelConverter::to_burden_level(c));

  amulet->set_quantity(125);

  EXPECT_EQ(BurdenLevel::BURDEN_LEVEL_BURDENED, BurdenLevelConverter::to_burden_level(c));

  amulet->set_quantity(175);

  EXPECT_EQ(BurdenLevel::BURDEN_LEVEL_STRAINED, BurdenLevelConverter::to_burden_level(c));

  amulet->set_quantity(325);

  EXPECT_EQ(BurdenLevel::BURDEN_LEVEL_OVERBURDENED, BurdenLevelConverter::to_burden_level(c));
}

TEST(SW_Engine_EngineConversion_MapTileTypes, default_tile_type)
{
  EXPECT_EQ(TileType::TILE_TYPE_FIELD, MapTileTypes::map_type_to_default_tile_type(MapType::MAP_TYPE_WORLD));
  EXPECT_EQ(TileType::TILE_TYPE_FIELD, MapTileTypes::map_type_to_default_tile_type(MapType::MAP_TYPE_OVERWORLD));
  EXPECT_EQ(TileType::TILE_TYPE_DUNGEON_COMPLEX, MapTileTypes::map_type_to_default_tile_type(MapType::MAP_TYPE_UNDERWORLD));
  EXPECT_EQ(TileType::TILE_TYPE_SEA, MapTileTypes::map_type_to_default_tile_type(MapType::MAP_TYPE_UNDERWATER));
}