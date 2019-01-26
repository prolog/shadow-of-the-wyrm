#include "MapExit.hpp"
#include "CoordUtils.hpp"
#include "Serialize.hpp"

using namespace std;

MapExit::MapExit()
: terrain_type(TileType::TILE_TYPE_UNDEFINED)
, coord(-1, -1)
{
}

MapExit::~MapExit()
{
}

bool MapExit::operator==(const MapExit& me) const
{
  bool result = true;

  result = result && (map_id == me.map_id);
  result = result && (terrain_type == me.terrain_type);
  result = result && (coord == me.coord);
  result = result && (properties == me.properties);
  result = result && (event_scripts == me.event_scripts);

  return result;
}

void MapExit::set_map_id(const string& new_map_id)
{
  map_id = new_map_id;
}

string MapExit::get_map_id() const
{
  return map_id;
}

void MapExit::set_terrain_type(const TileType new_terrain_type)
{
  terrain_type = new_terrain_type;
}

TileType MapExit::get_terrain_type() const
{
  return terrain_type;
}

void MapExit::set_coordinate(const Coordinate& c)
{
  coord = c;
}

Coordinate MapExit::get_coordinate() const
{
  return coord;
}

bool MapExit::has_coordinate() const
{
  return (CoordUtils::is_end(coord) == false);
}

bool MapExit::is_using_map_id() const
{
  return (!map_id.empty());
}

bool MapExit::is_using_terrain_type() const
{
  return (!is_using_map_id() && terrain_type != TileType::TILE_TYPE_UNDEFINED);
}

void MapExit::set_property(const string& prop, const string& val)
{
  properties[prop] = val;
}

string MapExit::get_property(const string& prop) const
{
  string val;

  auto p_it = properties.find(prop);
  if (p_it != properties.end())
  {
    val = p_it->second;
  }

  return val;
}

bool MapExit::has_property(const string& prop) const
{
  auto p_it = properties.find(prop);
  return (p_it != properties.end());
}

map<string, string> MapExit::get_properties() const
{
  return properties;
}

void MapExit::clear_event_scripts()
{
  event_scripts.clear();
}

void MapExit::set_event_scripts(const EventScriptsMap& esm)
{
  event_scripts = esm;
}

EventScriptsMap MapExit::get_event_scripts() const
{
  return event_scripts;
}

EventScriptsMap& MapExit::get_event_scripts_ref()
{
  return event_scripts;
}

void MapExit::add_event_script(const string& event_name, const ScriptDetails& sd)
{
  event_scripts[event_name] = sd;
}

bool MapExit::has_event_script(const string& event_name)
{
  bool has_event = false;

  EventScriptsMap::iterator e_it = event_scripts.find(event_name);

  if (e_it != event_scripts.end())
  {
    has_event = true;
  }

  return has_event;
}

ScriptDetails MapExit::get_event_script(const string& event_name) const
{
  ScriptDetails sd;

  EventScriptsMap::const_iterator e_it = event_scripts.find(event_name);

  if (e_it != event_scripts.end())
  {
    sd = e_it->second;
  }

  return sd;
}

bool MapExit::serialize(ostream& stream) const
{
  Serialize::write_string(stream, map_id);
  Serialize::write_enum(stream, terrain_type);
  Serialize::write_int(stream, coord.first);
  Serialize::write_int(stream, coord.second);
  Serialize::write_string_map(stream, properties);
  Serialize::write_event_scripts(stream, event_scripts);

  return true;
}

bool MapExit::deserialize(istream& stream)
{
  Serialize::read_string(stream, map_id);
  Serialize::read_enum(stream, terrain_type);
  Serialize::read_int(stream, coord.first);
  Serialize::read_int(stream, coord.second);
  Serialize::read_string_map(stream, properties);
  Serialize::read_event_scripts(stream, event_scripts);

  return true;
}

ClassIdentifier MapExit::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_MAP_EXIT;
}

#ifdef UNIT_TESTS
#include "unit_tests/MapExit_test.cpp"
#endif

