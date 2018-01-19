#include <boost/tokenizer.hpp>
#include "ActionTextKeys.hpp"
#include "Conversion.hpp"
#include "CoordUtils.hpp"
#include "CreatureFactory.hpp"
#include "CreatureProperties.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "FieldOfViewStrategyFactory.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "HostilityManager.hpp"
#include "Log.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "MovementAccumulationChecker.hpp"
#include "MovementAccumulationUpdater.hpp"
#include "MovementTextKeys.hpp"
#include "PickupAction.hpp"
#include "RNG.hpp"
#include "TextMessages.hpp"
#include "TileDescriber.hpp"
#include "ViewMapTranslator.hpp"
#include "WorldMapLocationTextKeys.hpp"

using namespace std;
using namespace boost;

// Does the area around a tile allow creature generation?
// Creatures can't be generated within a couple of steps of a stairway.
bool MapUtils::does_area_around_tile_allow_creature_generation(MapPtr map, const Coordinate& c)
{
  bool gen_ok = true;

  if (map != nullptr)
  {
    vector<Coordinate> adjacent_coordinates = CoordUtils::get_adjacent_map_coordinates(map->size(), c.first, c.second, 2);

    for (const Coordinate& adj : adjacent_coordinates)
    {
      TilePtr tile = map->at(adj);

      if (tile)
      {
        TileType tt = tile->get_tile_type();

        if (tt == TileType::TILE_TYPE_UP_STAIRCASE || tt == TileType::TILE_TYPE_DOWN_STAIRCASE)
        {
          gen_ok = false;
          break;
        }
      }
    }
  }

  return gen_ok;
}

// Check to see if a tile is available for a creature by checking:
// - if a creature is present
// - (if a blocking feature is present and if the tile type permits movement), 
//   or the creature is incorporeal (and can ignore tile movement/blocking
//   feature details)
bool MapUtils::is_tile_available_for_creature(CreaturePtr creature, TilePtr tile)
{
  return tile && !is_creature_present(tile) && !tile->get_is_blocking(creature);
}

// Check to see if a tile is available for an item by checking:
// - if a blocking feature is present
// - if the tile type permits movement
bool MapUtils::is_tile_available_for_item(TilePtr tile)
{
  return (!tile->get_is_blocking());
}

// Swap two creatures on their tiles.
void MapUtils::swap_places(MapPtr map, CreaturePtr creature, CreaturePtr adjacent_creature)
{
  if (creature && adjacent_creature)
  {
    ostringstream ss;
    ss << "Swapping " << creature->get_id() << " and " << adjacent_creature->get_id();
    Log::instance().debug(ss.str());

    // Get the location info.
    Coordinate cr_loc = map->get_location(creature->get_id());
    Coordinate adj_loc = map->get_location(adjacent_creature->get_id());
    TilePtr creatures_current_tile = map->at(cr_loc);

    // Remove the creatures, then add them in the new location.
    MapUtils::remove_creature(map, creature);
    MapUtils::remove_creature(map, adjacent_creature);

    MapUtils::add_or_update_location(map, creature, adj_loc);
    MapUtils::add_or_update_location(map, adjacent_creature, cr_loc);
  }
}

// Check to see if the creature can squeeze by into the next tile.
bool MapUtils::can_squeeze_by(MapPtr map, CreaturePtr creature, const Coordinate& new_coords, const Direction d)
{
  Coordinate potential_squeeze_coords = CoordUtils::get_new_coordinate(new_coords, d, 1);
  TilePtr potential_squeeze_tile = map->at(potential_squeeze_coords);

  return ((potential_squeeze_tile != nullptr) && MapUtils::is_tile_available_for_creature(creature, potential_squeeze_tile));
}

