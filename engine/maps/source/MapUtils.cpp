#include "Conversion.hpp"
#include "CoordUtils.hpp"
#include "CreatureFactory.hpp"
#include "Game.hpp"
#include "MapUtils.hpp"
#include "RNG.hpp"
#include "WorldMapLocationTextKeys.hpp"
#include <boost/tokenizer.hpp>

using namespace std;
using namespace boost;

// Check to see if a tile is available for a creature by checking:
// - if a creature is present
// - (if a blocking feature is present and if the tile type permits movement), 
//   or the creature is incorporeal (and can ignore tile movement/blocking
//   feature details)
bool MapUtils::is_tile_available_for_creature(CreaturePtr creature, TilePtr tile)
{
  bool creature_incorporeal = creature && creature->has_status(StatusIdentifiers::STATUS_ID_INCORPOREAL);

  return tile && !is_creature_present(tile) && (!tile->get_is_blocking(creature) || creature_incorporeal);
}

// Check to see if a tile is available for an item by checking:
// - if a blocking feature is present
// - if the tile type permits movement
bool MapUtils::is_tile_available_for_item(TilePtr tile)
{
  return (!tile->get_is_blocking());
}

// Get the dimensions for a new map based on the current map, the coords, and the size.
// If it's a large map and the coordinates are in the centre, the dimensions will likely
// be size x size.  In other cases, the dimensions will be smaller, particularly if the
// coordinates fall near the map's borders.
Dimensions MapUtils::get_dimensions(MapPtr map, const Coordinate& coords, const int size)
{
  Dimensions new_dimensions(0, 0);
  
  Dimensions original_dimensions = map->size();
  int rows_orig = original_dimensions.get_y();
  int cols_orig = original_dimensions.get_x();
  
  int coord_row = coords.first;
  int coord_col = coords.second;
  
  int num_rows = 0;
  int num_cols = 0;
  
  for(int row = (coord_row - size); row <= (coord_row + size); row++)
  {
    if ((row >= 0) && (row <= rows_orig - 1))
    {
      if (num_cols == 0)
      {
        for (int col = (coord_col - size); col <= (coord_col + size); col++)
        {
          if ((col >= 0) && (col <= cols_orig - 1))
          {
            num_cols++;
          }
        }
      }
      
      num_rows++;
    }
  }

  new_dimensions.set_y(num_rows);
  new_dimensions.set_x(num_cols);
  
  return new_dimensions;
}

// Add a creature randomly to the map
bool MapUtils::place_creature_randomly(MapPtr map, const string& creature_id)
{
  bool creatures_generated = false;

  Dimensions dim = map->size();
  int rows = dim.get_y();
  int cols = dim.get_x();

  Game& game = Game::instance();
  ActionManager& am = game.get_action_manager_ref();
  CreatureFactory cf;

  // Generate the creature
  CreaturePtr creature = cf.create_by_creature_id(am, creature_id);

  if (creature)
  {
    // Place the creature
    for (int attempts = 0; attempts < 200; attempts++)
    {
      int creature_row = RNG::range(0, rows - 1);
      int creature_col = RNG::range(0, cols - 1);

      // Check to see if the spot is empty, and if a creature can be added there.
      TilePtr tile = map->at(creature_row, creature_col);

      if (MapUtils::is_tile_available_for_creature(creature, tile))
      {
        Coordinate coords(creature_row, creature_col);
        MapUtils::add_or_update_location(map, creature, coords);
        creatures_generated = true;

        break;
      }
    }
  }

  return creatures_generated;
}

// Add the tile and its connected tiles to the Component.
void MapUtils::add_connected_tiles_to_component(MapPtr map, const Coordinate& coord, const Dimensions& dim, const set<TileType>& exclusion_tiles, Component* component)
{
  int row = coord.first;
  int col = coord.second;

  TilePtr tile2 = map->at(row, col);
  if (exclusion_tiles.find(tile2->get_tile_type()) == exclusion_tiles.end())
  {
    component->insert(coord);

    vector<Coordinate> adjacent_coordinates = CoordUtils::get_adjacent_map_coordinates(dim, row, col);

    for (vector<Coordinate>::const_iterator c_it = adjacent_coordinates.begin(); c_it != adjacent_coordinates.end(); c_it++)
    {
      Coordinate adjacent_coord = *c_it;

      // If the adjacent coordinate is not in the component, add it.
      if (component->find(adjacent_coord) == component->end())
      {
        TilePtr tile = map->at(row, col);

        if (exclusion_tiles.find(tile->get_tile_type()) == exclusion_tiles.end())
        {
          add_connected_tiles_to_component(map, adjacent_coord, dim, exclusion_tiles, component);
        }
      }
    }
  }
}

