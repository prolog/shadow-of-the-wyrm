#include <algorithm>
#include <cmath>
#include <boost/make_shared.hpp>
#include <boost/foreach.hpp>
#include "DungeonGenerator.hpp"
#include "AllTiles.hpp"
#include "FeatureGenerator.hpp"
#include "MapUtils.hpp"
#include "TileGenerator.hpp"
#include "RNG.hpp"

using namespace std;
using boost::make_shared;

// JCD FIXME refactor later
Room::Room(int nid, int nx1, int nx2, int ny1, int ny2)
: id(nid), x1(nx1), x2(nx2), y1(ny1), y2(ny2)
{
}

Room::Room()
: id(-1), x1(0), x2(0), y1(0), y2(0)
{
}

bool Room::operator==(const Room& that)
{
  // Ignored shared ptr.
  return ((x1 == that.x1) && (x2 == that.x2) && (y1 == that.y1) && (y2 == that.y2));
}

bool Room::contains(Coordinate c) const
{
  int cy = c.first;
  int cx = c.second;

  return ((cy < y2) && (cy >= y1) && (cx < x2) && (cx >= x1));
}

float tile_distance(Coordinate c1, Coordinate c2);
float tile_distance(Coordinate c1, Coordinate c2)
{
  // Chebyshev distance
  return max(abs(c1.second - c2.second), abs(c1.first - c2.first));
}

bool compare_rooms(const Room& r1, const Room& r2);
bool compare_rooms(const Room& r1, const Room& r2)
{
  Coordinate room1_c = r1.get_centre();
  Coordinate room1_centre_c = r1.centre_room->get_centre();

  Coordinate room2_c = r2.get_centre();
  Coordinate room2_centre_c = r2.centre_room->get_centre();
  
  float r1_td = tile_distance(room1_c, room1_centre_c);
  float r2_td = tile_distance(room2_c, room2_centre_c);
  
  return (r1_td < r2_td);
}

Coordinate Room::get_centre() const
{
  Coordinate c;
  
  c.first  = (y1 + y2) / 2;
  c.second = (x1 + x2) / 2;
  
  return c;
}

// comparator goes here.

DungeonGenerator::DungeonGenerator()
: DEFAULT_MIN_HEIGHT(4)
, DEFAULT_MAX_HEIGHT(7)
, DEFAULT_MIN_WIDTH(4)
, DEFAULT_MAX_WIDTH(8)
, SPACE_BETWEEN_FEATURES(2)
{
  initialize_height_and_width_maps();
}

void DungeonGenerator::initialize_height_and_width_maps()
{
  // Min/Max Heights
  feature_height_map.insert(make_pair(DUNGEON_FEATURE_ROOM, make_pair(DEFAULT_MIN_HEIGHT, DEFAULT_MAX_HEIGHT)));

  // Min/Max Widths
  feature_width_map.insert(make_pair(DUNGEON_FEATURE_ROOM, make_pair(DEFAULT_MIN_WIDTH, DEFAULT_MAX_WIDTH)));
}

MapPtr DungeonGenerator::generate(const Dimensions& dimensions, const std::string& new_map_exit_id)
{
  map_exit_id = new_map_exit_id;
  MapPtr null_map; // needed to compile - should never get hit.
  bool success = false;

  // Initialize the vectors for some guided randomness.
  y1_cheaty_vector.clear();
  y2_cheaty_vector.clear();

  y1_cheaty_vector.push_back(1);
  y2_cheaty_vector.push_back(dimensions.get_y()-1);
  y2_cheaty_vector.push_back(dimensions.get_y()-2);
  
  // Try until we get a resonable map
  while (!success)
  {
    MapPtr result_map = MapPtr(new Map(dimensions));

    fill(result_map, TILE_TYPE_ROCK);
      
    success = generate_dungeon(result_map);
    
    if (!success) continue;
    
    result_map->set_map_type(MAP_TYPE_UNDERWORLD);    

    return result_map;
  }

  return null_map;
}

TilePtr DungeonGenerator::generate_tile(MapPtr current_map, const int row, const int col)
{
  TilePtr result_tile = TileGenerator::generate(TILE_TYPE_DUNGEON);
  return result_tile;
}

