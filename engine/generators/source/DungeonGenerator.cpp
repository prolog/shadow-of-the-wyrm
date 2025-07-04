#include <algorithm>
#include <cmath>
#include "AllTiles.hpp"
#include "BeerHallSectorFeature.hpp"
#include "Conversion.hpp"
#include "CoordUtils.hpp"
#include "DenseVegetationSectorFeature.hpp"
#include "DungeonGenerator.hpp"
#include "DungeonFeatureTextKeys.hpp"
#include "FeatureGenerator.hpp"
#include "FruitVegetableGardenGenerator.hpp"
#include "Game.hpp"
#include "GeneratorUtils.hpp"
#include "ItemManager.hpp"
#include "LibrarySectorFeature.hpp"
#include "MapExitUtils.hpp"
#include "MapProperties.hpp"
#include "MapUtils.hpp"
#include "RoomFeatures.hpp"
#include "RoomGeneratorFactory.hpp"
#include "ShopGenerator.hpp"
#include "SpringsGenerator.hpp"
#include "TileGenerator.hpp"
#include "TileUtils.hpp"
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
, PCT_CHANCE_DUNGEON_SPRING_FAIRY(100)
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

bool DungeonGenerator::get_allow_ancient_beasts() const
{
  return true;
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
    
    return result_map;
  }

  return null_map;
}