// If there's a creature adjacent to the current one, but the next
// spot over is free, the creature can squeeze by the adjacent one
// and into the next tile.
bool MapUtils::squeeze_by(MapPtr map, CreaturePtr creature, const Coordinate& new_coords, const Direction d)
{
  bool movement_success = false;

  Coordinate potential_squeeze_coords = CoordUtils::get_new_coordinate(new_coords, d, 1);
  TilePtr potential_squeeze_tile = map->at(potential_squeeze_coords);

  if (creature != nullptr)
  {
    ostringstream ss;

    ss << "Creature " << creature->get_id() << " is squeezing by " << new_coords.first << "," << new_coords.second;
    Log::instance().debug(ss.str());

    if (potential_squeeze_tile != nullptr && MapUtils::is_tile_available_for_creature(creature, potential_squeeze_tile))
    {
      MapUtils::remove_creature(map, creature);
      MapUtils::add_or_update_location(map, creature, potential_squeeze_coords);
      movement_success = true;
    }
  }

  return movement_success;
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
        ostringstream ss;
        ss << "Placing creature " << creature->get_id() << " randomly at " << creature_row << "," << creature_col;
        Log::instance().debug(ss.str());

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

  if (creature != nullptr)
  {
    Log& log = Log::instance();

    if (log.debug_enabled())
    {
      ostringstream ss;
      ss << "Adding creature " << creature->get_id() << " (" << creature->get_original_id() << ") to map at " << c.first << "," << c.second;
      log.debug(ss.str());
    }
  }
  
  TilePtr creatures_new_tile = map->at(c);

  if (creature->get_is_player())
  {
    map->add_or_update_location(WorldMapLocationTextKeys::CURRENT_PLAYER_LOCATION, c);
  }

  map->add_or_update_location(creature->get_id(), c);

  // Did the creature belong to a previous tile?  Can we move it to the new tile?  If so, then
  // remove from the old tile, and add to the new.
  if (creature && creatures_new_tile && is_tile_available_for_creature(creature, creatures_new_tile))
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

    add_tile_related_messages(creature, creatures_new_tile);

    // Pick up any applicable items on the tile.
    DecisionStrategyPtr dec = creature->get_decision_strategy();

    if (dec != nullptr)
    {
      bool autopickup = dec->get_autopickup();

      if (autopickup)
      {
        set<ItemType> auto_items = dec->get_autopickup_types();

        if (!auto_items.empty())
        {
          Game& game = Game::instance();
          PickupAction pa;

          pa.pick_up(creature, &game.get_action_manager_ref(), PickUpType::PICK_UP_TYPES, auto_items);
        }
      }
    }
  }

  // Run the movement accumulation checker, in case the creature moved into a
  // dangerous/special tile.
  MovementAccumulationUpdater mau;
  mau.update(creature, creatures_new_tile);

  ICreatureRegenerationPtr move_checker = std::make_shared<MovementAccumulationChecker>();
  move_checker->tick(creature, creatures_new_tile, 0, 0);
  
  return added_location;
}

vector<string> MapUtils::get_creatures_with_creature_in_view(const MapPtr& map, const string& creature_id)
{
  CreatureMap creatures = map->get_creatures();
  vector<string> viewing_creatures;

  for (const auto& cr_pair : creatures)
  {
    if (cr_pair.first != creature_id)
    {
      CreaturePtr viewing_creature = cr_pair.second;

      if (viewing_creature != nullptr)
      {
        MapPtr fov_map = viewing_creature->get_decision_strategy()->get_fov_map();

        if (fov_map != nullptr)
        {
          CreatureMap fov_creatures = fov_map->get_creatures();
          if (fov_creatures.find(creature_id) != fov_creatures.end())
          {
            viewing_creatures.push_back(viewing_creature->get_id());
          }
        }
      }
    }
  }

  return viewing_creatures;
}

Coordinate MapUtils::get_coordinate_for_creature(const MapPtr& map, const CreaturePtr& creature)
{
  string creature_id = creature->get_id();
  return map->get_location(creature_id);
}

