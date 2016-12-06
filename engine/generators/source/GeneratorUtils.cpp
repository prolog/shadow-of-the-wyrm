#include "CoordUtils.hpp"
#include "FeatureGenerator.hpp"
#include "GeneratorUtils.hpp"
#include "Game.hpp"
#include "Log.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

using namespace std;

// Hidden away by protected access
GeneratorUtils::GeneratorUtils()
{
}

GeneratorUtils::~GeneratorUtils()
{
}

// Create a circle.  Check to ensure that the radius won't take us off
// the boundaries.
void GeneratorUtils::generate_circle(MapPtr map, const int row_centre, const int col_centre, const int radius, const TileType tile_type)
{
  Dimensions dim = map->size();
  int rows = dim.get_y();
  int cols = dim.get_x();
  bool generate = true;

  vector<Coordinate> circle_coords = CoordUtils::get_circle_coordinates(row_centre, col_centre, radius);

  // Circle in range?
  for (const Coordinate& c : circle_coords)
  {
    if (!(c.first >= 0 && c.first <= rows - 1 && c.second >= 0 && c.second <= cols - 1))
    {
      generate = false;
      break;
    }
  }

  // If the circle's in range, generate it.
  if (generate)
  {
    for (const Coordinate& c : circle_coords)
    {
      generate_tile(map, c.first, c.second, tile_type);
    }
  }
}

bool GeneratorUtils::position_in_range(const int min, const int max, const int actual)
{
  return (actual >= min) && (actual <= max);  
}

// I was using this sort of thing a lot, so I'm moving it here...
void GeneratorUtils::generate_building(const MapPtr map, const int start_row, const int start_col, const int height, const int width)
{
  TileGenerator tg;

  int end_row = start_row + height;
  int end_col = start_col + width;

  TilePtr current_tile;

  for (int row = start_row; row < end_row; row++)
  {
    for (int col = start_col; col < end_col; col++)
    {
      // Generate a wall at the borders, floor otherwise.
      if ((row == start_row) || (row == (end_row - 1))
        ||(col == start_col) || (col == (end_col - 1)))
      {
        current_tile = tg.generate(TileType::TILE_TYPE_ROCK);
      }
      else
      {
        current_tile = tg.generate(TileType::TILE_TYPE_DUNGEON);
      }

      map->insert(row, col, current_tile);
    }
  }  
}

void GeneratorUtils::generate_door(const MapPtr map, const int row, const int col)
{
  TileGenerator tg;

  TilePtr floor   = tg.generate(TileType::TILE_TYPE_DUNGEON);
  FeaturePtr door = FeatureGenerator::generate_door();

  if (floor && map)
  {
    floor->set_feature(door);
    map->insert(row, col, floor);
  }
}

// Generate a tile of a given type at a given location on a given map (that's a given).
void GeneratorUtils::generate_tile(const MapPtr map, const int row, const int col, const TileType tile_type)
{
  TileGenerator tg;
  TilePtr tile = tg.generate(tile_type);
  if (tile && map)
  {
    map->insert(row, col, tile);
  }
}

void GeneratorUtils::generate_fire_pillar(const MapPtr map, const int row, const int col)
{
  FeaturePtr fire_pillar = FeatureGenerator::generate_fire_pillar();
  TilePtr tile = map->at(row, col);
  
  if (tile)
  {
    tile->set_feature(fire_pillar);
  }
}

TilePtr GeneratorUtils::generate_grave_or_barrow()
{
  TilePtr generated_tile;
  TileGenerator tg;

  if (RNG::percent_chance(35))
  {
    generated_tile = tg.generate(TileType::TILE_TYPE_BARROW);
  }
  else
  {
    generated_tile = tg.generate(TileType::TILE_TYPE_GRAVE);
  }

  return generated_tile;
}

void GeneratorUtils::generate_fountain(const MapPtr map, const int row, const int col)
{
  FeaturePtr fountain = FeatureGenerator::generate_fountain();
  TilePtr tile = map->at(row, col);
  
  if (tile)
  {
    tile->set_feature(fountain);
  }
}

// Generate a number of random traps.  Only consider tiles that do not already
// have a feature, and exclude those tiles with movement multipliers of 0.
// Return value is the number of traps generated.
int GeneratorUtils::generate_traps(const MapPtr map, const int num_traps)
{
  int num_gen = 0;

  int trap_y = 0, trap_x = 0;

  Game& game = Game::instance();
  vector<TrapPtr> traps = game.get_trap_info_ref();

  Dimensions dim = map->size();
  int max_y = dim.get_y() - 1;
  int max_x = dim.get_x() - 1;

  for (int i = 0; i < num_traps; i++)
  {
    // Try a few attempts each
    for (int j = 0; j < 2; j++)
    {
      trap_y = RNG::range(0, max_y);
      trap_x = RNG::range(0, max_x);

      TilePtr tile = map->at(trap_y, trap_x);

      if ((tile != nullptr) && (tile->get_movement_multiplier() > 0) && !tile->has_feature())
      {
        GeneratorUtils::generate_trap(map, trap_y, trap_x, traps);
        break;
      }
    }
  }

  return num_gen;
}

// Generate a trap with a given ID and place it at the given coordinates.
void GeneratorUtils::generate_trap(const MapPtr map, const int row, const int col, const vector<TrapPtr>& traps, const string& trap_id, const bool trap_triggered)
{
  if (!traps.empty())
  {
    TrapPtr selected_trap;

    for (TrapPtr trap : traps)
    {
      if (trap && trap->get_id() == trap_id)
      {
        selected_trap = trap;
        break;
      }
    }

    if (selected_trap != nullptr)
    {
      // Make a copy of the one provided.
      TrapPtr new_trap = TrapPtr(selected_trap->clone_and_randomize_uses());
      new_trap->set_triggered(trap_triggered);

      // Set the new copy on to the tile.
      TilePtr tile = map->at(row, col);

      if (tile != nullptr)
      {
        tile->set_feature(new_trap);

        ostringstream ss;
        ss << "GeneratorUtils::generate_trap - trap generated at (" << row << "," << col << ").";
        Log::instance().debug(ss.str());
      }
    }
  }
}

// Generate a random trap from the list and place it at the given coordinates.
void GeneratorUtils::generate_trap(const MapPtr map, const int row, const int col, const vector<TrapPtr>& traps, const bool trap_triggered)
{
  if (!traps.empty())
  {
    size_t trap_size = traps.size();

    uint idx = RNG::range(0, trap_size-1);
    TrapPtr trap = traps.at(idx);

    if (trap != nullptr)
    {
      // Make a copy of the one provided.
      trap = TrapPtr(trap->clone_and_randomize_uses());
      trap->set_triggered(trap_triggered);

      // Set the new copy on to the tile.
      TilePtr tile = map->at(row, col);

      if (tile != nullptr)
      {
        tile->set_feature(trap);

        ostringstream ss;
        ss << "GeneratorUtils::generate_trap - trap generated at (" << row << "," << col << ").";
        Log::instance().debug(ss.str());
      }
    }
  }
}