#include <algorithm>
#include <cmath>
#include "Conversion.hpp"
#include "CoordUtils.hpp"
#include "DungeonGenerator.hpp"
#include "DungeonFeatureTextKeys.hpp"
#include "AllTiles.hpp"
#include "FeatureGenerator.hpp"
#include "Game.hpp"
#include "GeneratorUtils.hpp"
#include "MapExitUtils.hpp"
#include "MapProperties.hpp"
#include "MapUtils.hpp"
#include "RoomFeatures.hpp"
#include "RoomGeneratorFactory.hpp"
#include "TileGenerator.hpp"
#include "TreasureRoomPopulator.hpp"
#include "VaultPopulator.hpp"
#include "RNG.hpp"

using namespace std;

// Dungeon Generator
DungeonGenerator::DungeonGenerator(const std::string& new_map_exit_id)
: Generator(new_map_exit_id, TileType::TILE_TYPE_DUNGEON_COMPLEX)
, DEFAULT_MIN_HEIGHT(4)
, DEFAULT_MAX_HEIGHT(7)
, DEFAULT_MIN_WIDTH(5)
, DEFAULT_MAX_WIDTH(9)
, MIN_NUM_ROOMS(8)
, MAX_NUM_ROOMS(10)
{
}

void DungeonGenerator::initialize_and_seed_cheat_vectors(const Dimensions& dimensions)
{
  y1_cheaty_vector.clear();
  y2_cheaty_vector.clear();

  y1_cheaty_vector.push_back(1);
  y2_cheaty_vector.push_back(dimensions.get_y()-1);
  y2_cheaty_vector.push_back(dimensions.get_y()-2);  
}

MapPtr DungeonGenerator::generate(const Dimensions& dimensions)
{
  MapPtr null_map; // needed to compile - should never get hit.
  bool success = false;

  // Initialize the vectors for some guided randomness.
  initialize_and_seed_cheat_vectors(dimensions);
  
  // Try until we get a reasonable map
  while (!success)
  {
    MapPtr result_map = std::make_shared<Map>(dimensions);

    fill(result_map, TileType::TILE_TYPE_ROCK);
    success = generate_dungeon(result_map);
    
    if (!success) continue;
    
    result_map->set_map_type(MapType::MAP_TYPE_UNDERWORLD); 
    return result_map;
  }

  return null_map;
}

TilePtr DungeonGenerator::generate_tile(MapPtr current_map, const int row, const int col)
{
  TilePtr result_tile = tg.generate(TileType::TILE_TYPE_DUNGEON);
  return result_tile;
}

bool DungeonGenerator::generate_dungeon(MapPtr map)
{
  unconnected_rooms.clear();
  connected_rooms.clear();
  
  // This is the "place x random rooms" approach.  Looks OK some of the time.
  // Attempt to place a number of rooms.
  int cur_num_rooms = 0;
  int failure_counter = 0;
  int total_rooms = RNG::range(MIN_NUM_ROOMS, MAX_NUM_ROOMS);
  
  while (cur_num_rooms <= total_rooms)
  {
    int start_y, start_x, height, width;
    
    pair<bool, vector<string>> placement_success = generate_and_place_room(map, start_y, start_x, height, width);
        
    if (placement_success.first)
    {
      cur_num_rooms++;
      Room new_room(placement_success.second, cur_num_rooms, start_x, start_x+width, start_y, start_y+height);
      failure_counter = 0;

      if (cur_num_rooms > 1)
      {
        for (Room& croom : connected_rooms)
        {
          std::shared_ptr<Room> roomp = std::shared_ptr<Room>(new Room(new_room));
          croom.centre_room = roomp;
        }

        std::sort(connected_rooms.begin(), connected_rooms.end(), Room::compare_rooms);
        
        Room next_room = connected_rooms.at(0);
        connect_rooms(map, new_room, next_room);
        connected_rooms.push_back(new_room);

        if (RNG::percent_chance(10))
        {
          place_traps(map, new_room);
        }
      }
      else
      {
        connected_rooms.push_back(new_room);
      }
    }
    else
    {
      failure_counter++;
      if (failure_counter == 200)
      {
        break;
      }
    }
  }

  place_doorways(map);
  place_staircases(map);

  return true;
}