// Generate a list of map components.
// FIXME: Unit tests
MapComponents MapUtils::get_map_components(MapPtr map, const set<TileType>& exclusion_tiles)
{
  MapComponents result;

  set<TileType>::const_iterator c_it;
  Dimensions dimensions = map->size();
  int height = dimensions.get_y();
  int width = dimensions.get_x();

  for (int y = 0; y < height; y++)
  {
    for (int x = 0; x < width; x++)
    {
      Coordinate current_tile_pair = make_pair(y, x);
      TilePtr current_tile = map->at(y, x);

      // Is it a rock tile?  If so, ignore, and check in
      // existing sets.
      c_it = exclusion_tiles.find(current_tile->get_tile_type());
      if (c_it == exclusion_tiles.end())
      {
        if (!is_tile_contained_in_an_existing_component(current_tile_pair, result))
        {
          Component component;
          add_connected_tiles_to_component(map, current_tile_pair, dimensions, exclusion_tiles, &component);

          result.push_back(component);
        }
      }
    }
  }
  return result;
}

bool MapUtils::add_or_update_location(MapPtr map, CreaturePtr creature, const Coordinate& c, TilePtr creatures_old_tile)
{
  bool added_location = false;

  TilePtr creatures_new_tile = map->at(c);
  
  if (creature->get_is_player())
  {
    map->add_or_update_location(WorldMapLocationTextKeys::CURRENT_PLAYER_LOCATION, c);
  }

  map->add_or_update_location(creature->get_id(), c);
  
  // Did the creature belong to a previous tile?  Can we move it to the new tile?  If so, then
  // remove from the old tile, and add to the new.
  if (creatures_new_tile && is_tile_available_for_creature(creature, creatures_new_tile))
  {
    if (creatures_old_tile)
    {
      creatures_old_tile->remove_creature();      
    }
    
    creatures_new_tile->set_creature(creature);
    added_location = true;

    // If this is a new creature, add this to the map's temporary creature list.
    if (!creatures_old_tile)
    {
      map->add_creature(creature);
    }
  }
  
  return added_location;
}

TilePtr MapUtils::get_tile_for_creature(const MapPtr& map, const CreaturePtr& creature)
{
  string creature_id = creature->get_id();
  Coordinate creature_location = map->get_location(creature_id);
  TilePtr creatures_tile = map->at(creature_location.first, creature_location.second);
  
  return creatures_tile;
}

// Get the adjacent tiles to a creature by getting the adjacent coordinates,
// mapping each coordinate to a direction, then looking up the tile and placing
// it in the result map.
std::map<Direction, TilePtr> MapUtils::get_adjacent_tiles_to_creature(const MapPtr& map, const CreaturePtr& creature)
{
  std::map<Direction, TilePtr> result_map;

  if (map && creature)
  {
    Coordinate creature_coord = map->get_location(creature->get_id());

    vector<Coordinate> adjacent_coords = CoordUtils::get_adjacent_map_coordinates(map->size(), creature_coord.first, creature_coord.second);

    for (const Coordinate& c : adjacent_coords)
    {
      Direction d = CoordUtils::get_direction(creature_coord, c);
      TilePtr tile = map->at(c);

      result_map.insert(make_pair(d, tile));
    }
  }
  
  return result_map;
}

// Get the adjacent tiles, plus the tile that the creature is standing on.
TileDirectionMap MapUtils::get_adjacent_and_creature_tiles(const MapPtr& map, const CreaturePtr& creature)
{
  TileDirectionMap direction_map = get_adjacent_tiles_to_creature(map, creature);
  TilePtr creature_tile = get_tile_for_creature(map, creature);
  direction_map.insert(make_pair(DIRECTION_NULL, creature_tile));

  return direction_map;
}

