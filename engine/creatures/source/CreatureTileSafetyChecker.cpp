#include <boost/foreach.hpp>
#include <boost/make_shared.hpp>
#include "CreatureTileSafetyChecker.hpp"
#include "WaterSafetyCondition.hpp"

using namespace std;

CreatureTileSafetyChecker::CreatureTileSafetyChecker()
{
  initialize_tile_safety_conditions();
}

// Check to see if the tile is safe for the creature:
// - Is it safe for all tile type safety conditions?
// - Is it safe for all tile super type safety conditions?
bool CreatureTileSafetyChecker::is_tile_safe_for_creature(CreaturePtr creature, TilePtr tile)
{
  bool tile_safe = false;

  if (creature && tile)
  {
    if (are_safety_conditions_satisfied(creature, tile, get_safety_conditions(tile->get_tile_type())) &&
        are_safety_conditions_satisfied(creature, tile, get_safety_conditions(tile->get_tile_super_type())))
    {
      tile_safe = true;
    }
  }

  return tile_safe;
}

bool CreatureTileSafetyChecker::are_safety_conditions_satisfied(CreaturePtr creature, TilePtr tile, const vector<ITileSafetyConditionPtr>& safety_conditions)
{
  bool safety_conditions_satisfied = true;

  BOOST_FOREACH(ITileSafetyConditionPtr safety_condition, safety_conditions)
  {
    safety_conditions_satisfied = safety_condition && safety_condition->is_safe(creature, tile);

    if (safety_conditions_satisfied == false)
    {
      break;
    }
  }

  return safety_conditions_satisfied;
}

// Get the safety conditions for a particular tile type
vector<ITileSafetyConditionPtr> CreatureTileSafetyChecker::get_safety_conditions(const TileType tile_type)
{
  vector<ITileSafetyConditionPtr> safety_conditions;

  TileTypeSafetyConditionsMap::iterator t_it = tile_type_safety_conditions.find(tile_type);
  if (t_it != tile_type_safety_conditions.end())
  {
    safety_conditions = t_it->second;
  }

  return safety_conditions;
}

// Get the safety conditions for a particular tile super type
// Get the safety conditions for a particular tile type
vector<ITileSafetyConditionPtr> CreatureTileSafetyChecker::get_safety_conditions(const TileSuperType tile_super_type)
{
  vector<ITileSafetyConditionPtr> safety_conditions;

  TileSuperTypeSafetyConditionsMap::iterator t_it = tile_super_type_safety_conditions.find(tile_super_type);
  if (t_it != tile_super_type_safety_conditions.end())
  {
    safety_conditions = t_it->second;
  }

  return safety_conditions;
}

// Initialize the safety conditions for the tile types and tile super types.
void CreatureTileSafetyChecker::initialize_tile_safety_conditions()
{
  initialize_tile_type_safety_conditions();
  initialize_tile_super_type_safety_conditions();
}

// Initialize all the tile-type-based conditions.
void CreatureTileSafetyChecker::initialize_tile_type_safety_conditions()
{
}

// Initialize all the tile-super-type-based conditions.
void CreatureTileSafetyChecker::initialize_tile_super_type_safety_conditions()
{
  vector<ITileSafetyConditionPtr> water_conditions;
  ITileSafetyConditionPtr water_condition = boost::make_shared<WaterSafetyCondition>();
  water_conditions.push_back(water_condition);

  tile_super_type_safety_conditions.insert(make_pair(TILE_SUPER_TYPE_WATER, water_conditions));
}