pair<bool, vector<string>> DungeonGenerator::generate_and_place_room(MapPtr map, int& start_y, int& start_x, int& height, int& width)
{
  Dimensions dim = map->size();
  int max_y = dim.get_y();
  int max_x = dim.get_x();

  if (!y1_cheaty_vector.empty())
  {
    start_y = y1_cheaty_vector.back();
    height = RNG::range(DEFAULT_MIN_HEIGHT, DEFAULT_MAX_HEIGHT);
    y1_cheaty_vector.pop_back();
  }
  else if (!y2_cheaty_vector.empty())
  {
    height = RNG::range(DEFAULT_MIN_HEIGHT, DEFAULT_MAX_HEIGHT);
    start_y = y2_cheaty_vector.back() - height;
    y2_cheaty_vector.pop_back();
  }
  else
  {
    start_y = RNG::range(1, max_y-DEFAULT_MAX_HEIGHT-1);
    height = RNG::range(DEFAULT_MIN_HEIGHT, DEFAULT_MAX_HEIGHT);
  }

  start_x = RNG::range(1, max_x-DEFAULT_MAX_WIDTH-1);
  width = RNG::range(DEFAULT_MIN_WIDTH, DEFAULT_MIN_WIDTH);
  
  return place_room(map, start_y, start_x, height, width);  
}

// Dig the hallways.
bool DungeonGenerator::connect_rooms(MapPtr map, const Room& room1, const Room& room2)
{
  int row_inc = 1;
  int col_inc = 1;
  Coordinate r1_c = room1.get_centre();
  Coordinate r2_c = room2.get_centre();
  
  int r1_c_first = r1_c.first;
  int r1_c_second = r1_c.second;
  int r2_c_first = r2_c.first;
  int r2_c_second = r2_c.second;
  
  int dx = r1_c.second - r2_c.second;
  if (dx > 0) col_inc = -1;
  
  int dy = r1_c.first  - r2_c.first;
  if (dy > 0) row_inc = -1;
  
  // Checks to ensure we don't "brush up against" another room.  Need a tile's
  // separation.  Otherwise, it looks like the second room expands in strange
  // ways.
  if (r1_c_second == (room2.x1))
  {
    r1_c_second -= 2;
  }
  
  if (r1_c_second == (room2.x2))
  {
    r1_c_second += 2;      
  }

  if (r1_c_second == (room2.x1-1))
  {
    r1_c_second--;
  }
  
  if (r1_c_second == (room2.x2))
  {
    r1_c_second++;
  }

  
  // Go from room1's centre to room2's centre, drawing lines along the way.  If we
  // replace a rock tile that is contained in either room1 or room2, then add a 
  // door feature.
  int start_row = 0;
  for (start_row = r1_c_first; start_row != r2_c_first; start_row += row_inc)
  {
    TilePtr cur_tile = map->at(start_row, r1_c_second);
    bool no_overwrite = String::to_bool(cur_tile->get_additional_property(TileProperties::TILE_PROPERTY_NO_OVERWRITE));
   
    if (cur_tile && !no_overwrite)
    {
      TilePtr floor_tile = tg.generate(TileType::TILE_TYPE_DUNGEON);
      map->insert(start_row, r1_c_second, floor_tile);
    }

    Coordinate current;
    current.first = start_row;
    current.second = r1_c_second;
    
    // Is this in a room in the unconnected vector?
    for (vector<Room>::iterator v_it = unconnected_rooms.begin(); v_it != unconnected_rooms.end(); v_it++)
    {
      Room current_room = *v_it;
      
      if (current_room.contains(current))
      {
        connected_rooms.push_back(current_room);
        unconnected_rooms.erase(v_it);        
      }
      if (current_room == room2) return true;
    }
  }

  TilePtr cur_tile = map->at(start_row, r1_c_second);
  if (cur_tile && !cur_tile->has_additional_property(TileProperties::TILE_PROPERTY_NO_OVERWRITE))
  {
    TilePtr extra_floor_tile = tg.generate(TileType::TILE_TYPE_DUNGEON);
    map->insert(start_row, r1_c_second, extra_floor_tile);
  }

  if (start_row == (room1.y1 - 1))
  {
    start_row--;
  }
  
  if (start_row == (room1.y2))
  {
    start_row++;
  }
    
  int start_col = 0;
  for (start_col = r1_c_second; start_col != r2_c_second; start_col+=col_inc)
  {
    TilePtr cur_tile = map->at(start_row, start_col);

    if (cur_tile && !cur_tile->has_additional_property(TileProperties::TILE_PROPERTY_NO_OVERWRITE))
    {
      TilePtr floor_tile = tg.generate(TileType::TILE_TYPE_DUNGEON);
      map->insert(start_row, start_col, floor_tile);
    }

    Coordinate current;
    current.first = start_row;
    current.second = start_col;
    
    // check above/below to see if we're making ugly dungeons by making wider corridors.
    TilePtr above = map->at(start_row-1, start_col);
    TilePtr below = map->at(start_row+1, start_col);
    
    Coordinate above_c;
    Coordinate below_c;
    
    above_c.first = start_row-1;
    above_c.second = start_col;
    below_c.first = start_row-1;
    below_c.second = start_row+1;
    
    // Is this in a room in the unconnected vector?
    for (vector<Room>::iterator v_it = unconnected_rooms.begin(); v_it != unconnected_rooms.end(); v_it++)
    {
      Room current_room = *v_it;
      
      if (current_room.contains(current))
      {
        connected_rooms.push_back(current_room);
        unconnected_rooms.erase(v_it);
        break; // coordinates can only be in one room, so this is safe.
      }
      if (current_room == room2) return true;
    }    
  }
  
  return true;
}

