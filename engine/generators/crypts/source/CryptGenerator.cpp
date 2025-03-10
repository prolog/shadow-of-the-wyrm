#include "CoordUtils.hpp"
#include "CryptGenerator.hpp"
#include "CryptLayoutStrategyFactory.hpp"
#include "ItemManager.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

using namespace std;

CryptGenerator::CryptGenerator(const std::string& new_map_exit_id)
: Generator(new_map_exit_id, TileType::TILE_TYPE_CRYPT)
{
}

MapPtr CryptGenerator::generate(const Dimensions& dim)
{
  MapPtr map = std::make_shared<Map>(dim);
  fill(map, TileType::TILE_TYPE_ROCK);
  
  auto loc_details = generate_central_crypt(map);
  generate_crypt_features(loc_details, map);

  return map;
}

TilePtr CryptGenerator::generate_tile(MapPtr /*current_map*/, const int /*row*/, const int /*col*/)
{
  TilePtr grave_tile = tg.generate(TileType::TILE_TYPE_CRYPT);

  return grave_tile;
}

bool CryptGenerator::get_permanence_default() const
{
  return true;
}

// Create the central crypt, a long room with an ascending staircase near 
// the end (by one of the N/S/E/W walls)
tuple<Coordinate, Coordinate, Coordinate> CryptGenerator::generate_central_crypt(MapPtr map)
{
  Dimensions dim = map->size();
  int rows = dim.get_y();
  int cols = dim.get_x();

  int width = RNG::range(cols / 2, cols - (cols / 5));
  int height = RNG::range(rows / 2, rows - (rows / 5));

  // Centre the crypt on the map.
  int startx = (cols / 2) - (width / 2);
  int endx = startx + width;
  int starty = (rows / 2) - (height / 2);
  int endy = starty + height;

  Coordinate top_left = make_pair(starty, startx);
  Coordinate bottom_right = make_pair(endy, endx);

  TilePtr tile;
  vector<Coordinate> coords = CoordUtils::get_coordinates_in_range(top_left, bottom_right);
  for (const auto& coord : coords)
  {
    tile = tg.generate(TileType::TILE_TYPE_DUNGEON);
    map->insert(coord.first, coord.second, tile);
  }

  Coordinate stair_loc = generate_up_staircase(top_left, bottom_right, map);

  // Return the boundaries of the crypt.
  return make_tuple(stair_loc, top_left, bottom_right);
}

// Generate the crypt features:
// - Either:
//     - a central room, or
//     - a long series of triple-doored walls (can't give the player an
//       automatic chokepoint!)
//     - a long series of pillars
void CryptGenerator::generate_crypt_features(const std::tuple<Coordinate, Coordinate, Coordinate>& loc_details, MapPtr map)
{
  // First, check to see if skeletons should be generated along the perimeter.
  bool perimeter_skeletons = RNG::percent_chance(50);

  if (perimeter_skeletons)
  {
    generate_perimeter_skeletons(loc_details, map);
  }

  CryptLayoutType layout_type = static_cast<CryptLayoutType>(RNG::range(static_cast<int>(CryptLayoutType::CRYPT_LAYOUT_PILLARS), static_cast<int>(CryptLayoutType::CRYPT_LAYOUT_LAST)-1));
  ICryptLayoutStrategyPtr layout_strategy = CryptLayoutStrategyFactory::create_layout_strategy(layout_type);

  if (layout_strategy != nullptr)
  {
    layout_strategy->create_layout(map, loc_details);
  }
}

// Generate skeletons around the perimeter of the crypt.
void CryptGenerator::generate_perimeter_skeletons(const std::tuple<Coordinate, Coordinate, Coordinate>& loc_details, MapPtr map)
{
  Coordinate top_left = get<1>(loc_details);
  Coordinate bottom_right = get<2>(loc_details);

  vector<Coordinate> coords = CoordUtils::get_perimeter_coordinates(top_left, bottom_right);
  TilePtr tile;

  for (const auto& coord : coords)
  {
    tile = map->at(coord.first, coord.second);

    ItemPtr bones = ItemManager::create_item("_pile_of_bones");

    if (tile && (tile->get_tile_type() == TileType::TILE_TYPE_DUNGEON) && (bones != nullptr))
    {
      tile->get_items()->add(bones);
    }
  }
}

// Generate the staircase to the surface.
Coordinate CryptGenerator::generate_up_staircase(const Coordinate& top_left, const Coordinate& bottom_right, MapPtr map)
{
  // Generate the up-staircase.
  CardinalDirection d = static_cast<CardinalDirection>(RNG::range(static_cast<int>(CardinalDirection::CARDINAL_DIRECTION_NORTH), static_cast<int>(CardinalDirection::CARDINAL_DIRECTION_WEST)));
  Coordinate stair_coords(0, 0);

  switch (d)
  {
    case CardinalDirection::CARDINAL_DIRECTION_NORTH:
      stair_coords.first = top_left.first;
      stair_coords.second = (top_left.second + bottom_right.second) / 2;
      break;
    case CardinalDirection::CARDINAL_DIRECTION_SOUTH:
      stair_coords.first = bottom_right.first;
      stair_coords.second = (top_left.second + bottom_right.second) / 2;
      break;
    case CardinalDirection::CARDINAL_DIRECTION_EAST:
      stair_coords.first = (top_left.first + bottom_right.first) / 2;
      stair_coords.second = top_left.second;
      break;
    case CardinalDirection::CARDINAL_DIRECTION_WEST:
    default:
      stair_coords.first = (top_left.first + bottom_right.first) / 2;
      stair_coords.second = bottom_right.second;
      break;
  }

  place_staircase(map, stair_coords.first, stair_coords.second, TileType::TILE_TYPE_UP_STAIRCASE, TileType::TILE_TYPE_CRYPT, Direction::DIRECTION_UP, get_permanence(), true);
  return stair_coords;
}

MapType CryptGenerator::get_map_type() const
{
  return MapType::MAP_TYPE_UNDERWORLD;
}