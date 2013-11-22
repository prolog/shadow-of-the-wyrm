#include "BresenhamLine.hpp"
#include "CoordUtils.hpp"
#include "MineGenerator.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

using namespace std;

const int MineGenerator::MINE_MIN_ROOM_WIDTH = 4;
const int MineGenerator::MINE_MAX_ROOM_WIDTH = 7;
const int MineGenerator::MINE_MIN_ROOM_HEIGHT = 4;
const int MineGenerator::MINE_MAX_ROOM_HEIGHT = 7;

MineGenerator::MineGenerator(const std::string& map_exit_id)
: Generator(map_exit_id, TILE_TYPE_MINE)
{
}

// Generate the mines.  These should resemble the second level of the
// Earth Cave in Final Fantasy.
MapPtr MineGenerator::generate(const Dimensions& dim)
{
  MapPtr result_map = boost::make_shared<Map>(dim);

  fill(result_map, TILE_TYPE_ROCK);

  generate_main_mining_corridor(result_map);
  generate_rooms(result_map);
  connect_rooms(result_map);

  rooms.clear();
  main_hallway_centre.reset();

  return result_map;
}

MapType MineGenerator::get_map_type() const
{
  return MAP_TYPE_UNDERWORLD;
}

void MineGenerator::generate_rooms(MapPtr map)
{
  Dimensions dim = map->size();
  int rows = dim.get_y();
  int cols = dim.get_x();

  for (int i = 0; i < 25; i++)
  {
    int start_y = RNG::range(1, rows - 1 - MINE_MIN_ROOM_HEIGHT);
    int start_x = RNG::range(1, cols - 1 - MINE_MIN_ROOM_WIDTH);
    int height = RNG::range(MINE_MIN_ROOM_HEIGHT, MINE_MAX_ROOM_HEIGHT);
    int width = RNG::range(MINE_MIN_ROOM_WIDTH, MINE_MAX_ROOM_WIDTH);
  
    if (generate_room(map, start_y, start_x, height, width))
    {
      Room room(i, start_x, start_x+width, start_y, start_y+height);
      room.centre_room = main_hallway_centre;
      rooms.push_back(room);
    }
  }
}

void MineGenerator::connect_rooms(MapPtr map)
{
  Dimensions dim = map->size();
  int centre_col = dim.get_x() / 2;

  // sort the rooms by their distance to the main corridor
  std::sort(rooms.begin(), rooms.end(), Room::compare_rooms);

  if (!rooms.empty())
  {
    // The room nearest to the corridor is always connected to
    // the corridor.
    Room r = rooms.at(0);
    Coordinate rc = r.get_centre();
    BresenhamLine bl;
    vector<Coordinate> tiles_to_dig = bl.get_points_in_line(rc.first, rc.second, RNG::range(rc.first-1, rc.first+1), centre_col); 

    dig_floor(map, tiles_to_dig);

    // The remaining rooms may be connected to either the corridor or the 
    // next-nearest room, based on a declining probability.
    if (rooms.size() > 1)
    {
      for (uint i = 1; i < rooms.size(); i++)
      {
        r = rooms.at(i);
        rc = r.get_centre();

        Coordinate dest_c(rc.first, centre_col);

        // As the distance from the centre corridor increases, so too does the chance that
        // the room will be connected to the nearest room, though there is always a small
        // chance that it will be connected to the main corridor.
        if (RNG::percent_chance(std::min<int>(95, CoordUtils::chebyshev_distance(rc, dest_c))))
        {
          dest_c = rooms.at(i-1).get_centre();
        }

        tiles_to_dig = bl.get_points_in_line(rc.first, rc.second, dest_c.first, dest_c.second);
        dig_floor(map, tiles_to_dig);
      }
    }
  }
  
}

void MineGenerator::dig_floor(MapPtr map, const vector<Coordinate>& tiles_to_dig)
{
  TileGenerator tg;

  for (const Coordinate& c : tiles_to_dig)
  {
    // Dig, unless we hit the staircase.
    TilePtr existing_tile = map->at(c);
    if (existing_tile)
    {
      TileType tt = existing_tile->get_tile_type();
      if (tt == TILE_TYPE_UP_STAIRCASE || tt == TILE_TYPE_DOWN_STAIRCASE) break;
    }

    TilePtr floor_tile = tg.generate(TILE_TYPE_DUNGEON);
    map->insert(c.first, c.second, floor_tile);
  }
}

