#include <sstream>
#include <boost/tokenizer.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "Conversion.hpp"
#include "Map.hpp"
#include "MapFactory.hpp"
#include "MapUtils.hpp"
#include "Serialize.hpp"
#include "TileFactory.hpp"

using namespace std;
using namespace boost;

Map::Map(const Map& new_map)
: terrain_type(TileType::TILE_TYPE_UNDEFINED), map_type(MapType::MAP_TYPE_OVERWORLD), permanent(false), danger(0), allow_creature_updates(true)
{
  if (this != &new_map)
  {
    Dimensions new_dimensions = new_map.size();
    TilesContainer new_tiles = new_map.get_tiles();

    dimensions = new_dimensions;
    original_dimensions = new_dimensions;
    tiles = new_tiles;

    map_id = new_map.map_id;
  }
}

Map::Map(const Dimensions& new_dimensions, const Dimensions& orig_dimensions)
: terrain_type(TileType::TILE_TYPE_UNDEFINED), map_type(MapType::MAP_TYPE_OVERWORLD), permanent(false), danger(0), allow_creature_updates(true)
{
  dimensions = new_dimensions;
  original_dimensions = orig_dimensions;
  
  // Generate a default unique identifier for this map
  boost::uuids::uuid id = boost::uuids::random_generator()();
  map_id = Uuid::to_string(id);
}

bool Map::operator==(const Map& map) const
{
  bool result = true;

  result = result && (tiles.size() == map.tiles.size());

  if (result)
  {
    // The search needs to be done this way because the TilesContainer is
    // a std::unordered_map, and therefore can't guarantee ordering of
    // keys.
    TilesContainer tiles_cont = map.tiles;
    TilesContainer::const_iterator t_it = tiles.begin();
    TilesContainer::const_iterator t_it2 = tiles_cont.begin();

    while (t_it != tiles.end())
    {
      string tile_key = t_it->first;
      TilesContainer::const_iterator t_it2 = tiles_cont.find(tile_key);
      result = result && (t_it2 != tiles_cont.end()) && (*(t_it->second) == *(t_it2->second));

      t_it++;
    }
  }

  result = result && (dimensions == map.dimensions);
  result = result && (original_dimensions == map.original_dimensions);
  result = result && (locations == map.locations);
  result = result && (terrain_type == map.terrain_type);
  result = result && (map_type == map.map_type);
  result = result && ((map_exit && map.map_exit) || (!map_exit && !map.map_exit));

  if (result && map_exit)
  {
    result = result && (*map_exit == *map.map_exit);
  }

  result = result && (map_id == map.map_id);
  result = result && (permanent == map.permanent);
  result = result && (danger == map.danger);
  result = result && (allow_creature_updates == map.allow_creature_updates);
  result = result && (properties == map.properties);
  result = result && (tile_transforms == map.tile_transforms);

  return result;
}

// Create the creature list by iterating over all the map tiles, and adding any Creature
// attached to a tile.
void Map::create_creatures()
{
  creatures.clear();

  TilesContainer::iterator map_it;

  for (map_it = tiles.begin(); map_it != tiles.end(); map_it++)
  {
    TilePtr current_tile = map_it->second;
    
    if (current_tile)
    {
      CreaturePtr potential_creature = current_tile->get_creature();

      if (potential_creature)
      {
        add_creature(potential_creature);
      }
    }
  }
}

bool Map::has_creature(const string& creature_id)
{
  if (creatures.empty())
  {
    create_creatures();
  }

  return (creatures.find(creature_id) != creatures.end());
}

void Map::add_creature(CreaturePtr creature)
{
  if (creature)
  {
    creatures.insert(make_pair(creature->get_id(), creature));
  }
}

CreaturePtr Map::get_creature(const string& creature_id)
{
  if (creatures.empty())
  {
    create_creatures();
  }

  CreaturePtr creature;
  
  map<string, CreaturePtr>::iterator c_it = creatures.find(creature_id);
  
  if (c_it != creatures.end())
  {
    creature = c_it->second;
  }
  
  return creature;
}

map<string, CreaturePtr> Map::get_creatures()
{
  if (creatures.empty())
  {
    create_creatures();
  }

  return creatures;
}

map<string, CreaturePtr>& Map::get_creatures_ref()
{
  if (creatures.empty())
  {
    create_creatures();
  }
  
  return creatures;
}

map<Direction, vector<Coordinate>>& Map::get_tile_exits_ref()
{
  return tile_exits;
}

map<Direction, vector<Coordinate>> Map::get_tile_exits() const
{
  return tile_exits;
}

