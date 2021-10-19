#include "CarryingCapacityCalculator.hpp"
#include "CommandKeys.hpp"
#include "EngineConversion.hpp"
#include "Log.hpp"

using namespace std;

DirectionEnum::DirectionEnum()
{
}

DirectionEnum::~DirectionEnum()
{
}

string DirectionEnum::to_string(const Direction d)
{
  string command_key_direction;

  switch(d)
  {
    case Direction::DIRECTION_NULL:
      command_key_direction = CommandKeys::SEARCH;
      break;
    case Direction::DIRECTION_SOUTH_WEST:
      command_key_direction = CommandKeys::MOVE_SOUTHWEST;
      break;
    case Direction::DIRECTION_SOUTH:
      command_key_direction = CommandKeys::MOVE_SOUTH;
      break;
    case Direction::DIRECTION_SOUTH_EAST:
      command_key_direction = CommandKeys::MOVE_SOUTHEAST;
      break;
    case Direction::DIRECTION_WEST:
      command_key_direction = CommandKeys::MOVE_WEST;
      break;
    case Direction::DIRECTION_EAST:
      command_key_direction = CommandKeys::MOVE_EAST;
      break;
    case Direction::DIRECTION_NORTH_WEST:
      command_key_direction = CommandKeys::MOVE_NORTHWEST;
      break;
    case Direction::DIRECTION_NORTH:
      command_key_direction = CommandKeys::MOVE_NORTH;
      break;
    case Direction::DIRECTION_NORTH_EAST:
      command_key_direction = CommandKeys::MOVE_NORTHEAST;
      break;
    case Direction::DIRECTION_UP:
    case Direction::DIRECTION_DOWN:
    default:
      break;
  }

  return command_key_direction;
}

string DirectionEnum::to_attack_string(const Direction d)
{
  string command_key_direction;

  switch(d)
  {
    case Direction::DIRECTION_NULL:
      command_key_direction = CommandKeys::SEARCH;
      break;
    case Direction::DIRECTION_SOUTH_WEST:
      command_key_direction = CommandKeys::ATTACK_SOUTHWEST;
      break;
    case Direction::DIRECTION_SOUTH:
      command_key_direction = CommandKeys::ATTACK_SOUTH;
      break;
    case Direction::DIRECTION_SOUTH_EAST:
      command_key_direction = CommandKeys::ATTACK_SOUTHEAST;
      break;
    case Direction::DIRECTION_WEST:
      command_key_direction = CommandKeys::ATTACK_WEST;
      break;
    case Direction::DIRECTION_EAST:
      command_key_direction = CommandKeys::ATTACK_EAST;
      break;
    case Direction::DIRECTION_NORTH_WEST:
      command_key_direction = CommandKeys::ATTACK_NORTHWEST;
      break;
    case Direction::DIRECTION_NORTH:
      command_key_direction = CommandKeys::ATTACK_NORTH;
      break;
    case Direction::DIRECTION_NORTH_EAST:
      command_key_direction = CommandKeys::ATTACK_NORTHEAST;
      break;
    case Direction::DIRECTION_UP:
    case Direction::DIRECTION_DOWN:
    default:
      break;
  }

  return command_key_direction;  
}

HandednessEnum::HandednessEnum()
{
}

HandednessEnum::~HandednessEnum()
{
}

RotationDirection HandednessEnum::to_rotation_direction(const Handedness h)
{
  RotationDirection rd = RotationDirection::ROTATION_DIRECTION_NULL;

  switch (h)
  {
    case Handedness::LEFT_HANDED:
      rd = RotationDirection::ROTATION_DIRECTION_CLOCKWISE;
      break;
    case Handedness::RIGHT_HANDED:
    default:
      rd = RotationDirection::ROTATION_DIRECTION_COUNTERCLOCKWISE;
      break;
  }

  return rd;
}

double ActionCostConverter::to_seconds(const ActionCostValue action_cost_value, const MapType map_type)
{
  double seconds = 0.0;
  
  if (map_type == MapType::MAP_TYPE_WORLD)
  {
    seconds = ActionCostConverter::to_seconds_on_world_map(action_cost_value);
  }
  else
  {
    seconds = ActionCostConverter::to_seconds_on_submap(action_cost_value);
  }
  
  return seconds;
}

// Each action on the world map takes the action cost in minutes, times 1.5.  So moving at a base speed
// of 50 would take 75 minutes.
double ActionCostConverter::to_seconds_on_world_map(const ActionCostValue action_cost_value)
{
  return (static_cast<double>(action_cost_value) * 60.0 * 1.5);
}

// Each action on a submap takes half the amount of action cost in seconds.  So moving at a base,
// default speed of 50ish would take about 25 seconds.
double ActionCostConverter::to_seconds_on_submap(const ActionCostValue action_cost_value)
{
  return (action_cost_value / 2);
}