void MineGenerator::generate_main_mining_corridor(MapPtr map)
{
  TileGenerator tg;

  Dimensions dim = map->size();
  int rows = dim.get_y();
  int cols = dim.get_x();
  int x_offset = cols/10;

  int start_y = RNG::range(1, 2);
  int offset = cols / 10;
  int orig_xpos = RNG::range(cols/2 - x_offset, cols/2 + x_offset);
  int xpos = orig_xpos;
  int end_y = rows - RNG::range(1,2);
  int up_staircase_y = RNG::range(start_y+2, end_y-2);
  main_hallway_centre = boost::make_shared<Room>(-1 /* id doesn't matter */, start_y, end_y, orig_xpos, orig_xpos);

  bool stairway_placed = false;
  int incr_value = 1;

  // JCD FIXME
  bool place_player_on_down_staircase = false;

  for (int y = start_y; y != end_y; y += incr_value)
  {
    for (int x = xpos-1; x <= xpos+1; x++)
    {
      TilePtr tile = tg.generate(TILE_TYPE_DUNGEON);
      map->insert(y, x, tile);
    }

    // 20% chance of the corridor changing direction a little bit.
    if (RNG::percent_chance(20))
    {
      if (xpos == orig_xpos)
      {
        if (RNG::percent_chance(50))
        {
          xpos--;
        }
        else
        {
          xpos++;
        }
      }
      else
      {
        xpos = orig_xpos;
      }
    }

    // The up staircase is always somewhere within the main corridor.
    if (y == up_staircase_y)
    {
      // Place the up staircase, and note that the player 
      // should be placed here.
      place_staircase(map, y, orig_xpos, TILE_TYPE_UP_STAIRCASE, TILE_TYPE_MINE, DIRECTION_UP, get_permanence(), !place_player_on_down_staircase);
  
      TilePtr up_stairs = map->at(y, orig_xpos);
      // This may be empty, in which case, the custom map ID will be empty
      // and terrain will be checked instead, which is the desired behaviour.
      up_stairs->set_custom_map_id(get_additional_property(TileProperties::TILE_PROPERTY_PREVIOUS_MAP_ID));
      up_stairs->set_additional_property(TileProperties::TILE_PROPERTY_ORIGINAL_MAP_ID, get_additional_property(TileProperties::TILE_PROPERTY_ORIGINAL_MAP_ID));

      Depth depth = map->size().depth();
      
      // If we're on level 1, set the custom map ID to be the original map ID.
      if (depth.get_current() <= 1)
      {
        string original_map_id = get_additional_property(TileProperties::TILE_PROPERTY_ORIGINAL_MAP_ID);
        up_stairs->set_custom_map_id(original_map_id);
      }
      stairway_placed = true;
    }
  }

  if (!stairway_placed)
  {
    int x = 1;
  }
}

bool MineGenerator::generate_room(MapPtr map, const int start_y, const int start_x, const int height, const int width)
{
  TileGenerator tg;

  bool room_generated = false;
  Dimensions dim = map->size();
  int max_rows = dim.get_y();
  int max_cols = dim.get_x();

  int endpos_y = start_y + height;
  int endpos_x = start_x + width;

  // The room fits if:
  // - the starting y/x values are greater than zero (we want a layer of rock
  //   surrounding the mines for aesthetic reasons), and the room size doesn't
  //   go over the maximum boundary.
  // - there's nothing but rock in the requested positions.
  bool room_fits = (start_y > 0) && (start_x > 0) && (endpos_y < max_rows - 1) && (endpos_x < max_cols - 1);

  if (room_fits)
  {
    for (int y = start_y; y < endpos_y; y++)
    {
      for (int x = start_x; x < endpos_x; x++)
      {
        TilePtr tile = map->at(y, x);
        if (tile && (tile->get_tile_type() != TILE_TYPE_ROCK))
        {
          room_fits = false;
          break;
        }
      }
    }
  }

  if (room_fits)
  {
    for (int y = start_y; y < endpos_y; y++)
    {
      for (int x = start_x; x < endpos_x; x++)
      {
        TilePtr tile = tg.generate(TILE_TYPE_DUNGEON);
        map->insert(y, x, tile);
      }
    }

    room_generated = true;
  }

  return room_generated;
}

// Place the stairs.  The up stairs should be at the top of the map, and
// the down stairs should be at the bottom.
void MineGenerator::place_staircases(MapPtr map)
{
}

// By default, persist any generated mines.
bool MineGenerator::get_permanence_default() const
{
  return true;
}