bool DungeonGenerator::is_tile_adjacent_to_room_tile(const Dimensions& dim, const int row, const int col)
{
  vector<Coordinate> adjacent_coords = CoordUtils::get_adjacent_map_coordinates(dim, row, col);
  
  for (const Coordinate& c : adjacent_coords)
  {
    if (!tile_exists_outside_of_room(c.first, c.second, true, true))
    {
      return true;
    }
  }
  
  return false;
}

bool DungeonGenerator::tile_exists_outside_of_room(const int row, const int col, const bool check_connected, const bool check_unconnected)
{
  Coordinate current;
  current.first = row;
  current.second = col;
  
  if (check_connected)
  {
    for (vector<Room>::iterator v_it = connected_rooms.begin(); v_it != connected_rooms.end(); v_it++)
    {
      Room r = *v_it;
      
      if (r.contains(current))
      {
        return false;
      }
    }        
  }
  
  if (check_unconnected)
  {
    for (vector<Room>::iterator v_it = unconnected_rooms.begin(); v_it != unconnected_rooms.end(); v_it++)
    {
      Room r = *v_it;
      
      if (r.contains(current))
      {
        return false;
      }
    }        
  }
  
  return true;
}

// Check to see if something can be placed in the specified range, allowing for a little edge room.
bool DungeonGenerator::check_range(MapPtr map, int start_row, int start_col, int size_rows, int size_cols)
{
  int size_y = start_row + size_rows;
  int size_x = start_col + size_cols;
  for (int row = start_row; row < size_y; row++)
  {
    for (int col = start_col; col < size_x; col++)
    {
      TilePtr tile = map->at(row, col);
      if (tile && tile->get_tile_type() != TileType::TILE_TYPE_ROCK)
      {
        return false;
      }
    }
  }
  
  return true;
}