TilePtr MapUtils::get_tile_for_creature(const MapPtr& map, const CreaturePtr& creature)
{
  string creature_id = creature->get_id();
  Coordinate creature_location = map->get_location(creature_id);
  TilePtr creatures_tile = map->at(creature_location.first, creature_location.second);
  
  return creatures_tile;
}

uint MapUtils::get_num_following_creatures(const MapPtr& map)
{
  uint count = 0;
  std::map<string, CreaturePtr> creatures = map->get_creatures();
  for (const auto& cr_pair : creatures)
  {
    if (cr_pair.second && cr_pair.second->has_additional_property(CreatureProperties::CREATURE_PROPERTIES_FOLLOWS_CR_ID))
    {
      count++;
    }
  }

  return count;
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

std::vector<TilePtr> MapUtils::get_adjacent_tiles_to_creature_unsorted(const MapPtr& map, const CreaturePtr& creature, const int offset)
{
  std::vector<TilePtr> result_map;

  if (map && creature)
  {
    Coordinate creature_coord = map->get_location(creature->get_id());

    vector<Coordinate> adjacent_coords = CoordUtils::get_adjacent_map_coordinates(map->size(), creature_coord.first, creature_coord.second, offset);

    for (const Coordinate& c : adjacent_coords)
    {
      TilePtr tile = map->at(c);
      result_map.push_back(tile);
    }
  }

  return result_map;
}

// Do the adjacent tiles in the given direction match a particular tile type?
bool MapUtils::adjacent_tiles_match_type(const MapPtr& map, const Coordinate& c, const vector<Direction>& directions, const TileType type_to_match)
{
  bool all_match = true;

  for (const Direction d : directions)
  {
    TilePtr tile = map->at(CoordUtils::get_new_coordinate(c, d));

    if (!tile || tile->get_tile_type() != type_to_match)
    {
      all_match = false;
      break;
    }
  }

  return all_match;
}

// Determine how many adjacent tiles are available to the creature
uint MapUtils::get_num_adjacent_movement_directions(const MapPtr& map, const CreaturePtr& creature)
{
  uint num_dirs = 0;
  TileDirectionMap tdm = MapUtils::get_adjacent_tiles_to_creature(map, creature);

  for (const auto& tdm_pair : tdm)
  {
    if (tdm_pair.second != nullptr)
    {
      TilePtr tile = tdm_pair.second;

      if (MapUtils::is_tile_available_for_creature(creature, tile))
      {
        num_dirs++;
      }
    }
  }

  return num_dirs;
}

// Get the tile adjacent to the creature's tile in a given direction.
// The returned tile may be null - e.g., if getting north of (0,0),
// etc.
TilePtr MapUtils::get_adjacent_tile(const MapPtr& map, const CreaturePtr& creature, const Direction d, const int offset)
{
  Coordinate c = map->get_location(creature->get_id());
  Coordinate new_coord = CoordUtils::get_new_coordinate(c, d, offset);
  TilePtr adj_tile = map->at(new_coord);

  return adj_tile;
}

// Get the adjacent tiles, plus the tile that the creature is standing on.
TileDirectionMap MapUtils::get_adjacent_and_creature_tiles(const MapPtr& map, const CreaturePtr& creature)
{
  TileDirectionMap direction_map = get_adjacent_tiles_to_creature(map, creature);
  TilePtr creature_tile = get_tile_for_creature(map, creature);
  direction_map.insert(make_pair(Direction::DIRECTION_NULL, creature_tile));

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

vector<CreaturePtr> MapUtils::get_adjacent_creatures_unsorted(const MapPtr& map, const CreaturePtr& creature)
{
  vector<CreaturePtr> adj_creatures;

  if (map && creature)
  {
    Coordinate creature_coord = map->get_location(creature->get_id());

    vector<Coordinate> adjacent_coords = CoordUtils::get_adjacent_map_coordinates(map->size(), creature_coord.first, creature_coord.second);

    for (const Coordinate& c : adjacent_coords)
    {
      TilePtr tile = map->at(c);

      if (tile && tile->has_creature())
      {
        adj_creatures.push_back(tile->get_creature());
      }
    }
  }

  return adj_creatures;
}
bool MapUtils::remove_creature(const MapPtr& map, const CreaturePtr& creature, const bool force_player_removal)
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
      if (!creature->get_is_player() || force_player_removal)
      {
        map->remove_creature(creature->get_id());
      }

      creature_tile->remove_creature();

      result = true;
    }
  }

  return result;
}