TilePtr DungeonGenerator::generate_tile(MapPtr /*current_map*/, const int /*row*/, const int /*col*/)
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

        if (RNG::percent_chance(20))
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
      floor_tile->copy_entities(cur_tile);

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
    extra_floor_tile->copy_entities(cur_tile);

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
    TilePtr ct = map->at(start_row, start_col);

    if (ct && !ct->has_additional_property(TileProperties::TILE_PROPERTY_NO_OVERWRITE))
    {
      TilePtr floor_tile = tg.generate(TileType::TILE_TYPE_DUNGEON);
      floor_tile->copy_entities(ct);

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

  bool generate_feature = RNG::x_in_y_chance(1, 35);

  if (generate_feature)
  {
    vector<pair<string, string>> feature_choices = {{RoomFeatures::ROOM_FEATURE_ALTAR, DungeonFeatureTextKeys::DUNGEON_FEATURE_ALTAR},
                                                    {RoomFeatures::ROOM_FEATURE_TREASURE_ROOM, DungeonFeatureTextKeys::DUNGEON_FEATURE_TREASURE_ROOM},
                                                    {RoomFeatures::ROOM_FEATURE_ZOO, DungeonFeatureTextKeys::DUNGEON_FEATURE_ZOO},
                                                    {RoomFeatures::ROOM_FEATURE_REST_ROOM, DungeonFeatureTextKeys::DUNGEON_FEATURE_REST_ROOM},
                                                    {RoomFeatures::ROOM_FEATURE_NODE, DungeonFeatureTextKeys::DUNGEON_FEATURE_NODE},
                                                    {RoomFeatures::ROOM_FEATURE_GRAVE, DungeonFeatureTextKeys::DUNGEON_FEATURE_GRAVE},
                                                    {RoomFeatures::ROOM_FEATURE_SPRING, DungeonFeatureTextKeys::DUNGEON_FEATURE_SPRING},
                                                    {RoomFeatures::ROOM_FEATURE_CRAFT_ROOM, DungeonFeatureTextKeys::DUNGEON_FEATURE_CRAFT_ROOM},
                                                    {RoomFeatures::ROOM_FEATURE_MAGIC_TREE, DungeonFeatureTextKeys::DUNGEON_FEATURE_MAGIC_TREE},
                                                    {RoomFeatures::ROOM_FEATURE_SHOP, DungeonFeatureTextKeys::DUNGEON_FEATURE_SHOP},
                                                    {RoomFeatures::ROOM_FEATURE_BEER_HALL, DungeonFeatureTextKeys::DUNGEON_FEATURE_BEER_HALL},
                                                    {RoomFeatures::ROOM_FEATURE_ORCHARD, DungeonFeatureTextKeys::DUNGEON_FEATURE_ORCHARD},
                                                    {RoomFeatures::ROOM_FEATURE_VEGETATION, DungeonFeatureTextKeys::DUNGEON_FEATURE_VEGETATION},
                                                    {RoomFeatures::ROOM_FEATURE_LITTLE_LIBRARY, DungeonFeatureTextKeys::DUNGEON_FEATURE_LITTLE_LIBRARY} };

    shuffle(feature_choices.begin(), feature_choices.end(), RNG::get_engine());

    // JCD TODO: Eventually, I need a mechanism for tracking room features
    // so the player can know in advance...
    while (!feature_choices.empty())
    {
      pair<string, string> feature_pair = feature_choices.back();
      string feature = feature_pair.first;
      string feature_sid = feature_pair.second;
      bool placed_feature = false;

      feature_choices.pop_back();

      if (dungeon_features.find(feature) == dungeon_features.end())
      {
        if (feature == RoomFeatures::ROOM_FEATURE_ALTAR)
        {
          placed_feature = generate_altar(map, start_row, end_row, start_col, end_col);
        }
        else if (feature == RoomFeatures::ROOM_FEATURE_TREASURE_ROOM)
        {
          placed_feature = generate_treasure_room(map, start_row, end_row, start_col, end_col);
        }
        else if (feature == RoomFeatures::ROOM_FEATURE_ZOO)
        {
          placed_feature = generate_zoo(map, start_row, end_row, start_col, end_col);
        }
        else if (feature == RoomFeatures::ROOM_FEATURE_REST_ROOM)
        {
          placed_feature = generate_rest_room(map, start_row, end_row, start_col, end_col);
        }
        else if (feature == RoomFeatures::ROOM_FEATURE_NODE)
        {
          placed_feature = generate_node(map, start_row, end_row, start_col, end_col);
        }
        else if (feature == RoomFeatures::ROOM_FEATURE_GRAVE)
        {
          placed_feature = generate_grave(map, start_row, end_row, start_col, end_col);
        }
        else if (feature == RoomFeatures::ROOM_FEATURE_SPRING)
        {
          placed_feature = generate_spring(map, start_row, end_row, start_col, end_col);
        }
        else if (feature == RoomFeatures::ROOM_FEATURE_CRAFT_ROOM)
        {
          // JCD FIXME: Later, refactor this so that it's in a common place and
          // can be called during village generation.
          placed_feature = generate_craft_room(map, start_row, end_row, start_col, end_col);
        }
        else if (feature == RoomFeatures::ROOM_FEATURE_MAGIC_TREE)
        {
          placed_feature = generate_magic_tree(map, start_row, end_row, start_col, end_col);
        }
        else if (feature == RoomFeatures::ROOM_FEATURE_SHOP)
        {
          placed_feature = generate_shop(map, start_row, end_row, start_col, end_col);
        }
        else if (feature == RoomFeatures::ROOM_FEATURE_BEER_HALL)
        {
          placed_feature = generate_beer_hall(map, start_row, end_row, start_col, end_col);
        }
        else if (feature == RoomFeatures::ROOM_FEATURE_ORCHARD)
        {
          placed_feature = generate_orchard(map, start_row, end_row, start_col, end_col);
        }
        else if (feature == RoomFeatures::ROOM_FEATURE_VEGETATION)
        {
          placed_feature = generate_vegetation(map, start_row, end_row, start_col, end_col);
        }
        else if (feature == RoomFeatures::ROOM_FEATURE_LITTLE_LIBRARY)
        {
          placed_feature = generate_little_library(map, start_row, end_row, start_col, end_col);
        }

        if (placed_feature)
        {
          room_features.push_back(feature);
          dungeon_features.insert(feature);
          feature_entry_text_sids.push_back(feature_sid);
        }

        break;
      }
    }
  }

  return room_features;
}