pair<bool, vector<string>> DungeonGenerator::place_room(MapPtr map, int start_row, int start_col, int size_rows, int size_cols)
{
  vector<string> room_features;

  if (!check_range(map, start_row-2, start_col-2, size_rows+3, size_cols+3))
  {
    return make_pair<bool, vector<string>>(false, {});
  }

  int end_row = start_row + size_rows;
  int end_col = start_col + size_cols;

  // We can place the room.
  RoomGeneratorFactory rgf;
  IRoomGeneratorPtr rg;

  // Most of the time, a basic room is created.
  if (RNG::percent_chance(90))
  {
    rg = rgf.create_room_generator(RoomType::ROOM_TYPE_BASIC);
    rg->generate(map, start_row, end_row, start_col, end_col);

    room_features = potentially_generate_room_features(map, start_row, end_row, start_col, end_col);
  }
  // Occasionally, a specially-designed room is created.
  else
  {
    rg = rgf.create_random_special_room_generator();
    rg->generate(map, start_row, end_row, start_col, end_col);
  }
  
  return make_pair(true, room_features);
}

// Do the various checks necessary to decide whether room features should be
// generated.  If yes, go and generate the features, adding them to the
// room.
vector<string> DungeonGenerator::potentially_generate_room_features(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col)
{
  vector<string> room_features;

  bool generate_feature = RNG::x_in_y_chance(1, 60);

  if (generate_feature)
  {
    vector<pair<string, string>> feature_choices = {{RoomFeatures::ROOM_FEATURE_ALTAR, DungeonFeatureTextKeys::DUNGEON_FEATURE_ALTAR},
                                                    {RoomFeatures::ROOM_FEATURE_TREASURE_ROOM, DungeonFeatureTextKeys::DUNGEON_FEATURE_TREASURE_ROOM},
                                                    {RoomFeatures::ROOM_FEATURE_ZOO, DungeonFeatureTextKeys::DUNGEON_FEATURE_ZOO},
                                                    {RoomFeatures::ROOM_FEATURE_REST_ROOM, DungeonFeatureTextKeys::DUNGEON_FEATURE_REST_ROOM},
                                                    {RoomFeatures::ROOM_FEATURE_NODE, DungeonFeatureTextKeys::DUNGEON_FEATURE_NODE}};

    shuffle(feature_choices.begin(), feature_choices.end(), RNG::get_engine());

    // JCD TODO: Eventually, I need a mechanism for tracking room features
    // so the player can know in advance...
    while (!feature_choices.empty())
    {
      pair<string, string> feature_pair = feature_choices.back();
      string feature = feature_pair.first;
      string feature_sid = feature_pair.second;

      feature_choices.pop_back();

      if (dungeon_features.find(feature) == dungeon_features.end())
      {
        if (feature == RoomFeatures::ROOM_FEATURE_ALTAR)
        {
          generate_altar(map, start_row, end_row, start_col, end_col);
        }
        else if (feature == RoomFeatures::ROOM_FEATURE_TREASURE_ROOM)
        {
          generate_treasure_room(map, start_row, end_row, start_col, end_col);
        }
        else if (feature == RoomFeatures::ROOM_FEATURE_ZOO)
        {
          generate_zoo(map, start_row, end_row, start_col, end_col);
        }
        else if (feature == RoomFeatures::ROOM_FEATURE_REST_ROOM)
        {
          generate_rest_room(map, start_row, end_row, start_col, end_col);
        }
        else if (feature == RoomFeatures::ROOM_FEATURE_NODE)
        {
          generate_node(map, start_row, end_row, start_col, end_col);
        }

        room_features.push_back(feature);
        dungeon_features.insert(feature);
        feature_entry_text_sids.push_back(feature_sid);

        break;
      }
    }
  }

  return room_features;
}

