#pragma once
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "ActionCost.hpp"
#include "common.hpp"
#include "Creature.hpp"
#include "Directions.hpp"
#include "EquipmentTypes.hpp"
#include "MapTypes.hpp"
#include "StatusTypes.hpp"

class DirectionEnum
{
  public:
    static std::string to_string(const Direction d);
    static std::string to_attack_string(const Direction d);

  protected:
    DirectionEnum();
    ~DirectionEnum();
};

class HandednessEnum
{
  public:
    static RotationDirection to_rotation_direction(const Handedness h);

  protected:
    HandednessEnum();
    ~HandednessEnum();
};

class ActionCostConverter
{
  public:
    static double to_seconds(const ActionCostValue action_cost_value, const MapType map_type);
    static double to_seconds_on_world_map(const ActionCostValue action_cost_value);
    static double to_seconds_on_submap(const ActionCostValue action_cost_value);
  protected:
    ActionCostConverter();
    ~ActionCostConverter();
};

class HungerLevelConverter
{
  public:
    static HungerLevel to_hunger_level(const int raw_hunger_value);

    static const int INT_HUNGER_LEVEL_COMPLETELY_FULL;
    static const int INT_HUNGER_LEVEL_STUFFED;
    static const int INT_HUNGER_LEVEL_FULL;
    static const int INT_HUNGER_LEVEL_NORMAL;
    static const int INT_HUNGER_LEVEL_HUNGRY;
    static const int INT_HUNGER_LEVEL_STARVING;
    static const int INT_HUNGER_LEVEL_DYING;

  protected:
    HungerLevelConverter();
    ~HungerLevelConverter();
};

class BurdenLevelConverter
{
  public:
    static BurdenLevel to_burden_level(CreaturePtr creature);

  protected:
    BurdenLevelConverter();
    ~BurdenLevelConverter();
};

class AlcoholConverter
{
  public:
    static const float GRAMS_PER_STANDARD_DRINK;

    static float standard_drinks_to_absorbable_grams(const float std_drinks);
    static float standard_drinks_to_grams(const float std_drinks);

  protected:
    AlcoholConverter();
    ~AlcoholConverter();
};

class MapTileTypes
{
  public:
    static TileType map_type_to_default_tile_type(const MapType mt);

  protected:
    MapTileTypes();
    ~MapTileTypes();
};