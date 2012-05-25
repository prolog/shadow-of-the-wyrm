#include <sstream>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include "Conversion.hpp"
#include "Map.hpp"

using namespace std;
using namespace boost;

Map::Map(const Map& new_map)
: terrain_type(TILE_TYPE_UNDEFINED), map_type(MAP_TYPE_OVERWORLD), permanent(false)
{
  if (this != &new_map)
  {
    Dimensions new_dimensions = new_map.size();
    std::map<std::string, TilePtr > new_tiles = new_map.get_tiles();

    dimensions = new_dimensions;
    tiles = new_tiles;
  }
}

Map::Map(const Dimensions& new_dimensions)
: terrain_type(TILE_TYPE_UNDEFINED), map_type(MAP_TYPE_OVERWORLD), permanent(false)
{
  dimensions = new_dimensions;
}

// Create the creature list by iterating over all the map tiles, and adding any Creature
// attached to a tile.
void Map::create_creatures()
{
  creatures.clear();

  std::map<string, TilePtr >::iterator map_it;

  for (map_it = tiles.begin(); map_it != tiles.end(); map_it++)
  {
    TilePtr current_tile = map_it->second;
    
    if (current_tile)
    {
      CreaturePtr potential_creature = current_tile->get_creature();

      if (potential_creature)
      {
        creatures.push_back(potential_creature);
      }
    }
  }
}

bool Map::has_creature(const string& creature_id)
{
  BOOST_FOREACH(CreaturePtr creature, creatures)
  {
    if (creature_id == creature->get_id())
    {
      return true;
    }
  }
  
  return false;
}

CreaturePtr Map::get_creature(const uint idx)
{
  CreaturePtr creature;

  if (idx < creatures.size())
  {
    return creatures.at(idx);
  }

  return creature;
}

vector<CreaturePtr> Map::get_creatures()
{
  if (creatures.empty())
  {
    create_creatures();
  }

  return creatures;
}

// Resets the creatures and the list of locations.  For the list of
// locations, it only re-adds the creature-based ones.
void Map::reset_creatures_and_locations()
{
  creatures.clear();
  locations.clear();
  
  for (map<string, TilePtr >::iterator t_it = tiles.begin(); t_it != tiles.end(); t_it++)
  {
    string tile_key = t_it->first;
    TilePtr tile    = t_it->second;
    
    if (tile && tile->has_creature())
    {
      CreaturePtr creature = tile->get_creature();
      creatures.push_back(creature);
      locations.insert(make_pair(creature->get_id(), convert_map_key_to_coordinate(tile_key)));
    }    
  }
}

void Map::remove_creature(const string& creature_id)
{
  for (vector<CreaturePtr>::iterator c_it = creatures.begin(); c_it != creatures.end(); c_it++)
  {
    CreaturePtr creature = *c_it;
    if (creature->get_id() == creature_id)
    {
      creatures.erase(c_it);
      return;
    }
  }
}

bool Map::insert(int row, int col, TilePtr tile)
{
  string key = make_key(row, col);

  tiles[key] = tile;
  return true;
}

string Map::make_key(const int row, const int col)
{
  std::ostringstream ss;
  ss << row << "-" << col;
  return ss.str();
}

TilePtr Map::at(int row, int col)
{
  string key = make_key(row, col);
  return tiles[key];
}

TilePtr Map::at(const Coordinate& c)
{
  string key = make_key(c.first, c.second);
  return tiles[key];
}

void Map::set_size(const Dimensions& new_dimensions)
{
  dimensions = new_dimensions;
}

Dimensions Map::size() const
{
  return dimensions;
}

void Map::set_terrain_type(const TileType new_terrain_type)
{
  terrain_type = new_terrain_type;
}

TileType Map::get_terrain_type() const
{
  return terrain_type;
}

void Map::set_map_type(const MapType& new_map_type)
{
  map_type = new_map_type;
}

MapType Map::get_map_type() const
{
  return map_type;
}

std::map<std::string, TilePtr > Map::get_tiles() const
{
  return tiles;
}

void Map::clear_locations()
{
  locations.clear();
}

void Map::add_or_update_location(const string& location, const Coordinate& coordinate)
{
  locations[location] = coordinate;
}

Coordinate Map::get_location(const string& location) const
{
  Coordinate c;

  c.first = 0;
  c.second = 0;

  NamedMapLocations::const_iterator l_it = locations.find(location);

  if (l_it != locations.end())
  {
    c = l_it->second;
  }

  return c;
}

bool Map::has_location(const string& location)
{
  NamedMapLocations::iterator n_it = locations.find(location);

  if (n_it != locations.end()) return true;
  else return false;  
}

TilePtr Map::get_tile_at_location(const string& location)
{
  TilePtr tile;

  NamedMapLocations::iterator n_it = locations.find(location);

  if (n_it != locations.end())
  {
    Coordinate coord = n_it->second;
    int row = coord.first;
    int col = coord.second;

    tile = at(row, col);
  }

  return tile;
}

// Set/get the map exit.  If this ptr is null, then the map doesn't have an exit from its
// boundary tiles.
void Map::set_map_exit(MapExitPtr new_map_exit)
{
  map_exit = new_map_exit;
}

MapExitPtr Map::get_map_exit() const
{
  return map_exit;
}

// Set/get the map's identifier, which is also used as its key in the map registry
void Map::set_map_id(const string& new_map_id)
{
  map_id = new_map_id;
}

string Map::get_map_id() const
{
  return map_id;
}

string Map::get_map_exit_id() const
{
  string map_exit_id;
  
  if (map_exit)
  {
    map_exit_id = map_exit->get_map_id();
  }
  
  return map_exit_id;
}

// Set/get whether or not the map should be permanent (is it a random terrain map?)
void Map::set_permanent(const bool permanence)
{
  permanent = permanence;
}

bool Map::get_permanent() const
{
  return permanent;
}

Coordinate Map::convert_map_key_to_coordinate(const string& map_key)
{
  Coordinate coords(0,0);
  
  char_separator<char> sep("-");
  tokenizer<char_separator<char> > tokens(map_key, sep);

  tokenizer<char_separator<char> >:: iterator t_it = tokens.begin();
  
  if (t_it != tokens.end())
  {
    coords.first = String::to_int(*t_it);
    t_it++;
  }
    
  if (t_it != tokens.end())
  {
    coords.second = String::to_int(*t_it);
  }

  return coords;
}

// There should be an IFDEF_UNIT_TESTS here, but the compiler isn't finding Map_test.cpp.
// However, it's able to do do so once I add that include to MapUtils.  So, the include
// statement is there.
