#include <boost/tokenizer.hpp>
#include "ActionTextKeys.hpp"
#include "Conversion.hpp"
#include "CoordUtils.hpp"
#include "CreatureFactory.hpp"
#include "CreatureGenerationConstants.hpp"
#include "CreatureProperties.hpp"
#include "CreatureTileSafetyChecker.hpp"
#include "CreatureUtils.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "DirectionLocationTextKeys.hpp"
#include "DirectionUtils.hpp"
#include "FieldOfViewStrategyFactory.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "HostilityManager.hpp"
#include "IntelligenceConstants.hpp"
#include "ItemProperties.hpp"
#include "LineOfSightCalculator.hpp"
#include "Log.hpp"
#include "MapCreatureGenerator.hpp"
#include "MapProperties.hpp"
#include "MapUtils.hpp"
#include "MeleeWeaponRangeCalculator.hpp"
#include "MessageManagerFactory.hpp"
#include "MovementAccumulationChecker.hpp"
#include "MovementAccumulationUpdater.hpp"
#include "MoveScript.hpp"
#include "MovementTextKeys.hpp"
#include "MusicEvent.hpp"
#include "PickupAction.hpp"
#include "RaceManager.hpp"
#include "RageEffect.hpp"
#include "RNG.hpp"
#include "SettlementGeneratorUtils.hpp"
#include "TextKeys.hpp"
#include "TextMessages.hpp"
#include "TileDescriber.hpp"
#include "TileDescriptionKeys.hpp"
#include "TileGenerator.hpp"
#include "ViewMapTranslator.hpp"
#include "WeaponManager.hpp"
#include "WorldMapLocationTextKeys.hpp"

using namespace std;

const int MapUtils::PLAYER_RESTRICTED_ZONE_RADIUS = 8;
const int MapUtils::CANNOT_MOVE_SCORE = -1;

string MapUtils::get_tile_direction_description(const Coordinate& base, const Coordinate& dest)
{
  string desc = StringTable::get(TileDescriptionKeys::TILE_DESCRIPTION_DISTANCE_FROM);

  pair<Direction, int> ns = CoordUtils::get_y_distance(base, dest);
  pair<Direction, int> ew = CoordUtils::get_x_distance(base, dest);

  ostringstream direction_info;

  if (ns.first == Direction::DIRECTION_NULL && ew.first == Direction::DIRECTION_NULL)
  {
    direction_info << "0";
  }
  else if (ns.first == Direction::DIRECTION_NULL)
  {
    string dir_sid = DirectionLocationTextKeys::get_direction_location_sid(ew.first);
    direction_info << ew.second << " " << StringTable::get(dir_sid);
  }
  else if (ew.first == Direction::DIRECTION_NULL)
  {
    string dir_sid = DirectionLocationTextKeys::get_direction_location_sid(ns.first);
    direction_info << ns.second << " " << StringTable::get(dir_sid);
  }
  else
  {
    string ns_dir_sid = DirectionLocationTextKeys::get_direction_location_sid(ns.first);
    direction_info << ns.second << " " << StringTable::get(ns_dir_sid) << ", ";

    string ew_dir_sid = DirectionLocationTextKeys::get_direction_location_sid(ew.first);
    direction_info << ew.second << " " << StringTable::get(ew_dir_sid);
  }

  boost::replace_first(desc, "%s", direction_info.str());
  return desc;
}


// Does the area around a tile allow creature generation?
// Creatures can't be generated within a couple of steps of a stairway.
// They also shouldn't be generated close to the player.
bool MapUtils::does_area_around_tile_allow_creature_generation(MapPtr map, const Coordinate& c)
{
  bool gen_ok = true;

  if (map != nullptr)
  {
    gen_ok = (MapUtils::does_area_around_tile_contain_staircase(map, c) == false);
    
    if (gen_ok)
    {
      gen_ok = (MapUtils::is_coordinate_within_player_restricted_zone(map, c) == false);
    }
  }

  return gen_ok;
}

bool MapUtils::does_area_around_tile_contain_staircase(MapPtr map, const Coordinate& c)
{
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
          return true;
        }
      }
    }

    return false;
  }

  return false;
}