// Convert raw hunger values to general levels
const int HungerLevelConverter::INT_HUNGER_LEVEL_COMPLETELY_FULL = 16000;
const int HungerLevelConverter::INT_HUNGER_LEVEL_STUFFED = 10000;
const int HungerLevelConverter::INT_HUNGER_LEVEL_FULL = 7500;
const int HungerLevelConverter::INT_HUNGER_LEVEL_NORMAL = 4000;
const int HungerLevelConverter::INT_HUNGER_LEVEL_HUNGRY = 2000;
const int HungerLevelConverter::INT_HUNGER_LEVEL_STARVING = 1000;
const int HungerLevelConverter::INT_HUNGER_LEVEL_DYING = 0;

HungerLevelConverter::HungerLevelConverter()
{
}

HungerLevelConverter::~HungerLevelConverter()
{
}

HungerLevel HungerLevelConverter::to_hunger_level(const int hunger)
{
  HungerLevel hunger_level = HungerLevel::HUNGER_LEVEL_NORMAL;

  if (hunger > INT_HUNGER_LEVEL_FULL)
  {
    hunger_level = HungerLevel::HUNGER_LEVEL_STUFFED;
  }
  else if (hunger <= INT_HUNGER_LEVEL_FULL && hunger > INT_HUNGER_LEVEL_NORMAL)
  {
    hunger_level = HungerLevel::HUNGER_LEVEL_FULL;
  }
  else if (hunger <= INT_HUNGER_LEVEL_HUNGRY && hunger > INT_HUNGER_LEVEL_STARVING)
  {
    hunger_level = HungerLevel::HUNGER_LEVEL_HUNGRY;
  }
  else if (hunger <= INT_HUNGER_LEVEL_STARVING && hunger > INT_HUNGER_LEVEL_DYING)
  {
    hunger_level = HungerLevel::HUNGER_LEVEL_STARVING;
  }
  else if (hunger <= INT_HUNGER_LEVEL_DYING)
  {
    hunger_level = HungerLevel::HUNGER_LEVEL_DYING;
  }

  return hunger_level;
}

BurdenLevelConverter::BurdenLevelConverter()
{
}

BurdenLevelConverter::~BurdenLevelConverter()
{
}

BurdenLevel BurdenLevelConverter::to_burden_level(CreaturePtr c)
{
  BurdenLevel bl = BurdenLevel::BURDEN_LEVEL_UNBURDENED;

  if (c != nullptr)
  {
    CarryingCapacityCalculator ccc;
    uint weight_carried = c->get_weight_carried();

    if (weight_carried >= ccc.calculate_overburdened_weight(c))
    {
      bl = BurdenLevel::BURDEN_LEVEL_OVERBURDENED;
    }
    else if (weight_carried >= ccc.calculate_strained_weight(c))
    {
      bl = BurdenLevel::BURDEN_LEVEL_STRAINED;
    }
    else if (weight_carried >= ccc.calculate_burdened_weight(c))
    {
      bl = BurdenLevel::BURDEN_LEVEL_BURDENED;
    }
  }

  return bl;
}

// Alcohol conversion routines!  The sign that my roguelike has gone off
// the rails.
//
// Using the Canadian/US standard drink of 13.6g/std_drink
const float AlcoholConverter::GRAMS_PER_STANDARD_DRINK = 13.6f;

AlcoholConverter::AlcoholConverter()
{
}

AlcoholConverter::~AlcoholConverter()
{
}

float AlcoholConverter::standard_drinks_to_absorbable_grams(const float std_drinks)
{
  float grams = standard_drinks_to_grams(std_drinks);

  // A standard drink should produce about 2g of absorbable alcohol.
  float absorbable_grams = grams * 0.14706f;
  return absorbable_grams;
}

float AlcoholConverter::standard_drinks_to_grams(const float std_drinks)
{
  return std_drinks * GRAMS_PER_STANDARD_DRINK;
}

// Tile and Map Type Conversions
MapTileTypes::MapTileTypes()
{
}

MapTileTypes::~MapTileTypes()
{
}

TileType MapTileTypes::map_type_to_default_tile_type(const MapType mt)
{
  static_assert(MapType::MAP_TYPE_LAST_INC == MapType(4), "Unrecognized MAP_TYPE_LAST_INC");
  TileType tt = TileType::TILE_TYPE_UNDEFINED;

  switch (mt)
  {
    case MapType::MAP_TYPE_WORLD:
    case MapType::MAP_TYPE_OVERWORLD:
      tt = TileType::TILE_TYPE_FIELD;
      break;
    case MapType::MAP_TYPE_UNDERWORLD:
      tt = TileType::TILE_TYPE_DUNGEON_COMPLEX;
      break;
    case MapType::MAP_TYPE_UNDERWATER:
      tt = TileType::TILE_TYPE_SEA;
      break;
    case MapType::MAP_TYPE_COSMOS:
      tt = TileType::TILE_TYPE_VOID;
    default:
      break;
  }

  return tt;
}

#ifdef UNIT_TESTS
#include "unit_tests/EngineConversion_test.cpp"
#endif