void DungeonGenerator::generate_altar(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col)
{
  string deity_id; // Leave empty for now.
  AlignmentRange altar_range = static_cast<AlignmentRange>(RNG::range(static_cast<int>(AlignmentRange::ALIGNMENT_RANGE_EVIL), static_cast<int>(AlignmentRange::ALIGNMENT_RANGE_GOOD)));

  FeaturePtr altar = FeatureGenerator::generate_altar(deity_id, altar_range);
  centre_feature(map, start_row, end_row, start_col, end_col, altar);
}

void DungeonGenerator::centre_feature(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col, FeaturePtr feature)
{
  int feature_y = (start_row + end_row - 1) / 2;
  int feature_x = (start_col + end_col - 1) / 2;

  TilePtr tile = map->at(feature_y, feature_x);

  if (tile && !tile->has_feature())
  {
    tile->set_feature(feature);
  }
}

void DungeonGenerator::generate_rest_room(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col)
{
  FeaturePtr bed = FeatureGenerator::generate_bed();
  centre_feature(map, start_row, end_row, start_col, end_col, bed);
}

void DungeonGenerator::generate_node(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col)
{
  FeaturePtr stone_marker = FeatureGenerator::generate_stone_marker();
  centre_feature(map, start_row, end_row, start_col, end_col, stone_marker);
}

void DungeonGenerator::generate_zoo(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col)
{
  VaultPopulator vp;
  vector<Coordinate> coords = CoordUtils::get_coordinates_in_range(make_pair(start_row, start_col), make_pair(end_row-1, end_col-1));
  vp.populate_vault_creatures(map, TileType::TILE_TYPE_DUNGEON_COMPLEX, coords, danger_level, Rarity::RARITY_COMMON);
}

void DungeonGenerator::generate_treasure_room(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col)
{
  TreasureRoomPopulator trp;
  trp.populate_treasure_room(map, TileType::TILE_TYPE_DUNGEON_COMPLEX, danger_level, start_row, end_row, start_col, end_col);
}

bool DungeonGenerator::place_doorway(MapPtr map, int row, int col)
{
  return false;
}

bool DungeonGenerator::place_doorways(MapPtr map)
{
  Dimensions dim = map->size();
  
  int rows = dim.get_y();
  int cols = dim.get_x();
  
  for (int row = 0; row < rows; row++)
  {
    for (int col = 0; col < cols; col++)
    {
      TilePtr tile = map->at(row, col);
      
      // Doors are always generated.  They are generated shut about half the
      // time, unless adjacent to a special room, in which case they are always
      // generated closed (so that zoos aren't ruined).
      if (tile != nullptr)
      {
        TileType tile_type = tile->get_tile_type();

        if ((tile_type == TileType::TILE_TYPE_DUNGEON || tile->has_additional_property(TileProperties::TILE_PROPERTY_NO_OVERWRITE)) && tile_exists_outside_of_room(row, col, true, true) && is_tile_adjacent_to_room_tile(dim, row, col))
        {
          DoorPtr doorway = FeatureGenerator::generate_door();

          // Generate doors closed by default, or when there's a creature nearby
          if (RNG::percent_chance(50) || MapUtils::adjacent_creature_exists(row, col, map))
          {
            doorway->get_state_ref().set_state(EntranceStateType::ENTRANCE_TYPE_CLOSED);
          }

          tile->set_feature(doorway);
        }
      }        
    }      
  }

  return true;
}