// Resets the creatures and the list of locations.  For the list of
// locations, it only re-adds the creature-based ones.
void Map::reset_creatures_and_locations()
{
  creatures.clear();
  locations.clear();
  
  for (TilesContainer::iterator t_it = tiles.begin(); t_it != tiles.end(); t_it++)
  {
    string tile_key = t_it->first;
    TilePtr tile    = t_it->second;
    
    if (tile && tile->has_creature())
    {
      CreaturePtr creature = tile->get_creature();
      
      if (creature)
      {
        add_creature(creature);
      }

      locations.insert(make_pair(creature->get_id(), MapUtils::convert_map_key_to_coordinate(tile_key)));
    }    
  }
}

// Remove a creature both from the main list, as well as from the locations list.
void Map::remove_creature(const string& creature_id)
{
  auto c_it = creatures.find(creature_id);
  
  if (c_it != creatures.end())
  {
    creatures.erase(c_it);
  }

  auto l_it = locations.find(creature_id);

  if (l_it != locations.end())
  {
    locations.erase(l_it);
  }
}

void Map::set_tiles(const TilesContainer& new_tiles)
{
  tiles = new_tiles;
}

bool Map::insert(int row, int col, TilePtr tile)
{
  string key = MapUtils::convert_coordinate_to_map_key(row, col);
  CreaturePtr creature = tile->get_creature();

  // Ensure that the map's list of locations is updated with the
  // new creature, if one exists on the tile.
  if (creature != nullptr)
  {
    add_or_update_location(creature->get_id(), {row, col});
  }

  tiles[key] = tile;
  return true;
}

bool Map::insert(const Coordinate& c, TilePtr tile)
{
  return insert(c.first, c.second, tile);
}

TilePtr Map::at(int row, int col)
{
  string key = MapUtils::convert_coordinate_to_map_key(row, col);
  TilePtr tile;

  TilesContainer::iterator t_it = tiles.find(key);
  
  if (t_it != tiles.end())
  {
    tile = t_it->second;
  }
  
  return tile;
}

TilePtr Map::at(const Coordinate& c)
{
  return at(c.first, c.second);
}

void Map::set_size(const Dimensions& new_dimensions)
{
  dimensions = new_dimensions;
}

Dimensions Map::size() const
{
  return dimensions;
}

Dimensions& Map::size_ref()
{
  return dimensions;
}

void Map::set_original_size(const Dimensions& new_original_dimensions)
{
  original_dimensions = new_original_dimensions;
}

Dimensions Map::original_size() const
{
  return original_dimensions;
}

