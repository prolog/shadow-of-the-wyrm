#include "LoadedMapDetails.hpp"
#include "CoordUtils.hpp"
#include "Serialize.hpp"

using namespace std;

LoadedMapDetails::LoadedMapDetails()
: prev_engine_coord(0,0), cur_engine_coord(0,0),
  prev_display_coord(0,0), cur_display_coord(0,0),
  prev_blind_status(false), cur_blind_status(false),
  prev_season(Season::SEASON_WINTER), cur_season(Season::SEASON_WINTER)
{
}

bool LoadedMapDetails::operator==(const LoadedMapDetails& lmd) const
{
  bool result = true;

  result = result && (prev_map_id == lmd.prev_map_id);
  result = result && (cur_map_id == lmd.cur_map_id);

  result = result && (prev_engine_coord == lmd.prev_engine_coord);
  result = result && (cur_engine_coord == lmd.cur_engine_coord);

  result = result && (prev_display_coord == lmd.prev_display_coord);
  result = result && (cur_display_coord == lmd.cur_display_coord);

  result = result && (prev_blind_status == lmd.prev_blind_status);
  result = result && (cur_blind_status == lmd.cur_blind_status);

  result = result && (prev_season == lmd.prev_season);
  result = result && (cur_season == lmd.cur_season);

  return result;
}

void LoadedMapDetails::update_map_id(const string& new_map_id)
{
  prev_map_id = cur_map_id;
  cur_map_id = new_map_id;
}

void LoadedMapDetails::update_engine_coord(const Coordinate& new_engine_coord)
{
  prev_engine_coord = cur_engine_coord;
  cur_engine_coord = new_engine_coord;
}

void LoadedMapDetails::update_display_coord(const Coordinate& new_display_coord)
{
  prev_display_coord = cur_display_coord;
  cur_display_coord = new_display_coord;
}

void LoadedMapDetails::update_blind_status(const bool new_blind_status)
{
  prev_blind_status = cur_blind_status;
  cur_blind_status = new_blind_status;
}

void LoadedMapDetails::update_season(const Season& new_season)
{
  prev_season = cur_season;
  cur_season = new_season;
}

// Synchronize the previous values with the current.  Used at the end of the
// redraw routine so that the next time the player acts, any updates to the
// state variables can be used to trigger the redraw.
void LoadedMapDetails::synch()
{
  prev_map_id = cur_map_id;
  prev_engine_coord = cur_engine_coord;
  prev_display_coord = cur_display_coord;
  prev_blind_status = cur_blind_status;
  prev_season = cur_season;
}

bool LoadedMapDetails::requires_full_map_redraw() const
{
           // New map
  return ((prev_map_id != cur_map_id) ||
          // Moved > 1 coordinate (rare case - basically, teleportation)
          (CoordUtils::chebyshev_distance(prev_engine_coord, cur_engine_coord) > 1) ||
          // Display moved > 1 coordinate (as above, or moving to a different
          // sector on the world map.
          (CoordUtils::chebyshev_distance(prev_display_coord, cur_display_coord) > 1) ||
          // A change in blind status always requires a full redraw.  If the
          // player is blinded, the entire map needs to be blacked out.  If the
          // player is no longer blind, the map needs to be restored.
          (prev_blind_status != cur_blind_status) ||
          // A change in season requires full redraw so that there isn't a
          // combination of tiles all over the place.
          (prev_season != cur_season));
}

bool LoadedMapDetails::serialize(ostream& stream) const
{
  Serialize::write_string(stream, prev_map_id);
  Serialize::write_string(stream, cur_map_id);

  Serialize::write_int(stream, prev_engine_coord.first);
  Serialize::write_int(stream, prev_engine_coord.second);
  Serialize::write_int(stream, cur_engine_coord.first);
  Serialize::write_int(stream, cur_engine_coord.second);

  Serialize::write_int(stream, prev_display_coord.first);
  Serialize::write_int(stream, prev_display_coord.second);
  Serialize::write_int(stream, cur_display_coord.first);
  Serialize::write_int(stream, cur_display_coord.second);

  Serialize::write_bool(stream, prev_blind_status);
  Serialize::write_bool(stream, cur_blind_status);

  Serialize::write_enum(stream, prev_season);
  Serialize::write_enum(stream, cur_season);

  return true;
}

bool LoadedMapDetails::deserialize(istream& stream)
{
  Serialize::read_string(stream, prev_map_id);
  Serialize::read_string(stream, cur_map_id);

  Serialize::read_int(stream, prev_engine_coord.first);
  Serialize::read_int(stream, prev_engine_coord.second);
  Serialize::read_int(stream, cur_engine_coord.first);
  Serialize::read_int(stream, cur_engine_coord.second);

  Serialize::read_int(stream, prev_display_coord.first);
  Serialize::read_int(stream, prev_display_coord.second);
  Serialize::read_int(stream, cur_display_coord.first);
  Serialize::read_int(stream, cur_display_coord.second);

  Serialize::read_bool(stream, prev_blind_status);
  Serialize::read_bool(stream, cur_blind_status);

  Serialize::read_enum(stream, prev_season);
  Serialize::read_enum(stream, cur_season);

  return true;
}

ClassIdentifier LoadedMapDetails::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_LOADED_MAP_DETAILS;
}

#ifdef UNIT_TESTS
#include "unit_tests/LoadedMapDetails_test.cpp"
#endif