bool DungeonGenerator::place_staircases(MapPtr map)
{
  bool location_found = false;
  int y, x;
  
  Room first_staircase_room;
  string depth_increment = get_additional_property(TileProperties::TILE_PROPERTY_DEPTH_INCREMENT);
  bool place_player_on_down_staircase = (depth_increment.empty());

  // Update the map's depth information.
  string max_depth_property = get_additional_property(UnderworldProperties::UNDERWORLD_STRUCTURE_MAX_DEPTH);
  if (!max_depth_property.empty())
  {
    Depth depth = map->size().depth();
    depth.set_maximum(String::to_int(max_depth_property));
    map->size_ref().set_depth(depth);
  }

  Depth depth = map->size().depth();

  // Generate a down staircase if:
  // - The max_depth property is defined
  // - Our current depth is less than the max depth
  if (depth.get_current() < depth.get_maximum())
  {
    while (!location_found)
    {
      Room r = connected_rooms.at(RNG::range(0, connected_rooms.size()-1));
    
      y = RNG::range(r.y1+1, r.y2-2);
      x = RNG::range(r.x1+1, r.x2-2);
    
      place_staircase(map, y, x, TileType::TILE_TYPE_DOWN_STAIRCASE, TileType::TILE_TYPE_DUNGEON_COMPLEX, Direction::DIRECTION_DOWN, false, place_player_on_down_staircase);

      // Ensure that the original map ID is set on the down staircase.  This will
      // allow it to be set on future maps.  In a fully randomized dungeon, this
      // will keep the value persistent, and allow it to be used on the up staircase
      // on the first dungeon level.
      TilePtr down_tile = map->at(y, x);
      down_tile->set_additional_property(TileProperties::TILE_PROPERTY_ORIGINAL_MAP_ID, get_additional_property(TileProperties::TILE_PROPERTY_ORIGINAL_MAP_ID));
      down_tile->set_additional_property(UnderworldProperties::UNDERWORLD_STRUCTURE_MAX_DEPTH, max_depth_property);

      location_found = true;
    }
  }
  
  location_found = false;
  
  while (!location_found)
  {
    Room r = connected_rooms.at(RNG::range(0, connected_rooms.size()-1));
    
    // Stairs need to be in different rooms, and up staircases shouldn't be
    // in a zoo, or else the player will get pummelled.
    if (r == first_staircase_room || r.has_feature(RoomFeatures::ROOM_FEATURE_ZOO)) continue;
    
    y = RNG::range(r.y1+1, r.y2-2);
    x = RNG::range(r.x1+1, r.x2-2);
    
    place_staircase(map, y, x, TileType::TILE_TYPE_UP_STAIRCASE, TileType::TILE_TYPE_DUNGEON_COMPLEX, Direction::DIRECTION_UP, get_permanence(), !place_player_on_down_staircase);

    location_found = true;
  }
  
  return true;
}

// Every room that is trapped has at least one trap, and has a smaller chance
// of having a second trap.
bool DungeonGenerator::place_traps(MapPtr map, const Room& room)
{
  bool generated_trap = false;
  Game& game = Game::instance();
  vector<TrapPtr> traps = game.get_trap_info_ref();

  int num_traps = 1;

  if (RNG::percent_chance(30))
  {
    num_traps++;
  }

  // Generate however many traps, with about ten attempts for each trap.
  // This should be more than enough, but if for some reason this doesn't
  // generate the trap, then I suppose the adventurer's lucky.
  for (int t = 0; t < num_traps; t++)
  {
    // Try to generate the trap, making sure not to overwrite any existing
    // features.
    for (int i = 0; i < 10; i++)
    {
      int y_val = RNG::range(room.y1, room.y2);
      int x_val = RNG::range(room.x1, room.x2);

      TilePtr tile = map->at(y_val, x_val);

      if (tile != nullptr && tile->get_movement_multiplier() > 0 && !tile->has_feature())
      {
        GeneratorUtils::generate_trap(map, y_val, x_val, traps);

        generated_trap = true;
        break;
      }
    }
  }

  return generated_trap;
}

bool DungeonGenerator::get_permanence_default() const
{
  return true;
}

MapType DungeonGenerator::get_map_type() const
{
  return MapType::MAP_TYPE_UNDERWORLD;
}


bool DungeonGenerator::can_create_initial_items() const
{
  return true;
}