bool MapUtils::tiles_in_range_match_type(MapPtr map, const BoundingBox& bb, const TileType tt)
{
  bool match = false;

  if (map != nullptr)
  {
    match = true;

    Coordinate top_left = bb.get_c1();
    Coordinate bottom_right = bb.get_c2();

    for (int y = top_left.first; y <= bottom_right.first; y++)
    {
      for (int x = top_left.second; x <= bottom_right.second; x++)
      {
        TilePtr tile = map->at(y,x);

        if (!tile)
        {
          match = false;
          break;
        }
        else
        {
          if (tile->get_tile_type() != tt)
          {
            match = false;
            break;
          }
        }
      }

      if (!match)
      {
        break;
      }
    }
  }

  return match;
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

pair<bool, string> MapUtils::is_in_shop_or_adjacent(MapPtr map, const Coordinate& c)
{
  pair<bool, string> result = make_pair(false, "");

  if (map != nullptr)
  {
    std::map<string, Shop> shops = map->get_shops();

    for (const auto& shop_pair : shops)
    {
      Shop shop = shop_pair.second;

      Coordinate start = shop.get_start();
      Coordinate end = shop.get_end();

      if (c.first >= start.first-1 && c.first <= end.first+1 && c.second >= start.second-1 && c.second <= end.second+1)
      {
        result.first = true;
        result.second = shop_pair.first;

        break;
      }
    }
  }

  return result;
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
    
    moving_from_land_to_water = (old_st == TileSuperType::TILE_SUPER_TYPE_GROUND) && (new_st == TileSuperType::TILE_SUPER_TYPE_WATER);    
  }
  
  return moving_from_land_to_water;
}

// Get all the creatures hostile to a particular creature.
vector<CreaturePtr> MapUtils::get_hostile_creatures(const string& creature_id, MapPtr current_map)
{
  vector<CreaturePtr> hostile_creatures;

  if (current_map != nullptr)
  {
    map<std::string, CreaturePtr>& creature_map = current_map->get_creatures_ref();
    for (auto& cr_pair : creature_map)
    {
      CreaturePtr creature = cr_pair.second;

      if (creature && creature->hostile_to(creature_id))
      {
        hostile_creatures.push_back(creature);
      }
    }
  }

  return hostile_creatures;
}