bool DungeonGenerator::generate_altar(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col)
{
  string deity_id; // Leave empty for now.
  AlignmentRange altar_range = static_cast<AlignmentRange>(RNG::range(static_cast<int>(AlignmentRange::ALIGNMENT_RANGE_EVIL), static_cast<int>(AlignmentRange::ALIGNMENT_RANGE_GOOD)));

  FeaturePtr altar = FeatureGenerator::generate_altar(deity_id, altar_range);
  return centre_feature(map, start_row, end_row, start_col, end_col, altar).first;
}

pair<bool, TilePtr> DungeonGenerator::centre_feature(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col, FeaturePtr feature)
{
  int feature_y = (start_row + end_row - 1) / 2;
  int feature_x = (start_col + end_col - 1) / 2;

  TilePtr tile = map->at(feature_y, feature_x);
  bool placed = false;

  if (tile && !tile->has_feature())
  {
    tile->set_feature(feature);
    placed = true;
  }

  return make_pair(placed, tile);
}

bool DungeonGenerator::generate_rest_room(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col)
{
  FeaturePtr bed = FeatureGenerator::generate_bed();
  return centre_feature(map, start_row, end_row, start_col, end_col, bed).first;
}

bool DungeonGenerator::generate_node(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col)
{
  FeaturePtr stone_marker = FeatureGenerator::generate_stone_marker();
  return centre_feature(map, start_row, end_row, start_col, end_col, stone_marker).first;
}

bool DungeonGenerator::generate_grave(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col)
{
  FeaturePtr sarcophagus = FeatureGenerator::generate_sarcophagus();
  pair<bool, TilePtr> place_details = centre_feature(map, start_row, end_row, start_col, end_col, sarcophagus);
  TilePtr sar_tile = place_details.second;

  if (sar_tile != nullptr)
  {
    DigChances& dc = sar_tile->get_dig_chances_ref();

    // You're going to get something good, and probably, something bad.
    dc.set_pct_chance_item(100);
    dc.set_pct_chance_undead(80);
  }

  return place_details.first;
}

bool DungeonGenerator::generate_spring(MapPtr map, const int start_row, const int end_row, const int start_col, const int /*end_col*/)
{  
  int springs_size = RNG::range(3, 4);
  int y_start = RNG::range(start_row, (end_row - 1 - springs_size));
  map->set_property(MapProperties::MAP_PROPERTIES_WET, std::to_string(true));

  // Some rooms are very small.  Ensure the spring fits.
  if (end_row - start_row - 1 >= springs_size)
  {
    SpringsGenerator::generate_tall(map, y_start, start_col, springs_size, PCT_CHANCE_DUNGEON_SPRING_FAIRY);
    return true;
  }
  
  return false;
}

bool DungeonGenerator::generate_craft_room(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col)
{
  int y_offset = 1;
  int x_offset = 1;

  // Using the generated offsets, get the coordinates offset from each corner
  // of the room.  Shuffle them so that all the craft rooms don't look the
  // same.
  vector<Coordinate> placement_coords = {{start_row, start_col},
                                         {start_row, end_col - x_offset},
                                         {end_row - y_offset, start_col},
                                         {end_row - y_offset, end_col - x_offset}};

  vector<ClassIdentifier> feature_ids = {ClassIdentifier::CLASS_ID_WHEEL_AND_LOOM, 
                                         ClassIdentifier::CLASS_ID_TANNERY, 
                                         ClassIdentifier::CLASS_ID_PULPER,
                                         ClassIdentifier::CLASS_ID_FORGE, 
                                         ClassIdentifier::CLASS_ID_JEWELER_WORKBENCH,
                                         ClassIdentifier::CLASS_ID_KILN};

  std::shuffle(placement_coords.begin(), placement_coords.end(), RNG::get_engine());
  std::shuffle(feature_ids.begin(), feature_ids.end(), RNG::get_engine());

  bool generated = false;

  while (!feature_ids.empty() && !placement_coords.empty())
  {
    Coordinate c = placement_coords.back();
    ClassIdentifier fi = feature_ids.back();

    placement_coords.pop_back();
    feature_ids.pop_back();

    TilePtr tile = map->at(c);

    if (tile && !tile->has_feature())
    {
      FeaturePtr feature = FeatureGenerator::create_feature(fi);

      if (feature)
      {
        tile->set_feature(feature);
        generated = true;
      }
    }
  }

  return generated;
}

