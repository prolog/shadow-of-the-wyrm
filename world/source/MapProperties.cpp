#include "MapProperties.hpp"

using namespace std;

MapProperties::MapProperties()
{
}

MapProperties::~MapProperties()
{
}

const string MapProperties::MAP_PROPERTIES_PERMANENCE = "MAP_PROPERTIES_PERMANENCE";
const string MapProperties::MAP_PROPERTIES_WORLD_MAP_LOCATION = "MAP_PROPERTIES_WORLD_MAP_LOCATION";
const string MapProperties::MAP_PROPERTIES_WORLD_MAP_HEIGHT = "MAP_PROPERTIES_WORLD_MAP_HEIGHT";

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