bool MapUtils::is_coordinate_within_player_restricted_zone(MapPtr map, const Coordinate& c)
{
  if (map != nullptr)
  {
    Coordinate player_coord = map->get_location(CreatureID::CREATURE_ID_PLAYER);

    if (!CoordUtils::is_end(player_coord))
    {
      int distance = CoordUtils::chebyshev_distance(player_coord, c);

      if (distance <= PLAYER_RESTRICTED_ZONE_RADIUS)
      {
        return true;
      }
    }
  }

  return false;
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
// - if the inventory type isn't null
bool MapUtils::is_tile_available_for_item(TilePtr tile)
{
  return (!tile->get_is_blocking() && tile->get_items()->get_allows_items() == AllowsItemsType::ALLOWS_ITEMS);
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

    if (creatures_current_tile && !creatures_current_tile->get_dangerous(adjacent_creature))
    {
      // Remove the creatures, then add them in the new location.
      MapUtils::remove_creature(map, creature);
      MapUtils::remove_creature(map, adjacent_creature);

      MapUtils::add_or_update_location(map, creature, adj_loc);
      MapUtils::add_or_update_location(map, adjacent_creature, cr_loc);
    }
    else
    {
      IMessageManager& manager = MMF::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_SWITCH_REFUSED));

      manager.send();
    }
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
  CreaturePtr creature = cf.create_by_creature_id(am, creature_id, map);

  if (creature != nullptr)
  {
    CreatureTileSafetyChecker ctsc;

    // Place the creature
    for (int attempts = 0; attempts < 200; attempts++)
    {
      int creature_row = RNG::range(0, rows - 1);
      int creature_col = RNG::range(0, cols - 1);

      // Check to see if the spot is empty, if it's safe (eg don't generate
      // air-breathers on water) and if a creature can be added there.
      TilePtr tile = map->at(creature_row, creature_col);

      if (ctsc.is_tile_safe_for_creature(creature, tile) && MapUtils::is_tile_available_for_creature(creature, tile))
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
  string creature_id;
  Log& log = Log::instance();

  if (creature != nullptr)
  {
    creature_id = creature->get_id();

    if (log.debug_enabled())
    {
      ostringstream ss;
      ss << "Adding creature " << creature_id << " (" << creature->get_original_id() << ") to map at " << c.first << "," << c.second;
      log.debug(ss.str());
    }
  }
  
  TilePtr creatures_new_tile = map->at(c);

  if (creature->get_is_player())
  {
    map->add_or_update_location(WorldMapLocationTextKeys::CURRENT_PLAYER_LOCATION, c);
  }

  map->add_or_update_location(creature_id, c);

  // Did the creature belong to a previous tile?  Can we move it to the new tile?  If so, then
  // remove from the old tile, and add to the new.
  if (creature && creatures_new_tile && is_tile_available_for_creature(creature, creatures_new_tile))
  {
    if (creatures_old_tile)
    {
      creatures_old_tile->remove_creature();      
    }
    
    creatures_new_tile->set_creature(creature);
    
    // Mark the properties for automove if we're dealing with the player.
    if (creatures_old_tile != nullptr && creature->get_is_player())
    {
      IInventoryPtr old_tile_items = creatures_old_tile->get_items();
      if (old_tile_items != nullptr)
      {
        old_tile_items->set_additional_property(ItemProperties::ITEM_PROPERTIES_MARK_AUTOMOVE, to_string(true));
      }
    }

    added_location = true;

    // If this is a new creature, add this to the map's temporary creature list.
    if (!creatures_old_tile)
    {
      map->add_creature(creature);
    }

    add_tile_related_messages(creature, creatures_new_tile, map->get_map_type() == MapType::MAP_TYPE_WORLD);

    // Pick up any applicable items on the tile.
    DecisionStrategy* dec = creature->get_decision_strategy();

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

    // Run the movement accumulation checker, in case the creature moved into a
    // dangerous/special tile.
    MovementAccumulationUpdater mau;
    mau.update(creature, creatures_new_tile);

    ICreatureRegenerationPtr move_checker = std::make_unique<MovementAccumulationChecker>();
    move_checker->tick(creature, creatures_new_tile, 0, 0);

    // Run any movement scripts associated with the creature.
    run_movement_scripts(creature, map->get_map_id(), c);
  }
  else
  {
    CreaturePtr existing_cr = creatures_new_tile->get_creature();

    if (existing_cr != nullptr)
    {
      log.debug("Could not add creature " + creature_id + " to (" + String::create_string_from_coordinate(c) + ") because another creature (" + creatures_new_tile->get_creature()->get_id() + ") is present.");
    }
  }

  return added_location;
}

bool MapUtils::does_hostile_creature_exist(MapPtr map, const vector<string>& creature_list, const string& hostile_to_id)
{
  if (map != nullptr)
  {
    for (const auto& c_id : creature_list)
    {
      CreaturePtr creature = map->get_creature(c_id);

      if (creature != nullptr && creature->get_decision_strategy()->get_threats_ref().has_threat(hostile_to_id).first)
      {
        return true;
      }
    }
  }

  return false;
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

      // If the viewing creature has the creature in view, update the fov map
      // and check again.  FOV maps are typically only updated at the start
      // of each turn, and so can become stale.
      if (viewing_creature != nullptr && viewing_creature->has_creature_in_view(creature_id))
      {
        CreatureUtils::update_fov_map(map, nullptr, viewing_creature);

        if (viewing_creature->has_creature_in_view(creature_id))
        {
          viewing_creatures.push_back(viewing_creature->get_id());
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
  TilePtr creatures_tile;

  if (map != nullptr && creature != nullptr)
  {
    string creature_id = creature->get_id();
    Coordinate creature_location = map->get_location(creature_id);
    creatures_tile = map->at(creature_location.first, creature_location.second);
  }
  
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

// Get the adjacent tiles to a particular creature that another creature can
// be placed on.
std::map<Direction, TilePtr> MapUtils::get_available_adjacent_tiles_to_creature(const MapPtr& map, const CreaturePtr& centre_creature, const CreaturePtr& creature_to_place)
{
  std::map<Direction, TilePtr> result_map;

  if (map != nullptr && centre_creature != nullptr && creature_to_place != nullptr)
  {
    std::map<Direction, TilePtr> adjacent_map = get_adjacent_tiles_to_creature(map, centre_creature);

    for (const auto& t_pair : adjacent_map)
    {
      if (MapUtils::is_tile_available_for_creature(creature_to_place, t_pair.second))
      {
        result_map.insert(t_pair);
      }
    }
  }

  return result_map;
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

// Do the adjacent tiles in the given direction contain a particular tile type?
bool MapUtils::adjacent_tiles_contain_type(const MapPtr& map, const Coordinate& c, const vector<Direction>& directions, const TileType type_to_match)
{
  for (const Direction d : directions)
  {
    TilePtr tile = map->at(CoordUtils::get_new_coordinate(c, d));

    if (tile && tile->get_tile_type() == type_to_match)
    {
      return true;
    }
  }

  return false;
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

// Returns true if the leader has 0 followers, or has > 1 follower and all of
// them are adjacent.
bool MapUtils::are_all_followers_adjacent(const MapPtr& map, const CreaturePtr& leader)
{
  if (leader != nullptr && map != nullptr)
  {
    const CreatureMap& creatures = CreatureUtils::get_followers(leader, map);
    Coordinate l_coord = map->get_location(leader->get_id());

    for (const auto& c_pair : creatures)
    {
      CreaturePtr follower = c_pair.second;

      if (follower != nullptr)
      {
        Coordinate f_coord = map->get_location(follower->get_id());

        if (!CoordUtils::are_coordinates_adjacent(l_coord, f_coord))
        {
          return false;
        }
      }
    }
  }

  return true;
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
      CreaturePtr cr;

      if (tile && tile->has_creature())
      {
        cr = tile->get_creature();
        adjacent_creatures.insert(make_pair(d, cr));
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

void MapUtils::set_up_transitive_exits_as_necessary(MapPtr old_map, MapExitPtr map_exit)
{
  if (old_map != nullptr && old_map->get_map_type() == MapType::MAP_TYPE_OVERWORLD && map_exit != nullptr)
  {
    string exit_map_id = map_exit->get_map_id();
    MapExitPtr default_exit_old_map = old_map->get_map_exit(Direction::DIRECTION_NULL);

    if (default_exit_old_map != nullptr && !exit_map_id.empty())
    {
      MapPtr new_map = Game::instance().get_map_registry_ref().get_map(exit_map_id);

      if (new_map != nullptr)
      {
        MapExitPtr default_exit_new_map = new_map->get_map_exit(Direction::DIRECTION_NULL);

        if (default_exit_new_map == nullptr)
        {
          new_map->set_map_exit(default_exit_old_map);
        }
      }
    }
  }
}

Coordinate MapUtils::calculate_new_coord_for_multimap_movement(const Coordinate& current_coord, TilePtr tile, const Direction exit_direction, MapExitPtr map_exit)
{
  Coordinate c = CoordUtils::end();

  // If we're on a staircase, and trying to go up or down, don't try to calculate
  // the zlevel!
  if (tile != nullptr)
  {
    TileType tt = tile->get_tile_type();

    if (tt == TileType::TILE_TYPE_UP_STAIRCASE || tt == TileType::TILE_TYPE_DOWN_STAIRCASE)
    {
      if (DirectionUtils::is_zlevel(exit_direction))
      {
        return c;
      }
    }
  }
  if (map_exit != nullptr && map_exit->is_using_map_id())
  {
    MapPtr map = Game::instance().get_map_registry_ref().get_map(map_exit->get_map_id());

    if (map != nullptr && map->get_is_multi_map())
    {
      MapExitPtr default_exit = map->get_map_exit();

      // Only calculate the new coords for multi-map if we're exiting
      // and not to the default exit (typically the overworld).
      if ((map_exit  && !default_exit) ||
          (default_exit && map_exit && !(*default_exit == *map_exit)))
      {
        Dimensions dim = map->size();
        c = current_coord;
        
        switch (exit_direction)
        {
          // For up/down, we arrive in the exact same location.
          case Direction::DIRECTION_UP:
          case Direction::DIRECTION_DOWN:
            c = current_coord;
            break;
          // Arriving from the south
          case Direction::DIRECTION_NORTH_WEST:
            // Arriving from north
            if (c.first == 0)
            {
              c.first = dim.get_y() - 1;
            }
            else
            {
              c.first = c.first - 1;
            }

            if (c.second == 0)
            {
              c.second = dim.get_x() - 1;
            }
            else
            {
              c.second = c.second - 1;
            }

            break;
          case Direction::DIRECTION_NORTH:
            c.first = dim.get_y() - 1;
            break;
            // Arriving from the north
          case Direction::DIRECTION_NORTH_EAST:
            // Arriving from north
            if (c.first == 0)
            {
              c.first = dim.get_y() - 1;
            }
            else
            {
              c.first = c.first - 1;
            }

            if (c.second == dim.get_x() - 1)
            {
              c.second = 0;
            }
            else
            {
              c.second = c.second + 1;
            }
            break;
          case Direction::DIRECTION_SOUTH_WEST:
            if (c.first == dim.get_y() - 1)
            {
              c.first = 0;
            }
            else
            {
              c.first = c.first + 1;
            }

            if (c.second == 0)
            {
              c.second = dim.get_x() - 1;
            }
            else
            {
              c.second = c.second - 1;
            }
            break;
          case Direction::DIRECTION_SOUTH:
            c.first = 0;
            break;
          case Direction::DIRECTION_SOUTH_EAST:
            if (c.first == dim.get_y() - 1)
            {
              c.first = 0;
            }
            else
            {
              c.first = c.first + 1;
            }

            if (c.second == dim.get_x() - 1)
            {
              c.second = 0;
            }
            else
            {
              c.second = c.second + 1;
            }
            break;
            // Arriving from the west
          case Direction::DIRECTION_EAST:
            c.second = 0;
            break;
            // Arriving from the east
          case Direction::DIRECTION_WEST:
            c.second = dim.get_x() - 1;
            break;
          case Direction::DIRECTION_NULL:
          default:
            c = CoordUtils::end();
            break;
        }
      }
    }
  }

  return c;
}

// Generate the "correct" cardinal direction based on where we are on the
// map.  As an example, consider if we're on a multi-map like Carcassia, 
// standing at the far-eastern corner
//   ....
//   ...@
//   ....
//
// In this case, east, north-east, and south-east should all move you
// east.  If we're at the bottom of the map:
//
//
// ....
// .@..
// 
// South-west, south, and south-east should move you south.  And so on.
Direction MapUtils::get_exit_direction(const Direction d, const Dimensions& dim, const Coordinate& c)
{
  Direction dir = d;
  int rows = dim.get_y();
  int cols = dim.get_x();

  switch (d)
  {
    case Direction::DIRECTION_UP:
    case Direction::DIRECTION_DOWN:
    case Direction::DIRECTION_NULL:
    case Direction::DIRECTION_NORTH:
    case Direction::DIRECTION_SOUTH:
    case Direction::DIRECTION_EAST:
    case Direction::DIRECTION_WEST:
      return d;
    case Direction::DIRECTION_NORTH_EAST:
      // Row 0, N
      if (c.first == 0 && c.second < cols - 1)
      {
        dir = Direction::DIRECTION_NORTH;
      }
      // last col, E
      else if (c.first > 0 && c.second == cols - 1)
      {
        dir = Direction::DIRECTION_EAST;
      }
      // else, NE
      else
      {
        dir = Direction::DIRECTION_NORTH_EAST;
      }

      break;
    case Direction::DIRECTION_NORTH_WEST:
      // Row 0, N
      if (c.first == 0 && c.second > 0)
      {
        dir = Direction::DIRECTION_NORTH;
      }
      // Col 0, W
      else if (c.first > 0 && c.second == 0)
      {
        dir = Direction::DIRECTION_WEST;
      }
      // else, NW
      else
      {
        dir = Direction::DIRECTION_NORTH_WEST;
      }

      break;
    case Direction::DIRECTION_SOUTH_EAST:
      // last row, S
      if (c.first == rows - 1 && c.second < cols - 1)
      {
        dir = Direction::DIRECTION_SOUTH;
      }
      // last col, E
      else if (c.first < rows - 1 && c.second == cols - 1)
      {
        dir = Direction::DIRECTION_EAST;
      }
      // else SE
      else
      {
        dir = Direction::DIRECTION_SOUTH_EAST;
      }

      break;
    case Direction::DIRECTION_SOUTH_WEST:
      // last row, S
      if (c.first == rows - 1 && c.second > 0)
      {
        dir = Direction::DIRECTION_SOUTH;
      }
      // first col, W
      else if (c.first < rows - 1 && c.second == 0)
      {
        dir = Direction::DIRECTION_WEST;
      }
      // else, SW
      else
      {
        dir = Direction::DIRECTION_SOUTH_WEST;
      }

      break;
  }

  return dir;
}

void MapUtils::potentially_set_permanence_if_leaving_followers_behind(const MapPtr& map, const CreaturePtr& creature)
{
  if (creature != nullptr && map != nullptr)
  {
    if (CreatureUtils::has_followers(creature, map) &&
      !MapUtils::are_all_followers_adjacent(map, creature) &&
      !map->get_permanent() &&
      map->get_map_type() == MapType::MAP_TYPE_OVERWORLD)
    {
      Game& game = Game::instance();
      GameUtils::make_map_permanent(game, creature, map);
    }
  }
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

MapExitOutcome MapUtils::can_exit_map(MapPtr map, CreaturePtr creature, MapExitPtr map_exit, const Direction d, const Coordinate& proposed_new_coord)
{
  if (!map || map->get_map_type() == MapType::MAP_TYPE_WORLD)
  {
    return MapExitOutcome::NO_EXIT;
  }

  MapExitOutcome exit = MapExitOutcome::NO_EXIT;

  // First check: is the map_exit non-null and contain the information
  // necessary for the exit?
  if (map_exit && (map_exit->is_using_map_id() || map_exit->is_using_terrain_type()))
  {
    exit = MapExitOutcome::CAN_EXIT;
  }

  // Second check: if this is for a set map, is the new tile available/open?
  if (map_exit && map_exit->is_using_map_id() && !CoordUtils::is_end(proposed_new_coord))
  {
    MapPtr new_map = Game::instance().get_map_registry_ref().get_map(map_exit->get_map_id());

    if (new_map != nullptr)
    {
      TilePtr old_tile = MapUtils::get_tile_for_creature(map, creature);
      TilePtr tile = new_map->at(proposed_new_coord);

      if (tile == nullptr)
      {
        exit = MapExitOutcome::NO_EXIT;
      }
      else if (!is_tile_available_for_creature(creature, tile))
      {
        exit = MapExitOutcome::EXIT_BLOCKED;
      }

      // The purpose here is to, basically, pretend a roof exists and prevent
      // the player from being able to fly in and out of buildings, bypassing
      // doors, shopkeepers, etc.
      if (exit == MapExitOutcome::CAN_EXIT && 
          creature->has_status(StatusIdentifiers::STATUS_ID_FLYING) && 
          (d == Direction::DIRECTION_UP || d == Direction::DIRECTION_DOWN))
      {
        // Disallow moving from air to interior
        if (old_tile->is_interior())
        {
          exit = MapExitOutcome::EXIT_BLOCKED;
        }
        else
        {
          exit = tile->is_interior() ? MapExitOutcome::EXIT_BLOCKED : MapExitOutcome::CAN_EXIT;
        }
      }

      // Disallow moving from interior to air
      if (exit == MapExitOutcome::CAN_EXIT && 
          old_tile->is_interior() && 
          tile->get_tile_super_type() == TileSuperType::TILE_SUPER_TYPE_AIR && 
          DirectionUtils::is_zlevel(d))
      {
        exit = MapExitOutcome::NO_EXIT;
      }
    }
  }

  return exit;
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
  return convert_coordinate_to_map_key(c.first, c.second);
}

string MapUtils::convert_coordinate_to_map_key(const int row, const int col)
{
  string s = std::to_string(row) + "-" + std::to_string(col);
  return s; 
}

Coordinate MapUtils::convert_map_key_to_coordinate(const string& map_key)
{
  Coordinate coords(0,0);
  
  boost::char_separator<char> sep("-");
  boost::tokenizer<boost::char_separator<char>> tokens(map_key, sep);

  boost::tokenizer<boost::char_separator<char>>:: iterator t_it = tokens.begin();
  
  if (t_it != tokens.end())
  {
    coords.first = std::stoi(*t_it);
    t_it++;
  }
    
  if (t_it != tokens.end())
  {
    coords.second = std::stoi(*t_it);
  }

  return coords;
}

bool MapUtils::is_moving_from_land_type_tile_to_water_type_tile(TilePtr old_tile, TilePtr new_tile)
{
  bool moving_from_land_to_water = false;
  
  // General case: creature has an existing tile, and is moving into a new one.
  if (old_tile && new_tile)
  {
    TileSuperType old_st = old_tile->get_tile_super_type();
    TileSuperType new_st = new_tile->get_tile_super_type();
    
    moving_from_land_to_water = (old_st == TileSuperType::TILE_SUPER_TYPE_GROUND) && (new_st == TileSuperType::TILE_SUPER_TYPE_WATER);    
  }
  // Generation case: creature has no tile, moving to a new one.
  else if (old_tile == nullptr && new_tile != nullptr)
  {
    TileSuperType new_st = new_tile->get_tile_super_type();
    moving_from_land_to_water = (new_st == TileSuperType::TILE_SUPER_TYPE_WATER);
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

Coordinate MapUtils::place_creature(MapPtr map, CreaturePtr creature, const string& player_loc, const Coordinate& linked_location)
{
  Coordinate coords(0,0);

  if (map == nullptr)
  {
    return coords;
  }

  if (CoordUtils::is_end(linked_location))
  {
    bool set_coords = false;

    // First, check the generic "player location" coordinates.
    if (creature->get_is_player())
    {
      string current_player_loc = WorldMapLocationTextKeys::CURRENT_PLAYER_LOCATION;
      if (map->has_location(current_player_loc))
      {
        coords = map->get_location(current_player_loc);
        set_coords = true;
      }
    }

    if (map->has_location(player_loc))
    {
      coords = map->get_location(player_loc);
      set_coords = true;
    }

    if (set_coords == false)
    {
      coords = map->get_starting_location();
    }
  }
  else
  {
    coords = linked_location;
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

    // If there's a blocking feature (which would prevent the creature being
    // here), remove it, too.
    if (placement_tile->has_feature() && placement_tile->get_feature()->get_is_blocking())
    {
      placement_tile->remove_feature();
    }

    MapUtils::add_or_update_location(map, creature, coords);
  }

  return coords;
}

void MapUtils::set_multi_map_entry_details(MapPtr new_map, MapPtr old_map, const Coordinate& new_map_prev_loc)
{
  if (old_map != nullptr &&
      new_map != nullptr &&
      new_map->get_map_type() == MapType::MAP_TYPE_WORLD && 
      old_map->get_is_multi_map() &&
      (old_map->get_world_id() == new_map->get_world_id()))
  {
    TilePtr tile = new_map->at(new_map_prev_loc);

    if (tile != nullptr)
    {
      tile->set_custom_map_id(old_map->get_map_id());
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
    TilesContainer& tc = current_map->get_tiles_ref();

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

vector<TilePtr> MapUtils::get_tiles_supporting_items(MapPtr map)
{
  vector<TilePtr> tiles;

  if (map != nullptr)
  {
    // Be optimistic about how many tiles might be returned.
    tiles.reserve(map->size().get_y() * map->size().get_x());

    TilesContainer& tc = map->get_tiles_ref();
    for (auto& tc_pair : tc)
    {
      TilePtr tile = tc_pair.second;

      if (tile != nullptr && MapUtils::is_tile_available_for_item(tile))
      {
        tiles.push_back(tile);
      }
    }
  }

  return tiles;
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
        hm.set_hostility_to_creature(current_map->get_creature(s_it->second.get_shopkeeper_id()), anger_creature->get_id(), ThreatConstants::ACTIVE_THREAT_RATING);

        IMessageManager& manager = MMF::instance(MessageTransmit::MAP, anger_creature, true);
        manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_ENRAGED_SHOPKEEPER));
        manager.send();

        Game::instance().get_sound()->play(SoundEffectID::ALARM);
      }
    }
  }
}

void MapUtils::calculate_fov_maps_for_all_creatures(MapPtr current_map)
{
  std::map<string, CreaturePtr> map_creatures = current_map->get_creatures();
  LineOfSightCalculator losc;
  TimeOfDayType tod = GameUtils::get_date(Game::instance()).get_time_of_day();

  for (const auto& cr_pair : map_creatures)
  {
    CreaturePtr current_creature = cr_pair.second;

    if (current_creature && current_map)
    {
      int los_len = losc.calculate_los_length(current_creature, current_map->get_map_type(), tod);
      Coordinate creature_coords = current_map->get_location(current_creature->get_id());
      MapPtr view_map = ViewMapTranslator::create_view_map_around_tile(current_creature, current_map, creature_coords, los_len);

      FieldOfViewStrategyPtr fov_strategy = FieldOfViewStrategyFactory::create_field_of_view_strategy(current_creature->get_is_player());
      MapPtr fov_map = fov_strategy->calculate(current_creature, view_map, creature_coords, los_len);
      DecisionStrategy* strategy = current_creature->get_decision_strategy();

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

bool MapUtils::should_link_entry_point(MapType map_type)
{
  if (map_type == MapType::MAP_TYPE_WORLD)
  {
    return true;
  }

  return false;
}

WeatherPtr MapUtils::get_weather(MapPtr map, TilePtr tile)
{
  WeatherPtr weather;

  if (map != nullptr)
  {
    MapType mt = map->get_map_type();

    if (mt == MapType::MAP_TYPE_WORLD && tile != nullptr)
    {
      Weather w = tile->get_weather();
      weather = std::make_unique<Weather>(w);
    }

    if (mt == MapType::MAP_TYPE_OVERWORLD || mt == MapType::MAP_TYPE_AIR)
    {
      Weather w = map->get_weather();
      weather = std::make_unique<Weather>(w);
    }
  }

  return weather;
}

bool MapUtils::is_intersection(MapPtr map, CreaturePtr creature, const Coordinate& c)
{
  bool is_int = false;

  if (map != nullptr)
  {
    // A coordinate is an intersection if:
    // - it's a floor
    // - at least three adjacent directions are floors
    // - at least one one adjacent direction is impassable

    TilePtr t_c = map->at(c);
    int floor_cnt = 0;
    int imp_cnt = 0;

    if (t_c != nullptr)
    {
      if (t_c->has_feature())
      {
        FeaturePtr feat = t_c->get_feature();

        // If we're standing on a door or gate, consider this to be an 
        // intersection and stop.
        if (feat->get_is_entrance())
        {
          return true;
        }
      }

      vector<Direction> adj_cardinal = {Direction::DIRECTION_NORTH, 
                                        Direction::DIRECTION_SOUTH, 
                                        Direction::DIRECTION_EAST, 
                                        Direction::DIRECTION_WEST};

      for (const Direction d : adj_cardinal)
      {
        TilePtr tile_d = map->at(CoordUtils::get_new_coordinate(c, d));

        if (tile_d != nullptr)
        {
          int movement_mult = tile_d->get_movement_multiplier();
          int blocking_or_dangerous = tile_d->get_is_blocking_or_dangerous(creature);

          if (movement_mult > 0 && !blocking_or_dangerous)
          {
            floor_cnt++;
          }
          else
          {
            imp_cnt++;
          }
        }
      }

      vector<Direction> adj_diag = {Direction::DIRECTION_NORTH_EAST,
                                    Direction::DIRECTION_NORTH_WEST,
                                    Direction::DIRECTION_SOUTH_EAST,
                                    Direction::DIRECTION_SOUTH_WEST};

      for (const Direction d : adj_diag)
      {
        TilePtr tile_d = map->at(CoordUtils::get_new_coordinate(c, d));

        if (tile_d != nullptr && (tile_d->get_movement_multiplier() == 0 ||
                                  tile_d->get_is_blocking_or_dangerous(creature)))
        {
          imp_cnt++;
        }
      }
    }

    // Absolutely certain I'm going to question this later, so here's an
    // ASCII example:
    //
    // Not an intersection:
    // ####
    //  @
    // ####
    //
    // Still not:
    // # #
    // # ###
    // # @
    // #####
    //
    // Yes:
    // ## ##
    //   @
    // ## ##
    //
    // Also yes:
    // #####
    //   @
    // ## ##
    // Corner of a room, not an intersection.
    // #####
    // # @
    // #
    // #
    is_int = (floor_cnt > 2 && imp_cnt > 3);
  }
  
  return is_int;
}

// Add any messages after moving to a particular tile:
// - Should a message be displayed about the tile automatically? (staircases, etc)
//       If so, add it.
// - Are there any items on the tile?
//       If so, add the appropriate message.
// Hold off on immediately sending these, as we may be changing maps and don't
// want them erased too early.
void MapUtils::add_tile_related_messages(CreaturePtr creature, TilePtr tile, const bool is_world_map)
{
  add_message_about_tile_if_necessary(creature, tile, is_world_map);
  add_message_about_items_on_tile_if_necessary(creature, tile);
}

// Add a message about the tile if necessary.
bool MapUtils::add_message_about_tile_if_necessary(CreaturePtr creature, TilePtr tile, const bool is_world_map)
{
  bool msg_added = false;

  if (creature && tile && creature->get_is_player())
  {
    IMessageManager& manager = MMF::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());

    if (tile->display_description_on_arrival() || tile->has_extra_description() || has_known_treasure(tile, creature, true) || has_known_shipwreck(nullptr, tile, creature, true))
    {
      TileDescriber td(creature, tile, is_world_map);
      manager.add_new_message(td.describe());
      msg_added = true;
    }
    else if (tile->has_inscription())
    {
      CurrentCreatureAbilities cca;

      if (cca.can_read(creature))
      {
        manager.add_new_message(TextMessages::get_inscription_message(tile->get_inscription_sid(), is_world_map));
      }
      else
      {
        manager.add_new_message(StringTable::get(TileTextKeys::TILE_INSCRIPTION_ILLITERATE));
      }

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
        IMessageManager& manager = MMF::instance();
        manager.add_new_message(item_message);
        msg_added = true;
      }
    }
  }

  return msg_added;
}

void MapUtils::run_movement_scripts(CreaturePtr creature, const string& map_id, const Coordinate& c)
{
  if (creature != nullptr)
  {
    EventScriptsMap& events = creature->get_event_scripts_ref();
    auto e_it = events.find(CreatureEventScripts::CREATURE_EVENT_SCRIPT_ENTER_TILE);

    if (e_it != events.end())
    {
      ScriptDetails sd = e_it->second;

      if (RNG::percent_chance(sd.get_chance()))
      {
        ScriptEngine& se = Game::instance().get_script_engine_ref();
        MoveScript ms;

        ms.execute(se, sd.get_script(), creature, map_id, c);
      }
    }
  }
}

// If the creature has any adjacent followers that should follow them around,
// save these as serialized strings so they can be restored on the next map
// that isn't the world map.
void MapUtils::serialize_and_remove_followers(MapPtr old_map, MapPtr new_map, CreaturePtr creature)
{
  if (creature != nullptr && old_map != nullptr && new_map != nullptr && old_map->get_map_type() != MapType::MAP_TYPE_WORLD)
  {
    MapType new_map_type = new_map->get_map_type();
    CreatureDirectionMap cdm = MapUtils::get_adjacent_creatures(old_map, creature);
    int cnt = 1;

    for (auto cdm_pair : cdm)
    {
      CreaturePtr c = cdm_pair.second;

      if (!MapUtils::should_creature_move_to_new_map_type(c, new_map_type))
      {
        continue;
      }

      if (c != nullptr)
      {
        string leader_id = c->get_leader_id();

        if (!leader_id.empty() && leader_id == creature->get_id())
        {
          // Clear their threat map.
          c->get_decision_strategy()->get_threats_ref().clear();

          // Generate the follower key
          string follower_prop = CreatureUtils::get_follower_property_prefix() + std::to_string(cnt);

          // If the character has a follower with this key, loop until we find 
          // one that's okay.
          while (creature->has_additional_property(follower_prop) && cnt <= Creature::MAX_TRANSFERRABLE_FOLLOWERS)
          {
            follower_prop = CreatureUtils::get_follower_property_prefix() + std::to_string(cnt++);
          }

          // Remove and serialize to a property on the leader.
          MapUtils::remove_creature(old_map, c);

          ostringstream ss;
          c->serialize(ss);

          creature->set_additional_property(follower_prop, ss.str());

          if (cnt == Creature::MAX_TRANSFERRABLE_FOLLOWERS)
          {
            return;
          }

          cnt++;
        }
      }
    }
  }
}

bool MapUtils::should_creature_move_to_new_map_type(CreaturePtr creature, const MapType map_type)
{
  bool should_move = false;

  if (creature != nullptr)
  {
    should_move = true;

    if ((map_type == MapType::MAP_TYPE_UNDERWATER && !creature->can_breathe(BreatheType::BREATHE_TYPE_WATER)) ||
        (map_type == MapType::MAP_TYPE_AIR && !creature->has_status(StatusIdentifiers::STATUS_ID_FLYING)))
    {
      should_move = false;
    }
  }

  return should_move;
}

vector<string> MapUtils::place_followers(MapPtr map, CreaturePtr creature, const Coordinate& c)
{
  vector<string> placed_follower_ids;
  vector<string> placed_followers_keys;

  if (map != nullptr && map->get_map_type() != MapType::MAP_TYPE_WORLD && creature != nullptr)
  {
    vector<pair<string, string>> followers;

    for (int i = 1; i <= Creature::MAX_TRANSFERRABLE_FOLLOWERS; i++)
    {
      string prop = CreatureUtils::get_follower_property_prefix() + std::to_string(i);
      string val = creature->get_additional_property(prop);

      if (!val.empty())
      {
        followers.push_back(make_pair(prop, val));
      }
    }

    if (!followers.empty())
    {
      vector<Coordinate> coords = CoordUtils::get_adjacent_map_coordinates(map->size(), c.first, c.second);
      std::shuffle(coords.begin(), coords.end(), RNG::get_engine());
      CreaturePtr follower = std::make_shared<Creature>();
      pair<string, string> follower_details = followers.back();

      {
        istringstream iss(follower_details.second);
        follower->deserialize(iss);
      }

      while (!followers.empty() && !coords.empty())
      {
        Coordinate cur_coord = coords.back();
        TilePtr adj_tile = map->at(cur_coord);
        coords.pop_back();

        if (adj_tile != nullptr && is_tile_available_for_creature(follower, adj_tile) && !adj_tile->get_dangerous(follower))
        {
          MapUtils::add_or_update_location(map, follower, cur_coord);
          followers.pop_back();
          placed_followers_keys.push_back(follower_details.first);
          placed_follower_ids.push_back(follower->get_id());

          if (!followers.empty())
          {
            follower = std::make_shared<Creature>();
            follower_details = followers.back();
            istringstream iss(follower_details.second);
            follower->deserialize(iss);
          }
        }
      }

      if (!followers.empty())
      {
        // Add a message about feeling abandoned.
        IMessageManager& manager = MMF::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
        manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_ABANDONED));
        manager.send();
      }
    }

    for (auto key : placed_followers_keys)
    {
      creature->remove_additional_property(key);
    }
  }

  return placed_follower_ids;
}

pair<bool, TilePtr> MapUtils::get_melee_attack_target(MapPtr map, CreaturePtr creature, const Direction d)
{
  pair<bool, TilePtr> result = {false, nullptr};

  if (map != nullptr && creature != nullptr)
  {
    MeleeWeaponRangeCalculator mwrc;
    int range = mwrc.get_primary_melee_range(creature);
    string c_id = creature->get_id();
    Coordinate creature_coords = map->get_location(c_id);

    // Find the attacked tile, if one exists
    for (int i = 1; i <= range; i++)
    {
      Coordinate c = CoordUtils::get_new_coordinate(creature_coords, d, i);
      TilePtr t = map->at(c);

      // Checking if the tile is generally blocking instead of specifically
      // for the creature for game balance purposes. Otherwise, a creature
      // could attack two-deep in rock/earth, behind doors, etc.
      if (t != nullptr && !t->get_is_blocking(nullptr))
      {
        if (t->has_creature())
        {
          CreaturePtr tc = t->get_creature();

          // Attack if the tile creature has the attacking creature in its
          // threat map, or if the attacking creature has the tile creature
          // in its own.
          if (tc->get_decision_strategy()->get_threats_ref().has_threat(c_id).first ||
              creature->get_decision_strategy()->get_threats_ref().has_threat(tc->get_id()).first)
          {
            result = {true, t};
          }

          // If there's a creature present, stop checking.  If the creature
          // is hostile, we'll return true plus the tile; if not, we'll
          // return false and nullptr indicating we shouldn't attack.
          break;
        }
      }
      else
      {
        break;
      }
    }
  }

  return result;
}

string MapUtils::get_map_description(MapPtr map)
{
  ostringstream ss;

  if (map != nullptr)
  {
    string sid;
    string name_sid = map->get_name_sid();

    if (!name_sid.empty())
    {
      sid = name_sid;
    }
    else if (map->get_map_type() == MapType::MAP_TYPE_WORLD)
    {
      sid = TextKeys::THE_WORLD_MAP;
    }
    else
    {
      TileType tt = map->get_terrain_type();
      TileGenerator tg;
      TilePtr tile = tg.generate(tt);

      if (tile != nullptr)
      {
        sid = tile->get_tile_description_sid();
      }
    }

    ss << StringTable::get(sid);
  }

  return ss.str();
}

vector<CardinalDirection> MapUtils::get_unblocked_door_dirs(MapPtr map, const Coordinate& st_coord, const Coordinate& end_coord)
{
  vector<CardinalDirection> filtered_door_dirs;

  if (map != nullptr)
  {
    set<Direction> gate_dirs = DirectionUtils::get_all_directions_for_category(DirectionCategory::DIRECTION_CATEGORY_CARDINAL);

    for (const Direction d : gate_dirs)
    {
      Coordinate possible_gate_coord = SettlementGeneratorUtils::get_door_location(st_coord.first, end_coord.first, st_coord.second, end_coord.second, DirectionUtils::to_cardinal_direction(d));
      Coordinate space_in_front = CoordUtils::get_new_coordinate(possible_gate_coord, d);

      TilePtr adj_tile = map->at(space_in_front);

      if (adj_tile != nullptr && !adj_tile->get_is_blocking())
      {
        filtered_door_dirs.push_back(DirectionUtils::to_cardinal_direction(d));
      }
    }
  }

  return filtered_door_dirs;
}

bool MapUtils::add_item(MapPtr map, const vector<Coordinate>& possible_coords, ItemPtr item)
{

  if (map != nullptr && item != nullptr)
  {
    vector<Coordinate> coords = possible_coords;
    std::shuffle(coords.begin(), coords.end(), RNG::get_engine());

    for (const auto& c : coords)
    {
      TilePtr tile = map->at(c);

      if (tile != nullptr && MapUtils::is_tile_available_for_item(tile))
      {
        tile->get_items()->merge_or_add(item, InventoryAdditionType::INVENTORY_ADDITION_FRONT);
        return true;
      }
    }
  }

  return false;
}

vector<Direction> MapUtils::get_coastline_directions(MapPtr map, const Coordinate& c)
{
  vector<Direction> dirs;

  if (map != nullptr)
  {
    vector<Direction> check_dirs = {Direction::DIRECTION_NORTH, Direction::DIRECTION_SOUTH, Direction::DIRECTION_EAST, Direction::DIRECTION_WEST};

    for (const Direction cd : check_dirs)
    {
      Coordinate adj_c = CoordUtils::get_new_coordinate(c, cd);
      TilePtr tile = map->at(adj_c);

      // If we're off the end of the world, assume an endless and unyielding
      // sea...
      if (tile == nullptr)
      {
        dirs.push_back(cd);
      }
      else if (tile->get_tile_type() == TileType::TILE_TYPE_SEA)
      {
        dirs.push_back(cd);
      }
    }
  }

  return dirs;
}

Coordinate MapUtils::get_random_coastline_coordinate(MapPtr map)
{
  Coordinate c = CoordUtils::end();

  if (map != nullptr)
  {
    vector<Direction> dirs = map->get_coastline_directions();

    if (!dirs.empty())  
    {
      std::shuffle(dirs.begin(), dirs.end(), RNG::get_engine());
      Direction d = dirs[0];
      vector<Coordinate> coords = CoordUtils::get_edge_coordinates(map->size(), d);

      if (!coords.empty())
      {
        std::shuffle(coords.begin(), coords.end(), RNG::get_engine());

        for (const Coordinate& ec : coords)
        {
          TilePtr tile = map->at(ec);

          if (tile && tile->get_water_type() != WaterType::WATER_TYPE_UNDEFINED)
          {
            return ec;
          }
        }
      }
    }
  }

  return c;
}

void MapUtils::set_coastline_generator_dirs(SOTW::Generator* generator, const vector<Direction>& dirs)
{
  if (generator != nullptr)
  {
    for (const Direction d : dirs)
    {
      if (d == Direction::DIRECTION_NORTH)
      {
        generator->set_additional_property(MapProperties::MAP_PROPERTIES_COASTLINE_NORTH, std::to_string(true));
      }
      else if (d == Direction::DIRECTION_SOUTH)
      {
        generator->set_additional_property(MapProperties::MAP_PROPERTIES_COASTLINE_SOUTH, std::to_string(true));
      }
      else if (d == Direction::DIRECTION_EAST)
      {
        generator->set_additional_property(MapProperties::MAP_PROPERTIES_COASTLINE_EAST, std::to_string(true));
      }
      else if (d == Direction::DIRECTION_WEST)
      {
        generator->set_additional_property(MapProperties::MAP_PROPERTIES_COASTLINE_WEST, std::to_string(true));
      }
    }
  }
}

void MapUtils::update_creatures(MapPtr map)
{
  if (map != nullptr)
  {
    uint num_creatures = map->get_creatures().size();
    uint num_following = MapUtils::get_num_following_creatures(map);
    uint num_nonfollow = num_creatures - num_following;

    // Check to see if it can be updated with creatures
    if (map != nullptr && map->get_allow_creature_updates() && (num_nonfollow < CreatureGenerationConstants::MIN_CREATURES_FOR_MAP_UPDATE))
    {
      // The map can be updated.
      // Create the appropriate generator and call the update function.
      MapCreatureGenerator mcg;

      std::map<string, string> props = map->get_properties();
      mcg.generate_random_creatures(map, map->get_danger(), props);

      Game& game = Game::instance();
      game.get_sound()->play_music_for_event(MusicEvent::MUSIC_EVENT_RESPAWN, false);

      IMessageManager& manager = MMF::instance();
      manager.add_new_message_with_pause(StringTable::get(TextKeys::RESPAWN_MESSAGE));
      game.get_current_player()->get_decision_strategy()->get_confirmation();

      Game::instance().get_sound()->play_music(map);
    }
  }
}

string MapUtils::get_coordinate_location_sid(const Coordinate& c, const Dimensions& d)
{
  string sid = DirectionLocationTextKeys::DIRECTION_LOCATION_MIDDLE;

  int mid_y = (d.get_y() - 1) / 2;
  int mid_x = (d.get_x() - 1) / 2;
  int y_dist = static_cast<int>(d.get_y() * 0.2);
  int x_dist = static_cast<int>(d.get_x() * 0.2);
  int c_y = c.first;
  int c_x = c.second;

  if (c_y < (mid_y - y_dist))
  {
    if (c_x < (mid_x - x_dist))
    {
      sid = DirectionLocationTextKeys::DIRECTION_LOCATION_NORTH_WEST;
    }
    else if (c_x > mid_x + x_dist)
    {
      sid = DirectionLocationTextKeys::DIRECTION_LOCATION_NORTH_EAST;
    }
    else
    {
      sid = DirectionLocationTextKeys::DIRECTION_LOCATION_NORTH;
    }
  }
  else if (c_y > (mid_y + y_dist))
  {
    if (c_x < (mid_x - x_dist))
    {
      sid = DirectionLocationTextKeys::DIRECTION_LOCATION_SOUTH_WEST;
    }
    else if (c_x > mid_x + x_dist)
    {
      sid = DirectionLocationTextKeys::DIRECTION_LOCATION_SOUTH_EAST;
    }
    else
    {
    sid = DirectionLocationTextKeys::DIRECTION_LOCATION_SOUTH;
    }
  }
  else
  {
  if (c_x < (mid_x - x_dist))
  {
    sid = DirectionLocationTextKeys::DIRECTION_LOCATION_WEST;
  }
  else if (c_x > mid_x + x_dist)
  {
    sid = DirectionLocationTextKeys::DIRECTION_LOCATION_EAST;
  }
  // Middle handled above
  }

  return sid;
}

void MapUtils::enrage_nearby_creatures(MapPtr map, CreaturePtr creature, const string& base_creature_id, const string& corpse_race_id)
{
  if (map != nullptr && creature != nullptr)
  {
    if (!corpse_race_id.empty() || !base_creature_id.empty())
    {
      // Nearby creatures that can see the creature and match the 
      // base_creature_id or whose race matches the race_id are enraged!!
      const CreatureMap& creatures = map->get_creatures_ref();
      HostilityManager hm;
      RaceManager rm;

      for (const auto& cm_pair : creatures)
      {
        if (cm_pair.second && cm_pair.second->get_decision_strategy()->get_fov_map()->has_creature(creature->get_id()))
        {
          CreaturePtr cm_c = cm_pair.second;

          bool understands_corpses = (cm_c->get_intelligence().get_current() > IntelligenceConstants::MIN_INTELLIGENCE_UNDERSTAND_CORPSES);
          Race* race = rm.get_race(cm_c->get_race_id());

          if (cm_c->get_id() != creature->get_id() &&
            understands_corpses &&
            ((cm_c->get_race_id() == corpse_race_id && (race && !race->get_umbrella_race())) ||
              cm_c->get_original_id() == base_creature_id))
          {
            hm.set_hostility_to_creature(cm_c, creature->get_id());

            Coordinate cm_coord = map->get_location(cm_c->get_id());
            TilePtr cm_tile = map->at(cm_coord);

            RageEffect rage;
            rage.effect(cm_c, &Game::instance().get_action_manager_ref(), ItemStatus::ITEM_STATUS_BLESSED, cm_coord, cm_tile, false);
          }
        }
      }

    }
  }
}

void MapUtils::add_preset_village(MapPtr map, const int row, const int col)
{
  if (map != nullptr)
  {
    string key = convert_coordinate_to_map_key({ row, col });
    string preset_villages = map->get_property(MapProperties::MAP_PROPERTIES_PRESET_VILLAGE_COORDINATES);
    vector<string> preset_coords = { key };

    if (!preset_villages.empty())
    {
      preset_coords = String::create_string_vector_from_csv_string(preset_villages);
      preset_coords.push_back(key);
    }

    map->set_property(MapProperties::MAP_PROPERTIES_PRESET_VILLAGE_COORDINATES, String::create_csv_from_string_vector(preset_coords));
  }
}

std::tuple<int, int, std::string, std::string> MapUtils::get_random_village_by_property(MapPtr map, const std::string& prop, const vector<string>& exclude_map_ids)
{
  std::tuple<int, int, std::string, std::string> village = { -1, -1, "", "" };

  if (map != nullptr)
  {
    vector<string> coords = String::create_string_vector_from_csv_string(map->get_property(prop));

    if (!coords.empty())
    {
      std::shuffle(coords.begin(), coords.end(), RNG::get_engine());

      while (!coords.empty())
      {
        string coord_s = coords.back();
        Coordinate c = MapUtils::convert_map_key_to_coordinate(coord_s);

        TilePtr tile = map->at(c);

        if (tile != nullptr)
        {
          // Exclude any tile that links to a map with an ID that we want
          // to exclude. Right now this is done to avoid creating quests
          // to the same village or settlement.
          string map_id = tile->get_custom_map_id();

          if (std::find(exclude_map_ids.begin(), exclude_map_ids.end(), map_id) != exclude_map_ids.end())
          {
            coords.pop_back();
            continue;
          }

          string tile_name = tile->get_additional_property(TileProperties::TILE_PROPERTY_NAME);

          if (tile_name.empty())
          {
            if (!map_id.empty())
            {
              MapPtr assoc_map = Game::instance().get_map_registry_ref().get_map(map_id);

              if (assoc_map != nullptr)
              {
                tile_name = StringTable::get(assoc_map->get_name_sid());
              }
            }
          }

          village = { c.first, c.second, tile_name, MapUtils::get_coordinate_location_sid(c, map->size()) };
          break;
        }
      }
    }
  }

  return village;
}

bool MapUtils::has_known_treasure(TilePtr tile, CreaturePtr creature, const bool mark_skill)
{
  bool has_treasure = false;

  if (tile != nullptr && creature != nullptr && !creature->has_status(StatusIdentifiers::STATUS_ID_FLYING))
  {
    string difficulty = tile->get_additional_property(TileProperties::TILE_PROPERTY_MIN_LORE_REQUIRED);

    if (!difficulty.empty())
    {
      int diff = String::to_int(difficulty);
      SkillType required_skill = tile->get_treasure_skill();

      if (creature->get_skills().get_value(required_skill) >= diff)
      {
        has_treasure = true;
      }
      else
      {
        if (mark_skill)
        {
          int num_marks = RNG::range(4, 8);
          Skills& skills = creature->get_skills();
          SkillType train_skill = MapUtils::get_lore_skill_for_terrain(tile);

          if (train_skill != SkillType::SKILL_UNDEFINED)
          {
            for (int i = 0; i < num_marks; i++)
            {
              skills.mark(train_skill);
            }
          }
        }
      }
    }
  }

  return has_treasure;
}

bool MapUtils::has_known_shipwreck(MapPtr map, TilePtr tile, CreaturePtr creature, const bool mark_skill)
{
  bool has_shipwreck = false;

  if (tile != nullptr && creature != nullptr)
  {
    string difficulty = get_shipwreck_min_lore(map, tile);

    if (!difficulty.empty())
    {
      int diff = String::to_int(difficulty);
      SkillType required_skill = SkillType::SKILL_GENERAL_OCEAN_LORE;

      if (creature->get_skills().get_value(required_skill) >= diff)
      {
        has_shipwreck = true;
      }
      else
      {
        if (mark_skill)
        {
          int num_marks = RNG::range(4, 8);
          Skills& skills = creature->get_skills();

          for (int i = 0; i < num_marks; i++)
          {
            skills.mark(SkillType::SKILL_GENERAL_OCEAN_LORE);
          }
        }
      }
    }
  }

  return has_shipwreck;
}

string MapUtils::get_shipwreck_min_lore(MapPtr map, TilePtr tile)
{
  string min_lore;

  if (tile != nullptr)
  {
    min_lore = tile->get_additional_property(TileProperties::TILE_PROPERTY_UNDERWATER_MIN_LORE_REQUIRED);

    if (min_lore.empty() && map != nullptr && map->get_map_type() == MapType::MAP_TYPE_OVERWORLD)
    {
      min_lore = map->get_property(TileProperties::TILE_PROPERTY_UNDERWATER_MIN_LORE_REQUIRED);
    }
  }

  return min_lore;
}

pair<bool, string> MapUtils::can_change_zlevel(CreaturePtr creature, MapPtr map, TilePtr tile, const Direction d)
{
  bool can_change = false;
  string msg;

  if (creature != nullptr && map != nullptr && tile != nullptr)
  {
    TileType tt = tile->get_tile_type();

    // Can always go up and up staircase, down a down staircase.
    if ((d == Direction::DIRECTION_DOWN && tt == TileType::TILE_TYPE_DOWN_STAIRCASE) ||
        (d == Direction::DIRECTION_UP && tt == TileType::TILE_TYPE_UP_STAIRCASE))
    {
      return make_pair(true, "");
    }
    // Can never go down an up staircase, up a down staircase.
    else if ((d == Direction::DIRECTION_UP && tt == TileType::TILE_TYPE_DOWN_STAIRCASE) ||
             (d == Direction::DIRECTION_DOWN && tt == TileType::TILE_TYPE_UP_STAIRCASE))
    {
      return make_pair(false, MovementTextKeys::ACTION_MOVE_WRONG_STAIRS_DIRECTION);
    }

    MapType map_type = map->get_map_type();
    TileSuperType tst = tile->get_tile_super_type();
    bool can_breathe_water = creature->can_breathe(BreatheType::BREATHE_TYPE_WATER);
    bool can_fly = creature->has_status(StatusIdentifiers::STATUS_ID_FLYING);
    bool can_swim = creature->get_skills().get_value(SkillType::SKILL_GENERAL_SWIMMING) > 0;
    bool map_supports_flying = (map_type == MapType::MAP_TYPE_OVERWORLD || map_type == MapType::MAP_TYPE_AIR);
    bool is_interior = tile->is_interior();

    // Air - only have to check up movement. Can always go down!
    if (map_supports_flying && d == Direction::DIRECTION_UP)
    {
      can_change = can_fly && !map->get_is_open_sky();
    }
    else if (map_type == MapType::MAP_TYPE_AIR && d == Direction::DIRECTION_DOWN)
    {
      can_change = true;
    }
    else
    {
      // Water
      if (tst == TileSuperType::TILE_SUPER_TYPE_WATER)
      {
        if (d == Direction::DIRECTION_DOWN)
        {
          auto season = Game::instance().get_current_world()->get_calendar().get_season()->get_season();

          if (tile->get_is_frozen(season))
          {
            msg = MovementTextKeys::ACTION_MOVE_DIVE_ICE;
          }
          else
          {
            if (map_type != MapType::MAP_TYPE_UNDERWATER &&
              map->get_is_water_shallow() &&
              (can_breathe_water || can_swim))
            {
              if (map->get_allow_diving())
              {
                can_change = true;
              }
              else
              {
                msg = MovementTextKeys::ACTION_MOVE_DIVE_TOO_SHALLOW;
              }
            }
          }
        }
        else if (d == Direction::DIRECTION_UP)
        {
          if (map_type == MapType::MAP_TYPE_UNDERWATER && !is_interior)
          {
            can_change = true;
          }
        }
      }
    }
  }

  return make_pair(can_change, msg);
}

bool MapUtils::get_supports_time_of_day(const MapType map_type)
{
  return (map_type == MapType::MAP_TYPE_OVERWORLD || map_type == MapType::MAP_TYPE_AIR);
}

bool MapUtils::get_supports_weather(const MapType map_type)
{
  return (map_type == MapType::MAP_TYPE_WORLD || map_type == MapType::MAP_TYPE_OVERWORLD || map_type == MapType::MAP_TYPE_AIR);
}

SkillType MapUtils::get_lore_skill_for_terrain(TilePtr tile)
{
  SkillType st = SkillType::SKILL_UNDEFINED;

  if (tile != nullptr)
  {
    if (tile->get_tile_super_type() == TileSuperType::TILE_SUPER_TYPE_WATER)
    {
      st = SkillType::SKILL_GENERAL_OCEAN_LORE;
    }
    else
    {
      TileType tt = tile->get_tile_type();

      switch (tt)
      {
        case TileType::TILE_TYPE_DESERT:
          st = SkillType::SKILL_GENERAL_DESERT_LORE;
          break;
        case TileType::TILE_TYPE_FOREST:
          st = SkillType::SKILL_GENERAL_FOREST_LORE;
          break;
        case TileType::TILE_TYPE_MARSH:
          st = SkillType::SKILL_GENERAL_MARSH_LORE;
          break;
        case TileType::TILE_TYPE_MOUNTAINS:
          st = SkillType::SKILL_GENERAL_MOUNTAIN_LORE;
          break;
        default:
          st = SkillType::SKILL_UNDEFINED;
          break;
      }
    }
  }

  return st;
}

int MapUtils::get_threat_distance_score_for_direction(CreaturePtr creature, const Direction d, MapPtr map, MapPtr view_map)
{
  int score = 0;

  if (creature != nullptr && map != nullptr && view_map != nullptr)
  {
    Coordinate cur_loc = map->get_location(creature->get_id());
    Coordinate new_loc = CoordUtils::get_new_coordinate(cur_loc, d);
    TilePtr new_tile = map->at(new_loc);

    if (new_tile != nullptr)
    {
      if (!MapUtils::is_tile_available_for_creature(creature, new_tile))
      {
        return CANNOT_MOVE_SCORE;
      }

      const auto creatures = view_map->get_creatures();
      for (const auto& c_pair : creatures)
      {
        CreaturePtr cr = c_pair.second;

        if (cr != nullptr && CreatureUtils::either_creature_threatens(creature, cr))
        {
          Coordinate c = map->get_location(cr->get_id());
          score += CoordUtils::chebyshev_distance(c, new_loc);
        }
      }
    }
  }

  return score;
}

string MapUtils::get_drop_sound(TileSuperType tst)
{
  string sound_id;

  switch (tst)
  {
    case TileSuperType::TILE_SUPER_TYPE_AIR:
      sound_id = SoundEffectID::MISS;
      break;
    case TileSuperType::TILE_SUPER_TYPE_WATER:
      sound_id = SoundEffectID::SPLASH;
      break;
    case TileSuperType::TILE_SUPER_TYPE_GROUND:
    case TileSuperType::TILE_SUPER_TYPE_UNDEFINED:
    default:
      break;
  }

  return sound_id;
}

#ifdef UNIT_TESTS
#include "unit_tests/Map_test.cpp"
#include "unit_tests/MapUtils_test.cpp"
#endif