// Get all the tiles the creature can access (its own tile, and those adjacent) 
// that have terrain features.
TileDirectionMap MapUtils::get_tiles_with_features(MapPtr& map, CreaturePtr& creature)
{
  TileDirectionMap tiles_to_consider = MapUtils::get_adjacent_and_creature_tiles(map, creature);
  TileDirectionMap result_map;

  for (const TileDirectionMap::value_type& tile_pair : tiles_to_consider)
  {
    TilePtr tile = tile_pair.second;

    if (tile && tile->get_feature()) 
    {
      result_map.insert(tile_pair);
    }
  }

  return result_map;
}

// Get the number of adjacenct creatures
uint MapUtils::get_num_adjacent_creatures(const TileDirectionMap& adjacency_map)
{
  uint num_adjacent = 0;

  for (const TileDirectionMap::value_type& adjacent : adjacency_map)
  {
    TilePtr adjacent_tile = adjacent.second;

    if (adjacent_tile && adjacent_tile->has_creature())
    {
      num_adjacent++;
    }
  }

  return num_adjacent;
}

// Get a map of adjacent creatures to the current creature on the current
// map, keyed by their direction from the creature.
CreatureDirectionMap MapUtils::get_adjacent_creatures(const MapPtr& map, const CreaturePtr& creature)
{
  CreatureDirectionMap adjacent_creatures;

  if (map && creature)
  {
    Coordinate creature_coord = map->get_location(creature->get_id());

    vector<Coordinate> adjacent_coords = CoordUtils::get_adjacent_map_coordinates(map->size(), creature_coord.first, creature_coord.second);

    for (const Coordinate& c : adjacent_coords)
    {
      Direction d = CoordUtils::get_direction(creature_coord, c);
      TilePtr tile = map->at(c);
      CreaturePtr creature;

      if (tile && tile->has_creature())
      {
        creature = tile->get_creature();
        adjacent_creatures.insert(make_pair(d, creature));
      }
    }
  }
  
  return adjacent_creatures;
}

bool MapUtils::remove_creature(const MapPtr& map, const CreaturePtr& creature)
{
  bool result = false;

  if (creature)
  {
    TilePtr creature_tile = get_tile_for_creature(map, creature);
    
    if (creature_tile && map)
    {
      // If the creature is not the player, be sure to remove the creature from
      // the locations as well.  If it's the player, just remove the creature
      // from the tile.  If the player's dead, this doesn't much matter, and if
      // the player's just leaving the map, this allows the map to "remember"
      // the player's previous location for returning.
      if (!creature->get_is_player())
      {
        map->remove_creature(creature->get_id());
      }

      creature_tile->remove_creature();

      result = true;
    }
  }

  return result;
}

bool MapUtils::can_exit_map(MapExitPtr map_exit)
{
  bool can_exit = false;
  
  if (map_exit && (map_exit->is_using_map_id() || map_exit->is_using_terrain_type()))
  {
    can_exit = true;
  }
  
  return can_exit;
}

// Is there a feature on the tile, and does it block movement?
bool MapUtils::is_blocking_feature_present(TilePtr tile)
{
  if (tile)
  {
    FeaturePtr feature = tile->get_feature();
    
    if (feature)
    {
      return feature->get_is_blocking();
    }
  }
  
  return false;
}

// Is there a creature on the tile?
bool MapUtils::is_creature_present(TilePtr tile)
{
  if (tile)
  {
    CreaturePtr creature = tile->get_creature();
    
    return (creature != nullptr);
  }
  
  return false;
}

// Iterate through the existing components of the map, searching each one to see if the coordinates are contained within
// any one of them.
bool MapUtils::is_tile_contained_in_an_existing_component(const Coordinate& coord, const MapComponents& components)
{
  bool result = false;
  for (MapComponentsItc m_it = components.begin(); m_it != components.end(); m_it++)
  {
    Component component = *m_it;
    ComponentItc c_it = component.find(coord);

    if (c_it != component.end())
    {
      return true;
    }
  }

  return result;
}

