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
const string TileProperties::TILE_PROPERTY_PREVIOUS_MAP_ID = "TILE_PROPERTY_PREVIOUS_MAP_ID";
const string TileProperties::TILE_PROPERTY_ORIGINAL_MAP_ID = "TILE_PROPERTY_ORIGINAL_MAP_ID";
const string TileProperties::TILE_PROPERTY_DEPTH_INCREMENT = "TILE_PROPERTY_DEPTH_INCREMENT";
const string TileProperties::TILE_PROPERTY_FLORA_TILE_DESCRIPTION_SID = "TP_FLORA_TILE_DESC_SID";

// Generate the string used to identify the custom map ID of a particular depth
// in the dungeon or world.  A custom map ID for two levels deep in the dungeon
// would be "-2_MAP_ID".  One that was five levels up (in a tower, etc) would
// be "5_MAP_ID".
string TileProperties::get_depth_custom_map_id(const int depth)
{
  ostringstream ss;
  ss << depth << "_MAP_ID";

  return ss.str();
}

#ifdef UNIT_TESTS
#include "unit_tests/TileProperties_test.cpp"
#endif
