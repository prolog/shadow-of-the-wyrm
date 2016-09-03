#include "MapProperties.hpp"

using namespace std;

MapProperties::MapProperties()
{
}

MapProperties::~MapProperties()
{
}

const string MapProperties::MAP_PROPERTIES_PERMANENCE = "MAP_PROPERTIES_PERMANENCE";
const string MapProperties::MAP_PROPERTIES_GENERATED_MAP_ID = "MAP_PROPERTIES_GENERATED_MAP_ID";
const string MapProperties::MAP_PROPERTIES_WORLD_MAP_LOCATION = "MAP_PROPERTIES_WORLD_MAP_LOCATION";
const string MapProperties::MAP_PROPERTIES_WORLD_MAP_HEIGHT = "MAP_PROPERTIES_WORLD_MAP_HEIGHT";
const string MapProperties::MAP_PROPERTIES_INITIAL_CREATURES = "MAP_PROPERTIES_INITIAL_CREATURES";
const string MapProperties::MAP_PROPERTIES_GENERATOR_FILTERS = "MAP_PROPERTIES_GENERATOR_FILTERS";
const string MapProperties::MAP_PROPERTIES_IGNORE_CREATURE_LVL_CHECKS = "MAP_PROPERTIES_IGNORE_CREATURE_LVL_CHECKS";
const string MapProperties::MAP_PROPERTIES_GENERATED_CREATURE_RACE_ID = "MAP_PROPERTIES_GENERATED_CREATURE_RACE_ID";
const string MapProperties::MAP_PROPERTIES_FEATURE_ENTRY_TEXT_SIDS = "MAP_PROPERTIES_FEATURE_ENTRY_TEXT_SIDS";
const string MapProperties::MAP_PROPERTIES_CANNOT_DIG = "MAP_PROPERTIES_CANNOT_DIG";
const string MapProperties::MAP_PROPERTIES_CANNOT_TELEPORT = "MAP_PROPERTIES_CANNOT_TELEPORT";
const string MapProperties::MAP_PROPERTIES_CREATURE_GENERATION_RATE = "MAP_PROPERTIES_CREATURE_GENERATION_RATE";
const string MapProperties::MAP_PROPERTIES_PCT_CHANCE_FORAGABLES = "MAP_PROPERTIES_PCT_CHANCE_FORAGABLES";
const string MapProperties::MAP_PROPERTIES_PCT_CHANCE_HERBS = "MAP_PROPERTIES_PCT_CHANCE_HERBS";
const string MapProperties::MAP_PROPERTIES_RELIC_ID = "MAP_PROPERTIES_RELIC_ID";
const string MapProperties::MAP_PROPERTIES_CREATURE_IDS = "MAP_PROPERTIES_CREATURE_IDS";

UnderworldProperties::UnderworldProperties()
{
}

UnderworldProperties::~UnderworldProperties()
{
}

// If present, used to set the depth of the map.
const string UnderworldProperties::UNDERWORLD_STRUCTURE_DEPTH = "UNDERWORLD_STRUCTURE_DEPTH";

// If present, used (along with the current depth) to determine whether down
// staircases should be generated.
const string UnderworldProperties::UNDERWORLD_STRUCTURE_MAX_DEPTH = "UNDERWORLD_STRUCTURE_MAX_DEPTH";