bool DungeonGenerator::generate_dungeon(MapPtr map)
{
  unconnected_rooms.clear();
  connected_rooms.clear();
  
  Dimensions dim = map->size();
  int max_y = dim.get_y();
  int max_x = dim.get_x();

  // This is the "place x random rooms" approach.  Looks OK some of the time.
  // Attempt to place a number of rooms.
  int cur_num_rooms = 0;
  int failure_counter = 0;
  int max_rooms = RNG::range(8, 10);
  while (cur_num_rooms <= max_rooms)
  {
    // Attempt to add a room
    DungeonFeature feature_type = get_random_feature();

    int start_y;
    int start_x;
    
    int height;
    int width;  
    
    if (!y1_cheaty_vector.empty())
    {
      start_y = y1_cheaty_vector.back();
      height = RNG::range(get_min_feature_height(feature_type), get_max_feature_height(feature_type));
      y1_cheaty_vector.pop_back();
    }
    else if (!y2_cheaty_vector.empty())
    {
      height = RNG::range(get_min_feature_height(feature_type), get_max_feature_height(feature_type));
      start_y = y2_cheaty_vector.back() - height;
      y2_cheaty_vector.pop_back();
    }
    else
    {
      start_y = RNG::range(1, max_y-get_max_feature_height(feature_type)-1);;
      height = RNG::range(get_min_feature_height(feature_type), get_max_feature_height(feature_type));
    }

    start_x = RNG::range(1, max_x-get_max_feature_width(feature_type)-1);;
    width = RNG::range(get_min_feature_width(feature_type), get_max_feature_width(feature_type));;
    
    bool placement_success = place_feature(map, feature_type, start_y, start_x, height, width);
    
    if (placement_success)
    {
      cur_num_rooms++;
      Room new_room(cur_num_rooms, start_x, start_x+width, start_y, start_y+height);
      failure_counter = 0;

      if (cur_num_rooms > 1)
      {
        BOOST_FOREACH(Room& croom, connected_rooms)
        {
          boost::shared_ptr<Room> roomp = boost::shared_ptr<Room>(new Room(new_room));
          croom.centre_room = roomp;
        }

        std::sort(connected_rooms.begin(), connected_rooms.end(), compare_rooms);
        
        Room next_room = connected_rooms.at(0);
        connect_rooms(map, new_room, next_room);
        connected_rooms.push_back(new_room);
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

  // Make additional connections!
  //add_additional_corridors(map);

  place_doorways(map);
  place_staircases(map);

  return true;
}

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
/*  if (r1_c_second == room2.x1 - 1) r1_c_second--;
  if (r1_c_second == room2.x2 + 1) r1_c_second++;
  if (r1_c_first == room2.x1 - 1) r1_c_second--;
  if (r1_c_first == room2.x2 + 1) r1_c_second++; */
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
    TilePtr floor_tile = TileGenerator::generate(TILE_TYPE_DUNGEON);

    map->insert(start_row, r1_c_second, floor_tile);
    
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

  // JCD FIXME: Fix the "brush up against" problem here.
  cout << "Room1: x1: " << room1.x1 << ", x2: " << room1.x2 << ", y1: " << room1.y1 << ", y2: " << room1.y2 << endl;
  cout << "Room2: x1: " << room2.x1 << ", x2: " << room2.x2 << ", y1: " << room2.y1 << ", y2: " << room2.y2 << endl;
  cout << "Current coordinates are: (" << start_row << ", " << r1_c_second << ")" << endl;
  TilePtr extra_floor_tile = TileGenerator::generate(TILE_TYPE_DUNGEON);  
  if (start_row == (room1.y1-1))
  {
    map->insert(start_row, r1_c_second, extra_floor_tile);
    start_row--;
  }
  
  if (start_row == (room1.y2))
  {
    map->insert(start_row, r1_c_second, extra_floor_tile);
    start_row++;
  }
    
  int start_col = 0;
  for (start_col = r1_c_second; start_col != r2_c_second; start_col+=col_inc)
  {
    TilePtr floor_tile = TileGenerator::generate(TILE_TYPE_DUNGEON);

    map->insert(start_row, start_col, floor_tile);

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
  vector<Coordinate> adjacent_coords = MapUtils::get_adjacent_map_coordinates(dim, row, col);
  
  BOOST_FOREACH(Coordinate c, adjacent_coords)
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

bool DungeonGenerator::place_feature(MapPtr map, const DungeonFeature feature, int start_row, int start_col, int size_rows, int size_cols)
{
  bool placement_success = false;
  
  switch(feature)
  {
    // Update this later.
    case DUNGEON_FEATURE_ROOM:
    case DUNGEON_FEATURE_CIRCULAR_WITH_PIT:
    case DUNGEON_FEATURE_CAVE_IN:
    case DUNGEON_FEATURE_VAULT:
    case DUNGEON_FEATURE_OUT_OF_DEPTH_VAULT:
    case DUNGEON_FEATURE_BEEHIVE:
    case DUNGEON_FEATURE_ZOO:
      placement_success = place_room(map, start_row, start_col, size_rows, size_cols);
      break;
    default:
      break;
  }
  
  return placement_success;
}

// JCD FIXME: Rooms are generated too close in proximity to each other.  Fix this up.  They need to be at least three
// "rocks" apart.
bool DungeonGenerator::check_range(MapPtr map, int start_row, int start_col, int size_rows, int size_cols)
{
  int size_y = start_row + size_rows;
  int size_x = start_col + size_cols;
  for (int row = start_row; row < size_y; row++)
  {
    for (int col = start_col; col < size_x; col++)
    {
      TilePtr tile = map->at(row, col);
      if (tile && tile->get_tile_type() != TILE_TYPE_ROCK)
      {
        return false;
      }
    }
  }
  
  return true;
}

bool DungeonGenerator::place_room(MapPtr map, int start_row, int start_col, int size_rows, int size_cols)
{
  if (!check_range(map, start_row-2, start_col-2, size_rows+3, size_cols+3))
  {
    return false;
  }
  
  // We can place the room:  
  int size_y = start_row + size_rows;
  int size_x = start_col + size_cols;
  for (int y = start_row; y < size_y; y++)
  {
    for (int x = start_col; x < size_x; x++)
    {
      TilePtr tile = TileGenerator::generate(TILE_TYPE_DUNGEON);
      map->insert(y, x, tile);
    }
  }
  
  return true;
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
      
      if (tile && (tile->get_tile_type() == TILE_TYPE_DUNGEON) && tile_exists_outside_of_room(row, col, true, true) && is_tile_adjacent_to_room_tile(dim, row, col))
      {
        FeaturePtr doorway = FeatureGenerator::generate_door();
        tile->set_feature(doorway);
      }
    }      
  }

  return true;
}

bool DungeonGenerator::add_additional_corridors(MapPtr map)
{
  int num_addl_random_connections = RNG::range(10, 15);
  cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << endl;
  for (int i = 0; i < num_addl_random_connections; i++)
  {
    Room room = connected_rooms.at(RNG::range(0, connected_rooms.size()-1));
    
    BOOST_FOREACH(Room& r, connected_rooms)
    {
      boost::shared_ptr<Room> roomp = boost::shared_ptr<Room>(new Room(room));
      r.centre_room = roomp;      
    }
    
    std::sort(connected_rooms.begin(), connected_rooms.end(), compare_rooms);
    Room room2 = connected_rooms.at(0); // 0 would be the same room.
    
    connect_rooms(map, room2, room);
  }
  
  return true;
}

bool DungeonGenerator::place_staircases(MapPtr map)
{
  Dimensions dim = map->size();
  bool location_found = false;
  int y, x;
  
  while (!location_found)
  {
    y = RNG::range(0, dim.get_y()-1);
    x = RNG::range(0, dim.get_x()-1);
    
    TilePtr tile = map->at(y, x);
    
    if (tile && (tile->get_tile_type() == TILE_TYPE_DUNGEON) && !tile_exists_outside_of_room(y, x, true, true))
    {      
      TilePtr down_staircase = TileGenerator::generate(TILE_TYPE_DOWN_STAIRCASE);
      map->insert(y, x, down_staircase);
      location_found = true;
    }
  }
  
  location_found = false;
  
  while (!location_found)
  {
    y = RNG::range(0, dim.get_y()-1);
    x = RNG::range(0, dim.get_x()-1);

    TilePtr tile = map->at(y, x);
    
    if (tile && (tile->get_tile_type() == TILE_TYPE_DUNGEON) && !tile_exists_outside_of_room(y, x, true, true))
    {
      Coordinate c;
      c.first = y;
      c.second = x;
      
      TilePtr up_staircase = TileGenerator::generate(TILE_TYPE_UP_STAIRCASE);

      if (!map_exit_id.empty())
      {
        // JCD FIXME: Make this a MapUtils function
        TileExitMap& tile_exit_map = up_staircase->get_tile_exit_map_ref();

        MapExitPtr new_map_exit = make_shared<MapExit>();
        new_map_exit->set_map_id(map_exit_id);
        
        tile_exit_map.insert(make_pair(DIRECTION_UP, new_map_exit));
      }
      
      map->insert(y, x, up_staircase); 
      map->add_or_update_location(WorldMapLocationTextKeys::CURRENT_PLAYER_LOCATION, c);
      location_found = true;
    }    
  }
  
  return true;
}

// Eventually, this needs to be updated to get features based on danger level, as well.
DungeonFeature DungeonGenerator::get_random_feature()
{
//  DungeonFeature feature = static_cast<DungeonFeature>(RNG::range(DUNGEON_FEATURE_MIN, DUNGEON_FEATURE_MAX));
  return DUNGEON_FEATURE_ROOM;
}

int DungeonGenerator::get_min_feature_height(const DungeonFeature feature)
{
  DungeonFeatureSizeMapIterator_const h_it = feature_height_map.find(feature);

  if (h_it != feature_height_map.end())
  {
    return h_it->second.first;
  }

  return DEFAULT_MIN_HEIGHT;
}

int DungeonGenerator::get_max_feature_height(const DungeonFeature feature)
{
  DungeonFeatureSizeMapIterator_const h_it = feature_height_map.find(feature);

  if (h_it != feature_height_map.end())
  {
    return h_it->second.second;
  }

  return DEFAULT_MAX_HEIGHT;
}

int DungeonGenerator::get_min_feature_width(const DungeonFeature feature)
{
  DungeonFeatureSizeMapIterator_const w_it = feature_width_map.find(feature);

  if (w_it != feature_width_map.end())
  {
    return w_it->second.first;
  }

  return DEFAULT_MIN_WIDTH;
}

int DungeonGenerator::get_max_feature_width(const DungeonFeature feature)
{
  DungeonFeatureSizeMapIterator_const w_it = feature_width_map.find(feature);

  if (w_it != feature_width_map.end())
  {
    return w_it->second.second;
  }

  return DEFAULT_MAX_WIDTH;
}