bool DungeonGenerator::generate_magic_tree(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col)
{
  bool generated = false;

  if (map != nullptr)
  {
    int num_trees = RNG::range(2, 4);
    int num_generated = 0;

    for (int i = 0; i < 10; i++)
    {
      int y = RNG::range(start_row, end_row);
      int x = RNG::range(start_col, end_col);

      TilePtr tile = map->at(y, x);

      if (tile && tile->get_tile_type() == TileType::TILE_TYPE_DUNGEON)
      {
        // Transform the tile into a magic tree
        TilePtr magic_tree = tg.generate(TileType::TILE_TYPE_MAGICAL_TREE);
        map->insert({y,x}, magic_tree);

        num_generated++;
        generated = true;
      }

      if (num_generated == num_trees)
      {
        break;
      }
    }
  }

  return generated;
}

bool DungeonGenerator::generate_shop(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col)
{
  bool generated = false;

  if (map != nullptr)
  {
    ShopGenerator sg;

    // The coordinates passed in are already interior coordinates, so adjust
    // accordingly or the shop will only take up a subset of the room.
    Building b({start_row-1, start_col-1}, {end_row, end_col}, {start_row, start_col});

    generated = sg.generate_shop(map, b);
  }

  return generated;
}

bool DungeonGenerator::generate_beer_hall(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col)
{
  bool generated = false;

  if (map != nullptr)
  {
    BeerHallSectorFeature bhsf;
    generated = bhsf.generate(map, { start_row, start_col}, { end_row-1, end_col-1});
  }

  return generated;
}

bool DungeonGenerator::generate_orchard(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col)
{
  vector<TileType> vegetation_base_tiles = { TileType::TILE_TYPE_FRUIT_TREE, TileType::TILE_TYPE_FRUIT_TREE, TileType::TILE_TYPE_ROCKY_EARTH };

  DenseVegetationSectorFeature dvsg(vegetation_base_tiles, {}, 0);
  return dvsg.generate(map, { start_row, start_col }, { end_row-1, end_col-1 });
}

bool DungeonGenerator::generate_vegetation(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col)
{
  vector<TileType> vegetation_base_tiles = { TileType::TILE_TYPE_ROCKY_EARTH, TileType::TILE_TYPE_FIELD, TileType::TILE_TYPE_TREE, TileType::TILE_TYPE_BUSH };
  vector<string> item_ids = { ItemIdKeys::ITEM_ID_STONEFLOWER, ItemIdKeys::ITEM_ID_BERRIES, ItemIdKeys::ITEM_ID_WHITE_BASIL, ItemIdKeys::ITEM_ID_VOXFLOWER, ItemIdKeys::ITEM_ID_VERBENA };

  DenseVegetationSectorFeature dvsg(vegetation_base_tiles, item_ids, 20);
  return dvsg.generate(map, { start_row, start_col }, { end_row-1, end_col-1 });
}

bool DungeonGenerator::generate_little_library(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col)
{
  LittleLibrarySectorFeature llsf(false);
  llsf.set_danger_level(std::max<int>(danger_level, llsf.get_default_danger_level()));

  // Leave enough space so that creatures can walk around the structure fully.
  return llsf.generate(map, { start_row, start_col }, { end_row, end_col });
}

bool DungeonGenerator::generate_zoo(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col)
{
  VaultPopulator vp;
  vector<Coordinate> coords = CoordUtils::get_coordinates_in_range(make_pair(start_row, start_col), make_pair(end_row-1, end_col-1));
  vp.populate_vault_creatures(map, TileType::TILE_TYPE_DUNGEON_COMPLEX, coords, danger_level, Rarity::RARITY_COMMON);

  return true;
}

