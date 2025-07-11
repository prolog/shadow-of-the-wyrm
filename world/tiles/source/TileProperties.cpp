#include <sstream>
#include "TileProperties.hpp"

using namespace std;

TileProperties::TileProperties()
{
}

TileProperties::~TileProperties()
{
}

const string TileProperties::TILE_PROPERTY_EXTRA_DESCRIPTION_SID = "TILE_PROPERTY_EXTRA_DESCRIPTION_SID";
const string TileProperties::TILE_PROPERTY_CUSTOM_MAP_ID = "TILE_PROPERTY_CUSTOM_MAP_ID";
const string TileProperties::TILE_PROPERTY_LINKED_COORD = "TILE_PROPERTY_LINKED_COORD";
const string TileProperties::TILE_PROPERTY_PREVIOUS_MAP_ID = "TILE_PROPERTY_PREVIOUS_MAP_ID";
const string TileProperties::TILE_PROPERTY_ORIGINAL_MAP_ID = "TILE_PROPERTY_ORIGINAL_MAP_ID";
const string TileProperties::TILE_PROPERTY_DEPTH_INCREMENT = "TILE_PROPERTY_DEPTH_INCREMENT";
const string TileProperties::TILE_PROPERTY_FLORA_TILE_DESCRIPTION_SID = "TP_FLORA_TILE_DESC_SID";
const string TileProperties::TILE_PROPERTY_RUINED = "TILE_PROPERTY_RUINED";
const string TileProperties::TILE_PROPERTY_CASTLE_TYPE = "TILE_PROPERTY_CASTLE_TYPE";
const string TileProperties::TILE_PROPERTY_SETTLEMENT_TYPE = "TILE_PROPERTY_SETTLEMENT_TYPE";
const string TileProperties::TILE_PROPERTY_NO_OVERWRITE = "TILE_PROPERTY_NO_OVERWRITE";
const string TileProperties::TILE_PROPERTY_PREVIOUSLY_DUG = "TILE_PROPERTY_PREVIOUSLY_DUG";
const string TileProperties::TILE_PROPERTY_PLANTED = "TILE_PROPERTY_PLANTED";
const string TileProperties::TILE_PROPERTY_ENGRAVING_SID = "TILE_PROPERTY_ENGRAVING_SID";
const string TileProperties::TILE_PROPERTY_INSCRIPTION_SID = "TILE_PROPERTY_INSCRIPTION_SID";
const string TileProperties::TILE_PROPERTY_WATER_TYPE = "TILE_PROPERTY_WATER_TYPE";
const string TileProperties::TILE_PROPERTY_ALLOWED_RACES = "TILE_PROPERTY_ALLOWED_RACES";
const string TileProperties::TILE_PROPERTY_ALLOWED_CREATURE_IDS = "TILE_PROPERTY_ALLOWED_CREATURE_IDS";
const string TileProperties::TILE_PROPERTY_CANNOT_DIG = "TILE_PROPERTY_CANNOT_DIG";
const string TileProperties::TILE_PROPERTY_CLAY = "TILE_PROPERTY_CLAY";
const string TileProperties::TILE_PROPERTY_REMAINS = "TILE_PROPERTY_REMAINS";
const string TileProperties::TILE_PROPERTY_PCT_CHANCE_ITEMS = "TILE_PROPERTY_PCT_CHANCE_ITEMS";
const string TileProperties::TILE_PROPERTY_PCT_CHANCE_UNDEAD = "TILE_PROPERTY_PCT_CHANCE_UNDEAD";

// Represents the non-number part of a depth custom map ID key.
const string TileProperties::CUSTOM_MAP_ID_PART = "_CUSTOM_MAP_ID";

const string TileProperties::TILE_PROPERTY_NAME = "TILE_PROPERTY_NAME";

const string TileProperties::TILE_PROPERTY_MIN_LORE_REQUIRED = "TILE_PROPERTY_MIN_LORE_REQUIRED";
const string TileProperties::TILE_PROPERTY_TREASURE_SOURCE = "TILE_PROPERTY_TREASURE_SOURCE";
const string TileProperties::TILE_PROPERTY_UNDERWATER_MIN_LORE_REQUIRED = "TILE_PROPERTY_UNDERWATER_MIN_LORE_REQUIRED";
const string TileProperties::TILE_PROPERTY_UNDERWATER_TREASURE_SOURCE = "TILE_PROPERTY_UNDERWATER_TREASURE_SOURCE";

const string TileProperties::TILE_PROPERTY_UNPROTECTED_MOVEMENT_IS_DEATH = "TILE_PROPERTY_UNPROTECTED_MOVEMENT_IS_DEATH";

// Generate the string used to identify the custom map ID of a particular depth
// in the dungeon or world.  A custom map ID for two levels deep in the dungeon
// would be "-2_MAP_ID".  One that was five levels up (in a tower, etc) would
// be "5_MAP_ID".
string TileProperties::get_depth_custom_map_id(const int depth)
{
  ostringstream ss;
  ss << depth << CUSTOM_MAP_ID_PART;

  return ss.str();
}

bool TileProperties::is_depth_custom_map_id(const string& key)
{
  return (key.find(CUSTOM_MAP_ID_PART) != string::npos);
}

#ifdef UNIT_TESTS
#include "unit_tests/TileProperties_test.cpp"
#endif