string MapUtils::convert_coordinate_to_map_key(const Coordinate& c)
{
  ostringstream ss;
  ss << c.first << "-" << c.second;
  return ss.str();
}

string MapUtils::convert_coordinate_to_map_key(const int row, const int col)
{
  ostringstream ss;
  ss << row << "-" << col;
  return ss.str();
}

Coordinate MapUtils::convert_map_key_to_coordinate(const string& map_key)
{
  Coordinate coords(0,0);
  
  char_separator<char> sep("-");
  tokenizer<char_separator<char>> tokens(map_key, sep);

  tokenizer<char_separator<char>>:: iterator t_it = tokens.begin();
  
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

bool MapUtils::is_moving_from_land_type_tile_to_water_type_tile(TilePtr old_tile, TilePtr new_tile)
{
  bool moving_from_land_to_water = false;
  
  if (old_tile && new_tile)
  {
    TileSuperType old_st = old_tile->get_tile_super_type();
    TileSuperType new_st = new_tile->get_tile_super_type();
    
    moving_from_land_to_water = (old_st == TILE_SUPER_TYPE_GROUND) && (new_st == TILE_SUPER_TYPE_WATER);    
  }
  
  return moving_from_land_to_water;
}

// Check to see if there are any creatures hostile to the given creature ID on the map
bool MapUtils::hostile_creature_exists(const string& creature_id, MapPtr current_map)
{
  if (current_map)
  {
    map<std::string, CreaturePtr>& creature_map = current_map->get_creatures_ref();
    
    for (map<string, CreaturePtr>::const_iterator cr_it = creature_map.begin(); cr_it != creature_map.end(); cr_it++)
    {
      CreaturePtr creature = cr_it->second;
      
      if (creature->hostile_to(creature_id))
      {
        return true;
      }
    }
  }
  
  return false;
}

// Check to see if there is a creature (any!) adjacent to the creature
// represented by the given creature ID
bool MapUtils::adjacent_creature_exists(CreaturePtr creature, MapPtr map)
{
  if (map)
  {
    std::map<Direction, TilePtr> adjacent_tiles = MapUtils::get_adjacent_tiles_to_creature(map, creature);

    for (std::map<Direction, TilePtr>::const_iterator t_it = adjacent_tiles.begin(); t_it != adjacent_tiles.end(); t_it++)
    {
      TilePtr tile = t_it->second;

      if (tile && tile->has_creature())
      {
        return true;
      }
    }
  }
  
  return false;
}

// Check to see if there is a hostile creature adjacent to the creature represented by
// the given creature ID.
bool MapUtils::adjacent_hostile_creature_exists(const string& creature_id, MapPtr map)
{
  if (map)
  {
    Coordinate creature_location = map->get_location(creature_id);
    
    vector<Coordinate> adjacent_coords = CoordUtils::get_adjacent_map_coordinates(map->size(), creature_location.first, creature_location.second);
    
    for (const Coordinate& c : adjacent_coords)
    {
      TilePtr tile = map->at(c);
      
      if (tile)
      {
        CreaturePtr creature = tile->get_creature();
        
        if (creature)
        {
          // Is the creature on this tile hostile to the ID passed in?
          if (creature->hostile_to(creature_id))
          {
            return true;
          }
        }
      }
    }
  }
  
  return false;
}

void MapUtils::place_creature_on_previous_or_first_available_location(MapPtr map, CreaturePtr creature, const string& player_loc)
{
  Coordinate coords(0,0);

  // First, check the generic "player location" coordinates.
  if (creature->get_is_player())
  {
    string current_player_loc = WorldMapLocationTextKeys::CURRENT_PLAYER_LOCATION;
    if (map->has_location(current_player_loc))
    {
      coords = map->get_location(current_player_loc);
    }
  }

  if (map->has_location(player_loc))
  {
    coords = map->get_location(player_loc);
  }
                
  bool placed_creature = false;
  while (placed_creature == false && (CoordUtils::is_end(coords) == false))
  {
    placed_creature = MapUtils::add_or_update_location(map, creature, coords);

    // If we still haven't placed the creature, try the next tile...
    if (!placed_creature)
    {
      coords = CoordUtils::incr(coords, map->size());
    }
  }
}

bool MapUtils::is_corner(const Coordinate& c, const Direction d, MapPtr map)
{
  bool corner = false;

  vector<TilePtr> corner_tiles;

  TilePtr c_tile = map->at(c);
  TilePtr c1_tile;
  TilePtr c2_tile;

  corner_tiles.push_back(c_tile);

  if (d == DIRECTION_NORTH_WEST)
  {
    // Check the coordinates east and south
    c1_tile = map->at(CoordUtils::get_new_coordinate(c, DIRECTION_EAST));
    c2_tile = map->at(CoordUtils::get_new_coordinate(c, DIRECTION_SOUTH));
  }
  else if (d == DIRECTION_NORTH_EAST)
  {
    // Check the coordinates west and south
    c1_tile = map->at(CoordUtils::get_new_coordinate(c, DIRECTION_WEST));
    c2_tile = map->at(CoordUtils::get_new_coordinate(c, DIRECTION_SOUTH));
  }
  else if (d == DIRECTION_SOUTH_WEST)
  {
    // Check the coordinates east and north
    c1_tile = map->at(CoordUtils::get_new_coordinate(c, DIRECTION_EAST));
    c2_tile = map->at(CoordUtils::get_new_coordinate(c, DIRECTION_NORTH));
  }
  else if (d == DIRECTION_SOUTH_EAST)
  {
    // Check the coordinates west and north
    c1_tile = map->at(CoordUtils::get_new_coordinate(c, DIRECTION_WEST));
    c2_tile = map->at(CoordUtils::get_new_coordinate(c, DIRECTION_NORTH));
  }

  if (c_tile && c1_tile && c2_tile)
  {
    corner_tiles.push_back(c1_tile);
    corner_tiles.push_back(c2_tile);

    corner = true;

    for (TilePtr tile : corner_tiles)
    {
      // If it is not the case that the tile is solid (movement multiplier is
      // 0) or that there is a blocking feature, then there is "space" on this
      // tile, and it is not a corner.
      if (!((tile->get_movement_multiplier() == 0) || (tile->has_blocking_feature())))
      {
        corner = false;
        break;
      }
    }
  }

  return corner;
}

// Check to see if the given coordinates fall within the given dimensions.
// This function is provided to ensure "clean" inputs for cases like the
// scripting engine, etc.
bool MapUtils::are_coordinates_within_dimensions(const Coordinate& c, const Dimensions& d)
{
  return (c.first >= 0 && c.first < d.get_y() && c.second >= 0 && c.second < d.get_x());
}

std::map<int, pair<string, Coordinate>> MapUtils::create_distance_map(CreaturePtr creature, MapPtr map, bool hostile_only)
{
  std::map<int, pair<string, Coordinate>> distance_map;

  if (map != nullptr && creature != nullptr)
  {
    string creature_id = creature->get_id();
    std::map<string, CreaturePtr>& creatures = map->get_creatures_ref();
    Coordinate creature_location = map->get_location(creature->get_id());

    for (std::map<string, CreaturePtr>::iterator c_it = creatures.begin(); c_it != creatures.end(); c_it++)
    {
      CreaturePtr potential_target_creature = c_it->second;
      string potential_creature_id = potential_target_creature->get_id();

      // Make sure the targetted creature isn't the one doing the aiming.
      // Targetting one's self would be unfortunate.
      if (potential_target_creature && (potential_creature_id != creature_id))
      {
        // Get the potential target's coordinate from the main map, using its creature ID.
        Coordinate c = map->get_location(c_it->first);

        // Is the creature hostile towards the ranged combat creature?
        ThreatRatings& threat_ratings = potential_target_creature->get_decision_strategy()->get_threats_ref();

        if (threat_ratings.has_threat(creature_id).first || !hostile_only)
        {
          int distance = CoordUtils::chebyshev_distance(creature_location, c);
          distance_map.insert(make_pair(distance, make_pair(potential_creature_id, c)));
        }
      }
    }
  }

  return distance_map;
}

#ifdef UNIT_TESTS
#include "unit_tests/Map_test.cpp"
#include "unit_tests/MapUtils_test.cpp"
#endif
