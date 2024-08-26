#include <sstream>
#include <boost/tokenizer.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "Conversion.hpp"
#include "Map.hpp"
#include "MapFactory.hpp"
#include "MapProperties.hpp"
#include "MapUtils.hpp"
#include "NullInventory.hpp"
#include "Serialize.hpp"
#include "TileFactory.hpp"

using namespace std;

// JCD FIXME: Right now, this copies a pretty minimal subset of stuff.
// This will likely need to be updated to include new fields at some
// point.
Map::Map(const Map& new_map)
: terrain_type(TileType::TILE_TYPE_UNDEFINED), map_type(MapType::MAP_TYPE_OVERWORLD), permanent(new_map.permanent), danger(0), allow_creature_creation(true), allow_creature_updates(true), weather(new_map.weather)
{
  if (this != &new_map)
  {
    name_sid = new_map.name_sid;
    default_race_id = new_map.default_race_id;
    default_deity_id = new_map.default_deity_id;
    map_id = new_map.map_id;

    dimensions = new_map.size();
    original_dimensions = dimensions;
    tiles = new_map.get_tiles();

    map_id = new_map.map_id;
  }
}

Map::Map(const Dimensions& new_dimensions, const Dimensions& orig_dimensions)
: terrain_type(TileType::TILE_TYPE_UNDEFINED), map_type(MapType::MAP_TYPE_OVERWORLD), permanent(false), danger(0), allow_creature_creation(true), allow_creature_updates(true), weather("")
{
  dimensions = new_dimensions;
  original_dimensions = orig_dimensions;
  
  tiles.reserve(dimensions.get_y() * dimensions.get_x());

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

    while (t_it != tiles.end())
    {
      string tile_key = t_it->first;
      TilesContainer::const_iterator t_it2 = tiles_cont.find(tile_key);
      result = result && (t_it2 != tiles_cont.end()) && (*(t_it->second) == *(t_it2->second));

      t_it++;
    }
  }

  result = result && (name_sid == map.name_sid);
  result = result && (default_race_id == map.default_race_id);
  result = result && (default_deity_id == map.default_deity_id);
  result = result && (dimensions == map.dimensions);
  result = result && (original_dimensions == map.original_dimensions);
  result = result && (locations == map.locations);
  result = result && (terrain_type == map.terrain_type);
  result = result && (map_type == map.map_type);
  result = result && (map_exits.size() == map.map_exits.size());

  for (auto& m_it : map_exits)
  {
    auto m_it2 = map.map_exits.find(m_it.first);

    result = result && (m_it2 != map.map_exits.end() && m_it.second && m_it2->second && (*m_it.second == *m_it2->second));
  }

  result = result && (map_id == map.map_id);
  result = result && (permanent == map.permanent);
  result = result && (danger == map.danger);
  result = result && (allow_creature_creation == map.allow_creature_creation);
  result = result && (allow_creature_updates == map.allow_creature_updates);
  result = result && (properties == map.properties);
  result = result && (tile_transforms == map.tile_transforms);
  result = result && (tile_item_transforms == map.tile_item_transforms);
  result = result && (preset_locations == map.preset_locations);
  result = result && (shops == map.shops);
  result = result && (event_scripts == map.event_scripts);
  result = result && (weather == map.weather);

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