bool MapUtils::are_creatures_adjacent(MapPtr current_map, CreaturePtr c1, CreaturePtr c2)
{
  bool adjacent = false;

  if (current_map && c1 && c2)
  {
    Coordinate c1_coord = current_map->get_location(c1->get_id());
    Coordinate c2_coord = current_map->get_location(c2->get_id());

    adjacent = CoordUtils::are_coordinates_adjacent(c1_coord, c2_coord);
  }

  return adjacent;
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
      
      if (creature && creature->hostile_to(creature_id))
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

bool MapUtils::adjacent_creature_exists(const int row, const int col, MapPtr map)
{
  vector<Coordinate> coords = CoordUtils::get_adjacent_map_coordinates(map->size(), row, col);

  for (const auto& coord : coords)
  {
    TilePtr tile = map->at(coord);

    if (tile && tile->has_creature())
    {
      return true;
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

void MapUtils::place_creature_on_previous_location(MapPtr map, CreaturePtr creature, const string& player_loc)
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
  
  TilePtr placement_tile = map->at(coords);

  if (placement_tile != nullptr)
  {
    // Anything here? If so, remove it - the creature moving to the tile always
    // gets priority.
    if (placement_tile->has_creature())
    {
      CreaturePtr existing_creature = placement_tile->get_creature();
      MapUtils::remove_creature(map, existing_creature);
    }

    MapUtils::add_or_update_location(map, creature, coords);
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

  if (d == Direction::DIRECTION_NORTH_WEST)
  {
    // Check the coordinates east and south
    c1_tile = map->at(CoordUtils::get_new_coordinate(c, Direction::DIRECTION_EAST));
    c2_tile = map->at(CoordUtils::get_new_coordinate(c, Direction::DIRECTION_SOUTH));
  }
  else if (d == Direction::DIRECTION_NORTH_EAST)
  {
    // Check the coordinates west and south
    c1_tile = map->at(CoordUtils::get_new_coordinate(c, Direction::DIRECTION_WEST));
    c2_tile = map->at(CoordUtils::get_new_coordinate(c, Direction::DIRECTION_SOUTH));
  }
  else if (d == Direction::DIRECTION_SOUTH_WEST)
  {
    // Check the coordinates east and north
    c1_tile = map->at(CoordUtils::get_new_coordinate(c, Direction::DIRECTION_EAST));
    c2_tile = map->at(CoordUtils::get_new_coordinate(c, Direction::DIRECTION_NORTH));
  }
  else if (d == Direction::DIRECTION_SOUTH_EAST)
  {
    // Check the coordinates west and north
    c1_tile = map->at(CoordUtils::get_new_coordinate(c, Direction::DIRECTION_WEST));
    c2_tile = map->at(CoordUtils::get_new_coordinate(c, Direction::DIRECTION_NORTH));
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

std::multimap<int, pair<string, Coordinate>> MapUtils::create_distance_map(CreaturePtr creature, MapPtr map, bool hostile_only)
{
  std::multimap<int, pair<string, Coordinate>> distance_map;

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

map<TileType, vector<TilePtr>> MapUtils::partition_tiles(MapPtr current_map)
{
  map<TileType, vector<TilePtr>> part_tiles;

  if (current_map != nullptr)
  {
    TilesContainer tc = current_map->get_tiles();

    for (const auto& tc_pair : tc)
    {
      TilePtr tile = tc_pair.second;

      if (tile != nullptr)
      {
        part_tiles[tile->get_tile_type()].push_back(tile);
      }
    }
  }

  return part_tiles;
}

void MapUtils::anger_shopkeeper_if_necessary(const Coordinate& c, MapPtr current_map, CreaturePtr anger_creature)
{
  if (current_map != nullptr && anger_creature != nullptr)
  {
    pair<bool, string> shop_adjacency = MapUtils::is_in_shop_or_adjacent(current_map, c);
    if (shop_adjacency.first)
    {
      std::map<string, Shop> shops = current_map->get_shops();
      auto s_it = shops.find(shop_adjacency.second);
      if (s_it != shops.end())
      {
        // The shopkeeper is justifiably pissed!
        HostilityManager hm;
        hm.set_hostility_to_creature(current_map->get_creature(s_it->second.get_shopkeeper_id()), anger_creature->get_id());

        IMessageManager& manager = MM::instance(MessageTransmit::MAP, anger_creature, true);
        manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_ENRAGED_SHOPKEEPER));
        manager.send();
      }
    }
  }
}

void MapUtils::calculate_fov_maps_for_all_creatures(MapPtr current_map)
{
  std::map<string, CreaturePtr> map_creatures = current_map->get_creatures();

  for (const auto& cr_pair : map_creatures)
  {
    CreaturePtr current_creature = cr_pair.second;

    if (current_creature)
    {
      Coordinate creature_coords = current_map->get_location(current_creature->get_id());
      MapPtr view_map = ViewMapTranslator::create_view_map_around_tile(current_map, creature_coords, CreatureConstants::DEFAULT_CREATURE_LINE_OF_SIGHT_LENGTH /* FIXME */);

      FieldOfViewStrategyPtr fov_strategy = FieldOfViewStrategyFactory::create_field_of_view_strategy(current_creature->get_is_player());
      MapPtr fov_map = fov_strategy->calculate(current_creature, view_map, creature_coords, CreatureConstants::DEFAULT_CREATURE_LINE_OF_SIGHT_LENGTH /* FIXME */);
      DecisionStrategyPtr strategy = current_creature->get_decision_strategy();

      if (strategy)
      {
        strategy->set_fov_map(fov_map);
      }
    }
  }
}

int MapUtils::calculate_depth_delta(MapPtr map, TilePtr tile, const ExitMovementType emt)
{
  int depth_incr = 1;

  if (map != nullptr)
  {
    string m_depthincr_s = map->get_property(TileProperties::TILE_PROPERTY_DEPTH_INCREMENT);
    
    if (!m_depthincr_s.empty())
    {
      depth_incr = String::to_int(m_depthincr_s);
    }
  }

  if (tile != nullptr)
  {
    string t_depthincr_s = tile->get_additional_property(TileProperties::TILE_PROPERTY_DEPTH_INCREMENT);

    if (!t_depthincr_s.empty())
    {
      depth_incr = String::to_int(t_depthincr_s);
    }
  }

  if ((emt == ExitMovementType::EXIT_MOVEMENT_ASCEND && depth_incr > 0) || 
      (emt == ExitMovementType::EXIT_MOVEMENT_DESCEND && depth_incr < 0))
  {
    depth_incr *= -1;
  }

  return depth_incr;
}

// Add any messages after moving to a particular tile:
// - Should a message be displayed about the tile automatically? (staircases, etc)
//       If so, add it.
// - Are there any items on the tile?
//       If so, add the appropriate message.
void MapUtils::add_tile_related_messages(CreaturePtr creature, TilePtr tile)
{
  bool tile_message_added = add_message_about_tile_if_necessary(creature, tile);
  bool item_message_added = add_message_about_items_on_tile_if_necessary(creature, tile);

  if (tile_message_added || item_message_added)
  {
    IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
    manager.send();
  }
}

// Add a message about the tile if necessary.
bool MapUtils::add_message_about_tile_if_necessary(CreaturePtr creature, TilePtr tile)
{
  bool msg_added = false;

  if (creature && tile && creature->get_is_player())
  {
    IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());

    if (tile->display_description_on_arrival() || tile->has_extra_description())
    {
      TileDescriber td(tile);
      manager.add_new_message(td.describe());
      msg_added = true;
    }
    else if (tile->has_inscription())
    {
      manager.add_new_message(TextMessages::get_inscription_message(tile->get_inscription_sid()));
      msg_added = true;
    }
  }

  return msg_added;
}

// Add a message if the creature is the player, and if there are items on
// the tile.
bool MapUtils::add_message_about_items_on_tile_if_necessary(CreaturePtr creature, TilePtr tile)
{
  bool msg_added = false;

  if (creature && creature->get_is_player())
  {
    IInventoryPtr tile_items = tile->get_items();

    if (!tile_items->empty())
    {
      string item_message;

      // One item
      if (tile_items->size() == 1)
      {
        ItemPtr item_on_tile = tile_items->at(0);

        if (item_on_tile)
        {
          CurrentCreatureAbilities cca;
          item_message = TextMessages::get_item_on_ground_description_message(!cca.can_see(creature), item_on_tile);
        }
      }
      // Multiple items
      else
      {
        item_message = StringTable::get(MovementTextKeys::ITEMS_ON_TILE);
      }

      // Send the message
      if (!item_message.empty())
      {
        IMessageManager& manager = MM::instance();
        manager.add_new_message(item_message);
        msg_added = true;
      }
    }
  }

  return msg_added;
}

#ifdef UNIT_TESTS
#include "unit_tests/Map_test.cpp"
#include "unit_tests/MapUtils_test.cpp"
#endif