Dimensions& Map::original_size_ref()
{
  return original_dimensions;
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

TilesContainer Map::get_tiles() const
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

void Map::remove_location(const string& location)
{
  locations.erase(location);
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

// Set/get the danger level used to generate the monsters and items on the map.
void Map::set_danger(const int new_danger)
{
  danger = new_danger;
}

int Map::get_danger() const
{
  return danger;
}

void Map::set_allow_creature_updates(const bool new_allow_creature_updates)
{
  allow_creature_updates = new_allow_creature_updates;
}

bool Map::get_allow_creature_updates() const
{
  return ((map_type != MapType::MAP_TYPE_WORLD) && allow_creature_updates);
}

void Map::set_property(const string& prop, const string& value)
{
  properties[prop] = value;
}

bool Map::remove_property(const string& prop)
{
  bool removed = false;

  auto p_it = properties.find(prop);

  if (p_it != properties.end())
  {
    properties.erase(p_it);
    removed = true;
  }

  return removed;
}

void Map::set_properties(const map<string, string>& new_properties)
{
  properties = new_properties;
}

string Map::get_property(const string& prop) const
{
  string val;

  auto p_it = properties.find(prop);
  if (p_it != properties.end())
  {
    val = p_it->second;
  }

  return val;
}

map<string, string> Map::get_properties() const
{
  return properties;
}

void Map::set_tile_transforms(const TileTransformContainer& new_tile_transforms)
{
  tile_transforms = new_tile_transforms;
}

TileTransformContainer& Map::get_tile_transforms_ref()
{
  return tile_transforms;
}

TileTransformContainer Map::get_tile_transforms() const
{
  return tile_transforms;
}

bool Map::serialize(ostream& stream) const
{
  // creatures - not serialized.  build up after deserialization.

  size_t num_tile_exit_directions = tile_exits.size();
  Serialize::write_size_t(stream, num_tile_exit_directions);
  for (auto& dir_exit_pair : tile_exits)
  {
    Serialize::write_enum(stream, dir_exit_pair.first);

    // Write out the list of tiles with exits in that direction:
    vector<Coordinate> coords_for_dir = dir_exit_pair.second;
    Serialize::write_size_t(stream, coords_for_dir.size());

    for (const auto& coord : coords_for_dir)
    {
      Serialize::write_int(stream, coord.first);
      Serialize::write_int(stream, coord.second);
    }
  }

  // tiles
  Serialize::write_size_t(stream, tiles.size());

  for (const TilesContainer::value_type& map_pair : tiles)
  {
    Serialize::write_string(stream, map_pair.first);

    TilePtr tile = map_pair.second;
    Serialize::write_class_id(stream, tile->get_class_identifier());
    tile->serialize(stream);
  }

  dimensions.serialize(stream);
  original_dimensions.serialize(stream);

  Serialize::write_size_t(stream, locations.size());

  for (const NamedMapLocations::value_type& map_pair : locations)
  {
    Serialize::write_string(stream, map_pair.first);
    Serialize::write_int(stream, map_pair.second.first); // coords
    Serialize::write_int(stream, map_pair.second.second); // coords
  }

  Serialize::write_enum(stream, terrain_type);
  Serialize::write_enum(stream, map_type);

  // Map exit can be null (for overworld, maybe dungeon maps, etc.),
  // so guard against this case in both serialization and deserialization.
  if (map_exit)
  {
    Serialize::write_class_id(stream, map_exit->get_class_identifier());
    map_exit->serialize(stream);
  }
  else
  {
    Serialize::write_class_id(stream, ClassIdentifier::CLASS_ID_NULL);
  }

  Serialize::write_string(stream, map_id);
  Serialize::write_bool(stream, permanent);
  Serialize::write_int(stream, danger);
  Serialize::write_bool(stream, allow_creature_updates);
  Serialize::write_string_map(stream, properties);

  Serialize::write_size_t(stream, tile_transforms.size());
  for (const auto& t_pair : tile_transforms)
  {
    Serialize::write_int(stream, t_pair.first.first);
    Serialize::write_int(stream, t_pair.first.second);
    t_pair.second.serialize(stream);
  }

  return true;
}

bool Map::deserialize(istream& stream)
{
  // creatures - not deserialized - built up automatically

  // tile map exits map
  size_t num_tile_exit_directions = 0;
  Serialize::read_size_t(stream, num_tile_exit_directions);

  for (size_t i = 0; i < num_tile_exit_directions; i++)
  {
    Direction d = Direction::DIRECTION_NULL;
    Serialize::read_enum(stream, d);

    size_t vector_size = 0;
    Serialize::read_size_t(stream, vector_size);
    vector<Coordinate> coords_for_dir;

    for (size_t j = 0; j < vector_size; j++)
    {
      int row = 0, col = 0;
      Serialize::read_int(stream, row);
      Serialize::read_int(stream, col);

      coords_for_dir.push_back(make_pair(row, col));
    }

    tile_exits.insert(make_pair(d, coords_for_dir));
  }

  // tiles
  size_t num_tiles;
  Serialize::read_size_t(stream, num_tiles);

  tiles.clear();

  for (unsigned int i = 0; i < num_tiles; i++)
  {
    string map_key;
    Serialize::read_string(stream, map_key);

    ClassIdentifier tile_clid;
    Serialize::read_class_id(stream, tile_clid);

    if (tile_clid != ClassIdentifier::CLASS_ID_NULL)
    {
      TilePtr tile = TileFactory::create_tile(tile_clid);
      tile->deserialize(stream);
      tiles.insert(make_pair(map_key, tile));
    }
  }

  // creatures - build up after deserialization
  create_creatures();

  dimensions.deserialize(stream);
  original_dimensions.deserialize(stream);

  size_t map_size;
  Serialize::read_size_t(stream, map_size);

  locations.clear();

  for (unsigned int i = 0; i < map_size; i++)
  {
    string location_name;
    Coordinate coord;

    Serialize::read_string(stream, location_name);
    Serialize::read_int(stream, coord.first);
    Serialize::read_int(stream, coord.second);

    locations.insert(make_pair(location_name, coord));
  }

  Serialize::read_enum(stream, terrain_type);
  Serialize::read_enum(stream, map_type);

  // Consume and ignore class ID for now.  Then create the map exit, and deserialize.
  ClassIdentifier map_exit_clid;
  Serialize::read_class_id(stream, map_exit_clid);

  // If the map exit wasn't null originally (e.g., map exit on overworld map),
  // then read the details.
  if (map_exit_clid != ClassIdentifier::CLASS_ID_NULL)
  {
    map_exit = MapFactory::create_map_exit();
    map_exit->deserialize(stream);
  }

  Serialize::read_string(stream, map_id);
  Serialize::read_bool(stream, permanent);
  Serialize::read_int(stream, danger);
  Serialize::read_bool(stream, allow_creature_updates);

  properties.clear();
  Serialize::read_string_map(stream, properties);

  tile_transforms.clear();
  size_t trans_size = 0;
  Serialize::read_size_t(stream, trans_size);

  for (size_t i = 0; i < trans_size; i++)
  {
    Coordinate c;

    Serialize::read_int(stream, c.first);
    Serialize::read_int(stream, c.second);

    TileTransform tt;
    tt.deserialize(stream);

    tile_transforms.insert(make_pair(c, tt));
  }

  return true;
}

ClassIdentifier Map::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_MAP;
}

#ifdef UNIT_TESTS
#include "unit_tests/WorldMap_test.cpp"
#endif