bool Map::has_player()
{
  if (creatures.empty())
  {
    create_creatures();
  }

  return has_creature(CreatureID::CREATURE_ID_PLAYER);
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

// Resets the creatures and the list of creature locations.
// Leave general locations alone.
void Map::reset_creatures_and_creature_locations()
{
  creatures.clear();

  // explicitly not resetting all locations here, as we don't want to wipe
  // out any non-creature locations.

  for (TilesContainer::iterator t_it = tiles.begin(); t_it != tiles.end(); t_it++)
  {
    string tile_key = t_it->first;
    TilePtr tile = t_it->second;

    if (tile && tile->has_creature())
    {
      CreaturePtr creature = tile->get_creature();

      if (creature)
      {
        add_creature(creature);
        locations[creature->get_id()] = MapUtils::convert_map_key_to_coordinate(tile_key);
      }
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

  // Remove the dead creature from all creatures' threat ratings.
  for (auto c_pair : creatures)
  {
    CreaturePtr c = c_pair.second;
    if (c != nullptr)
    {
      DecisionStrategy* dec = c->get_decision_strategy();
      if (dec != nullptr)
      {
        ThreatRatings& threat_ratings = dec->get_threats_ref();
        pair<bool, int> threat_exists = threat_ratings.has_threat(creature_id);
        if (threat_exists.first)
        {
          threat_ratings.remove_threat(creature_id, threat_exists.second);
        }
      }
    }
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

  if (map_type == MapType::MAP_TYPE_UNDERWATER)
  {
    for (auto& tile_pair : tiles)
    {
      TilePtr tile = tile_pair.second;

      if (tile != nullptr)
      {
        tile->set_submerged(true);
      }
    }
  }
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

  // If this is the world map, ensure that the inventory is a
  // NullInventory
  if (map_type == MapType::MAP_TYPE_WORLD)
  {
    IInventoryPtr null_inv = std::make_shared<NullInventory>();
    tile->set_items(null_inv);
  }
  // If this is an underwater map, turn on the submerged flag.
  else if (map_type == MapType::MAP_TYPE_UNDERWATER)
  {
    tile->set_submerged(true);
  }
  
  tiles[key] = tile;
  return true;
}

bool Map::insert(const Coordinate& c, TilePtr tile)
{
  return insert(c.first, c.second, tile);
}

TilePtr Map::at(int row, int col) const
{
  string key = MapUtils::convert_coordinate_to_map_key(row, col);
  TilePtr tile;

  TilesContainer::const_iterator t_it = tiles.find(key);
  
  if (t_it != tiles.end())
  {
    tile = t_it->second;
  }
  
  return tile;
}

TilePtr Map::at(const Coordinate& c) const
{
  return at(c.first, c.second);
}

void Map::set_name_sid(const string& new_name_sid)
{
  name_sid = new_name_sid;
}

string Map::get_name_sid() const
{
  return name_sid;
}

void Map::set_default_race_id(const string& new_race_id)
{
  default_race_id = new_race_id;
}

string Map::get_default_race_id() const
{
  return default_race_id;
}

void Map::set_default_deity_id(const string& new_deity_id)
{
  default_deity_id = new_deity_id;
}

string Map::get_default_deity_id() const
{
  return default_deity_id;
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

TilesContainer& Map::get_tiles_ref()
{
  return tiles;
}

void Map::clear_locations()
{
  locations.clear();
}

void Map::set_is_water_shallow(const bool new_shallow)
{
  properties[MapProperties::MAP_PROPERTIES_SHALLOW_WATER] = std::to_string(new_shallow);
}

bool Map::get_is_water_shallow() const
{
  auto p_it = properties.find(MapProperties::MAP_PROPERTIES_SHALLOW_WATER);

  if (p_it != properties.end())
  {
    return String::to_bool(p_it->second);
  }

  return true;
}

void Map::set_is_open_sky(const bool new_open_sky)
{
  properties[MapProperties::MAP_PROPERTIES_OPEN_SKY] = std::to_string(new_open_sky);
}

bool Map::get_is_open_sky() const
{
  auto p_it = properties.find(MapProperties::MAP_PROPERTIES_OPEN_SKY);

  if (p_it != properties.end())
  {
    return String::to_bool(p_it->second);
  }

  return false;
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
  Coordinate c(0,0);

  NamedMapLocations::const_iterator l_it = locations.find(location);

  if (l_it != locations.end())
  {
    c = l_it->second;
  }

  return c;
}

pair<Coordinate, TilePtr> Map::get_location_and_tile(const std::string& creature_id) const
{
  pair<Coordinate, TilePtr> result_pair({0,0}, nullptr);

  result_pair.first = get_location(creature_id);
  result_pair.second = at(result_pair.first);

  return result_pair;
}

map<string, pair<Coordinate, CreaturePtr>> Map::get_locations_with_creatures() const
{
  map<string, pair<Coordinate, CreaturePtr>> clocs;
  
  for (const auto& loc : locations)
  {
    map<string, CreaturePtr>::const_iterator c_it = creatures.find(loc.first);

    if (c_it != creatures.end())
    {
      clocs[loc.first] = make_pair(loc.second, c_it->second);
    }
  }

  return clocs;
}

map<string, Coordinate> Map::get_locations() const
{
  return locations;
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
  map_exits[Direction::DIRECTION_NULL] = new_map_exit;
}

void Map::set_map_exit(const Direction d, MapExitPtr new_map_exit)
{
  map_exits[d] = new_map_exit;
}

void Map::set_map_exits(const std::map<Direction, MapExitPtr>& new_map_exits)
{
  map_exits = new_map_exits;
}

map<Direction, MapExitPtr> Map::get_map_exits() const
{
  return map_exits;
}

MapExitPtr Map::get_map_exit(const Direction d) const
{
  MapExitPtr map_exit;
  auto m_it = map_exits.find(d);

  if (m_it != map_exits.end())
  {
    map_exit = m_it->second;
  }

  return map_exit;
}

MapExitPtr Map::get_map_exit() const
{
  return get_map_exit(Direction::DIRECTION_NULL);
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

// A map with one exit (e.g., back to the overworld) is not a multi-map.
// A multi-map has exits to map IDs in more than one direction - ie, not
// just back to the overworld.
bool Map::get_is_multi_map() const
{
  bool mm = false;
  size_t m_size = map_exits.size();
  auto m_it = map_exits.find(Direction::DIRECTION_NULL);

  if (m_size > 1)
  {
    // More directional exits than just the default?  Multi-map.
    mm = true;
  }
  else if (m_size == 1)
  {
    // There is an exit, and it's not just the default.
    mm = (m_it == map_exits.end());
  }

  return mm;
}

string Map::get_map_exit_id() const
{
  return get_map_exit_id(Direction::DIRECTION_NULL);
}

string Map::get_map_exit_id(const Direction d) const
{
  string map_exit_id;
  
  if (!map_exits.empty())
  {
    auto m_it = map_exits.find(d);

    if (m_it != map_exits.end())
    {
      MapExitPtr map_exit = m_it->second;

      if (map_exit != nullptr)
      {
        map_exit_id = map_exit->get_map_id();
      }
    }
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
  string dlvl_override = get_property(MapProperties::MAP_PROPERTIES_DANGER_LEVEL_OVERRIDE);

  if (dlvl_override.empty())
  {
    danger = new_danger;
  }
}

int Map::get_danger() const
{
  string dlvl_override = get_property(MapProperties::MAP_PROPERTIES_DANGER_LEVEL_OVERRIDE);

  if (dlvl_override.empty())
  {
    // If danger's been set, return that. If it hasnt, estimate based on the
    // current depth.
    if (danger > 0)
    {
      return danger;
    }
    else
    {
      // JCD FIXME this is probably going to break tons of shit
      return std::abs(dimensions.depth().get_current());
    }
  }
  else
  {
    return String::to_int(dlvl_override);
  }
}

void Map::set_allow_creature_creation(const bool new_allow_creature_creation)
{
  allow_creature_creation = new_allow_creature_creation;
}

bool Map::get_allow_creature_creation() const
{
  return allow_creature_creation;
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

bool Map::has_property(const string& prop) const
{
  auto p_it = properties.find(prop);
  return p_it != properties.end();
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

size_t Map::count_tile_transforms_with_property(const Coordinate& c, const string& prop_name) const
{
  size_t tr = 0;

  for (const auto& t_pair : tile_transforms)
  {
    const auto& t_vec = t_pair.second;

    for (const auto& it_tr : t_vec)
    {
      if (it_tr.get_coordinate() == c)
      {
        map<string, string> props = it_tr.get_properties_cref();

        if (props.find(prop_name) != props.end())
        {
          tr++;
        }
      }
    }
  }

  return tr;
}

void Map::set_tile_item_transforms(const TileItemTransformContainer& new_tile_item_transforms)
{
  tile_item_transforms = new_tile_item_transforms;
}

TileItemTransformContainer& Map::get_tile_item_transforms_ref()
{
  return tile_item_transforms;
}

TileItemTransformContainer Map::get_tile_item_transforms() const
{
  return tile_item_transforms;
}

size_t Map::count_tile_item_transforms(const Coordinate& c) const
{
  size_t tr = 0;

  for (const auto& t_pair : tile_item_transforms)
  {
    const auto& t_vec = t_pair.second;

    for (const auto& it_tr : t_vec)
    {
      if (it_tr.get_coordinate() == c)
      {
        tr++;
      }
    }
  }

  return tr;
}

void Map::set_preset_locations(const vector<Coordinate>& new_preset_locations)
{
  preset_locations = new_preset_locations;
}

vector<Coordinate> Map::get_preset_locations() const
{
  return preset_locations;
}

vector<Coordinate>& Map::get_preset_locations_ref()
{
  return preset_locations;
}

pair<Coordinate, Coordinate> Map::get_generation_coordinates() const
{
  Dimensions d = size();
  pair<Coordinate, Coordinate> g_coords = std::make_pair(make_pair(0,0), make_pair(d.get_y()-1, d.get_x()-1));
  string range = get_property(MapProperties::MAP_PROPERTIES_GENERATION_COORDINATES);

  if (!range.empty())
  {
    vector<int> coord_v = String::create_int_vector_from_csv_string(range);

    if (coord_v.size() == 4)
    {
      g_coords = {{coord_v[0], coord_v[1]}, {coord_v[2], coord_v[3]}};
    }
  }

  return g_coords;
}

void Map::set_shops(const map<string, Shop>& new_shops)
{
  shops = new_shops;
}

map<string, Shop>& Map::get_shops_ref()
{
  return shops;
}

map<string, Shop> Map::get_shops() const
{
  return shops;
}

bool Map::has_shop(const string& shop_id) const
{
  return shops.find(shop_id) != shops.end();
}

void Map::clear_event_scripts()
{
  event_scripts.clear();
}

void Map::set_event_scripts(const EventScriptsMap& esm)
{
  event_scripts = esm;
}

EventScriptsMap Map::get_event_scripts() const
{
  return event_scripts;
}

EventScriptsMap& Map::get_event_scripts_ref()
{
  return event_scripts;
}

void Map::add_event_script(const string& event_name, const ScriptDetails& sd)
{
  event_scripts[event_name] = sd;
}

bool Map::has_event_script(const string& event_name)
{
  bool has_event = false;

  EventScriptsMap::iterator e_it = event_scripts.find(event_name);

  if (e_it != event_scripts.end())
  {
    has_event = true;
  }

  return has_event;
}

ScriptDetails Map::get_event_script(const string& event_name) const
{
  ScriptDetails sd;

  EventScriptsMap::const_iterator e_it = event_scripts.find(event_name);

  if (e_it != event_scripts.end())
  {
    sd = e_it->second;
  }

  return sd;
}

void Map::set_weather(const Weather& new_weather)
{
  weather = new_weather;
}

Weather Map::get_weather() const
{
  return weather;
}

Weather& Map::get_weather_ref()
{
  return weather;
}

Coordinate Map::get_starting_location() const
{
  Coordinate base = { 0, 0 };
  Coordinate c = base;
  int dy = 0;
  int dx = 0;

  bool n = String::to_bool(get_property(MapProperties::MAP_PROPERTIES_COASTLINE_NORTH));
  bool s = String::to_bool(get_property(MapProperties::MAP_PROPERTIES_COASTLINE_SOUTH));
  bool e = String::to_bool(get_property(MapProperties::MAP_PROPERTIES_COASTLINE_EAST));
  bool w = String::to_bool(get_property(MapProperties::MAP_PROPERTIES_COASTLINE_WEST));

  // If all are true (island) or none are true (inland), use 0,0.
  // Otherwise, use a value bsaed on the dimensions and the first available
  // non-coast of N, S, E, W
  if (!((n && s && e && w) || (!n && !s && !e && !w)))
  {
    Dimensions d = size();
    if (!n)
    {
      c = { 0, (d.get_x() - 1) / 2 };
      dy++;
    }
    else if (!s)
    {
      c = { d.get_y() - 1, (d.get_x() - 1) / 2 };
      dy--;
    }
    else if (!e)
    {
      c = { (d.get_y() - 1) / 2, d.get_x() - 1 };
      dx--;
    }
    else if (!w)
    {
      c = { (d.get_y() - 1) / 2, 0 };
      dx++;
    }
  }

  if (dy == 0 && dx == 0)
  {
    dy++;
    dx++;
  }

  while (dimensions.contains(c))
  {
    TilePtr tile = at(c);

    if (tile != nullptr)
    {
      if (!tile->get_is_blocking_or_dangerous(nullptr))
      {
        break;
      }
    } 

    c.first += dy;
    c.second += dx;
  }

  return c;
}

void Map::set_secondary_terrain(const vector<TileType>& new_secondary_terrain)
{
  ostringstream ss;

  for (size_t i = 0; i < new_secondary_terrain.size(); i++)
  {
    ss << static_cast<int>(new_secondary_terrain[i]);

    if (i < new_secondary_terrain.size() - 1)
    {
      ss << ",";
    }
  }

  set_property(MapProperties::MAP_PROPERTIES_SECONDARY_TERRAIN, ss.str());
}

void Map::add_secondary_terrain(const TileType tt)
{
  vector<TileType> sec_ter = get_secondary_terrain();

  if (std::find(sec_ter.begin(), sec_ter.end(), tt) == sec_ter.end())
  {
    sec_ter.push_back(tt);
    set_secondary_terrain(sec_ter);
  }
}

vector<TileType> Map::get_secondary_terrain() const
{
  vector<TileType> sec_ter;

  string sec_ter_s = get_property(MapProperties::MAP_PROPERTIES_SECONDARY_TERRAIN);
  if (!sec_ter_s.empty())
  {
    vector<string> sec_ter_v = String::create_string_vector_from_csv_string(sec_ter_s);

    for (const auto& s : sec_ter_v)
    {
      sec_ter.push_back(static_cast<TileType>(String::to_int(s)));
    }
  }

  return sec_ter;
}

vector<Direction> Map::get_coastline_directions() const
{
  vector<Direction> dirs;

  bool n = String::to_bool(get_property(MapProperties::MAP_PROPERTIES_COASTLINE_NORTH));
  bool s = String::to_bool(get_property(MapProperties::MAP_PROPERTIES_COASTLINE_SOUTH));
  bool e = String::to_bool(get_property(MapProperties::MAP_PROPERTIES_COASTLINE_EAST));
  bool w = String::to_bool(get_property(MapProperties::MAP_PROPERTIES_COASTLINE_WEST));

  if (n)
  {
    dirs.push_back(Direction::DIRECTION_NORTH);
  }

  if (s)
  {
    dirs.push_back(Direction::DIRECTION_SOUTH);
  }

  if (e)
  {
    dirs.push_back(Direction::DIRECTION_EAST);
  }

  if (w)
  {
    dirs.push_back(Direction::DIRECTION_WEST);
  }

  return dirs;
}

bool Map::is_islet() const
{
  return (map_type == MapType::MAP_TYPE_OVERWORLD && get_coastline_directions().size() == 4);
}

void Map::set_world_id(const string& new_world_id)
{
  properties[MapProperties::MAP_PROPERTIES_WORLD_ID] = new_world_id;
}

string Map::get_world_id() const
{
  string id;
  auto world_it = properties.find(MapProperties::MAP_PROPERTIES_WORLD_ID);

  if (world_it != properties.end())
  {
    id = world_it->second;
  }

  return id;
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

  Serialize::write_string(stream, name_sid);
  Serialize::write_string(stream, default_race_id);
  Serialize::write_string(stream, default_deity_id);

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
  Serialize::write_size_t(stream, map_exits.size());
  for (auto m_it : map_exits)
  {
    Serialize::write_enum(stream, m_it.first);
    MapExitPtr map_exit = m_it.second;

    if (map_exit)
    {
      Serialize::write_class_id(stream, map_exit->get_class_identifier());
      map_exit->serialize(stream);
    }
    else
    {
      Serialize::write_class_id(stream, ClassIdentifier::CLASS_ID_NULL);
    }
  }

  Serialize::write_string(stream, map_id);
  Serialize::write_bool(stream, permanent);
  Serialize::write_int(stream, danger);
  Serialize::write_bool(stream, allow_creature_creation);
  Serialize::write_bool(stream, allow_creature_updates);
  Serialize::write_string_map(stream, properties);

  Serialize::write_size_t(stream, tile_transforms.size());
  for (const auto& t_pair : tile_transforms)
  {
    Serialize::write_double(stream, t_pair.first);

    vector<TileTransform> t_trans = t_pair.second;
    Serialize::write_size_t(stream, t_trans.size());

    for (const TileTransform& tt : t_trans)
    {
      tt.serialize(stream);
    }
  }

  Serialize::write_size_t(stream, tile_item_transforms.size());
  for (const auto& t_pair : tile_item_transforms)
  {
    Serialize::write_double(stream, t_pair.first);

    vector<TileItemTransform> t_trans = t_pair.second;
    Serialize::write_size_t(stream, t_trans.size());

    for (const TileItemTransform& tit : t_trans)
    {
      tit.serialize(stream);
    }
  }

  Serialize::write_size_t(stream, preset_locations.size());
  for (const auto& c : preset_locations)
  {
    Serialize::write_int(stream, c.first);
    Serialize::write_int(stream, c.second);
  }

  Serialize::write_size_t(stream, shops.size());
  for (const auto& shop_pair : shops)
  {
    Serialize::write_string(stream, shop_pair.first);
    shop_pair.second.serialize(stream);
  }

  Serialize::write_event_scripts(stream, event_scripts);

  weather.serialize(stream);

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

  Serialize::read_string(stream, name_sid);
  Serialize::read_string(stream, default_race_id);
  Serialize::read_string(stream, default_deity_id);

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
  size_t num_exits = 0;
  Serialize::read_size_t(stream, num_exits);

  for (size_t i = 0; i < num_exits; i++)
  {
    Direction d = Direction::DIRECTION_NULL;
    Serialize::read_enum(stream, d);

    // Read and ignore the class ID
    ClassIdentifier map_exit_clid;
    Serialize::read_class_id(stream, map_exit_clid);

    // If the map exit wasn't null originally (e.g., map exit on overworld map),
    // then read the details.
    if (map_exit_clid != ClassIdentifier::CLASS_ID_NULL)
    {
      MapExitPtr map_exit = MapFactory::create_map_exit();
      map_exit->deserialize(stream);
      map_exits[d] = map_exit;
    }
  }

  Serialize::read_string(stream, map_id);
  Serialize::read_bool(stream, permanent);
  Serialize::read_int(stream, danger);
  Serialize::read_bool(stream, allow_creature_creation);
  Serialize::read_bool(stream, allow_creature_updates);

  properties.clear();
  Serialize::read_string_map(stream, properties);

  tile_transforms.clear();
  size_t trans_size = 0;
  Serialize::read_size_t(stream, trans_size);

  for (size_t i = 0; i < trans_size; i++)
  {
    double seconds = 0.0;
    Serialize::read_double(stream, seconds);

    size_t v_size = 0;
    Serialize::read_size_t(stream, v_size);
    vector<TileTransform> t_trans;

    for (size_t j = 0; j < v_size; j++)
    {
      TileTransform tt;
      tt.deserialize(stream);

      t_trans.push_back(tt);
    }

    tile_transforms.insert(make_pair(seconds, t_trans));
  }

  tile_item_transforms.clear();
  size_t it_trans_size = 0;
  Serialize::read_size_t(stream, it_trans_size);

  for (size_t i = 0; i < it_trans_size; i++)
  {
    double seconds = 0.0;
    Serialize::read_double(stream, seconds);

    size_t v_size = 0;
    Serialize::read_size_t(stream, v_size);
    vector<TileItemTransform> ti_trans;

    for (size_t j = 0; j < v_size; j++)
    {
      TileItemTransform tit;
      tit.deserialize(stream);

      ti_trans.push_back(tit);
    }

    tile_item_transforms.insert(make_pair(seconds, ti_trans));
  }

  preset_locations.clear();
  size_t preset_loc_size = 0;
  Serialize::read_size_t(stream, preset_loc_size);

  for (size_t i = 0; i < preset_loc_size; i++)
  {
    int y, x;

    Serialize::read_int(stream, y);
    Serialize::read_int(stream, x);

    preset_locations.push_back(make_pair(y, x));
  }

  size_t shops_sz = 0;
  Serialize::read_size_t(stream, shops_sz);
  shops.clear();

  for (size_t sz = 0; sz < shops_sz; sz++)
  {
    Shop shop;

    string shop_id;

    Serialize::read_string(stream, shop_id);
    shop.deserialize(stream);

    shops[shop_id] = shop;
  }

  Serialize::read_event_scripts(stream, event_scripts);
  
  weather.deserialize(stream);

  return true;
}

ClassIdentifier Map::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_MAP;
}

#ifdef UNIT_TESTS
#include "unit_tests/WorldMap_test.cpp"
#endif