bool DungeonGenerator::generate_treasure_room(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col)
{
  TreasureRoomPopulator trp;
  trp.populate_treasure_room(map, TileType::TILE_TYPE_DUNGEON_COMPLEX, danger_level, start_row, end_row, start_col, end_col);

  return true;
}

bool DungeonGenerator::place_doorway(MapPtr /*map*/, int /*row*/, int /*col*/)
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
  bool place_player_on_down_staircase = get_place_on_down_staircase(get_last_exit_movement_type());

  // Update the map's depth information.
  update_depth_details(map);

  Depth depth = map->size().depth();
  int cnt = 0;

  string up_extra_sid;
  string down_extra_sid;

  std::tie(up_extra_sid, down_extra_sid) = GeneratorUtils::generate_staircase_extra_descs();

  // Generate a down staircase if:
  // - The max_depth property is defined
  // - Our current depth is less than the max depth
  if (depth.has_more_levels(Direction::DIRECTION_DOWN))
  {
    while (!location_found)
    {
      cnt++;

      Room r = connected_rooms.at(RNG::range(0, connected_rooms.size()-1));
      if (r.stairs_allowed() == false || cnt < 20) continue;

      bool placed = false;
      
      while (placed == false)
      {
        y = RNG::range(r.y1 + 1, r.y2 - 2);
        x = RNG::range(r.x1 + 1, r.x2 - 2);

        placed = place_down_staircase(map, y, x, TileType::TILE_TYPE_DUNGEON_COMPLEX, Direction::DIRECTION_DOWN, false, place_player_on_down_staircase, down_extra_sid);
      }

      location_found = true;
    }
  }
  
  location_found = false;
  cnt = 0;

  while (!location_found)
  {
    cnt++;
    Room r = connected_rooms.at(RNG::range(0, connected_rooms.size()-1));
    
    if (r.stairs_allowed() == false || cnt < 20) continue;
        
    bool placed = false;

    while (placed == false)
    {
      y = RNG::range(r.y1 + 1, r.y2 - 2);
      x = RNG::range(r.x1 + 1, r.x2 - 2);

      placed = place_up_staircase(map, y, x, TileType::TILE_TYPE_DUNGEON_COMPLEX, Direction::DIRECTION_UP, get_permanence(), !place_player_on_down_staircase, up_extra_sid);
    }

    location_found = true;
  }
  
  return true;
}

// Every room that is trapped has at least one trap, and has a smaller chance
// of having a second trap.
bool DungeonGenerator::place_traps(MapPtr map, const Room& room)
{
  string danger_level_override = get_additional_property(MapProperties::MAP_PROPERTIES_DANGER_LEVEL_OVERRIDE);
  if (!danger_level_override.empty() && String::to_int(danger_level_override) <= 0)
  {
    return false;
  }

  bool generated_trap = false;
  Game& game = Game::instance();
  vector<TrapPtr> traps = game.get_trap_info_ref();

  int num_traps = 1;

  if (RNG::percent_chance(4))
  {
    fill_room_with_traps(map, room, traps);
  }
  else if (RNG::percent_chance(25))
  {
    num_traps += RNG::range(1, 3);
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

void DungeonGenerator::fill_room_with_traps(MapPtr map, const Room& room, const vector<TrapPtr>& traps)
{
  for (int y = room.y1; y <= room.y2; y++)
  {
    for (int x = room.x1; x <= room.x2; x++)
    {
      TilePtr tile = map->at(y, x);

      if (tile != nullptr && tile->get_movement_multiplier() > 0 && !tile->has_feature())
      {
        GeneratorUtils::generate_trap(map, y, x, traps);
      }
    }
  }

  // Notify the player that there's something bad going on here!
  feature_entry_text_sids.push_back(DungeonFeatureTextKeys::DUNGEON_FEATURE_TRAP_ROOM);
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