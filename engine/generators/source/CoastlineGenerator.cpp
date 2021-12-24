#include "CoastlineGenerator.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

const int CoastlineGenerator::PCT_CHANCE_SHIFT_DIR = 33;
const int CoastlineGenerator::MAX_COAST_OFFSET = 3;

CoastlineGenerator::CoastlineGenerator()
: chance_shoals_y(100)
{
}

void CoastlineGenerator::generate(MapPtr map, const bool north, const bool south, const bool east, const bool west)
{
  if (map != nullptr)
  {
    if (north)
    {
      generate_north(map);
    }

    if (south)
    {
      generate_south(map);
    }

    if (east)
    {
      generate_east(map);
    }

    if (west)
    {
      generate_west(map);
    }
  }
}

void CoastlineGenerator::generate_north(MapPtr map)
{
  chance_shoals_y = get_random_chance_shoals();
  int y = RNG::range(0, MAX_COAST_OFFSET);
  Dimensions dim = map->size();
  int cols = dim.get_x();

  for (int x = 0; x < cols; x++)
  {
    fill_sea(map, 0, y, x, x);

    if (RNG::percent_chance(PCT_CHANCE_SHIFT_DIR))
    {
      y = jiggle(y, 0, MAX_COAST_OFFSET);
    }
  }
}

void CoastlineGenerator::generate_south(MapPtr map)
{
  chance_shoals_y = get_random_chance_shoals();
  Dimensions dim = map->size();
  int rows = dim.get_y();
  int cols = dim.get_x();
  int y = RNG::range(rows-MAX_COAST_OFFSET-1, rows-1);

  for (int x = 0; x < cols; x++)
  {
    fill_sea(map, y, rows-1, x, x);

    if (RNG::percent_chance(PCT_CHANCE_SHIFT_DIR))
    {
      y = jiggle(y, rows-MAX_COAST_OFFSET-1, rows-1);
    }
  }
}

void CoastlineGenerator::generate_east(MapPtr map)
{
  chance_shoals_y = get_random_chance_shoals();
  Dimensions dim = map->size();
  int rows = dim.get_y();
  int cols = dim.get_x();
  int x = RNG::range(cols-MAX_COAST_OFFSET-1, cols-1);

  for (int y = 0; y < rows; y++)
  {
    fill_sea(map, y, y, x, cols-1);

    if (RNG::percent_chance(PCT_CHANCE_SHIFT_DIR))
    {
      x = jiggle(x, 0, MAX_COAST_OFFSET);
    }
  }
}

void CoastlineGenerator::generate_west(MapPtr map)
{
  chance_shoals_y = get_random_chance_shoals();
  int x = RNG::range(0, MAX_COAST_OFFSET);
  Dimensions dim = map->size();
  int rows = dim.get_y();

  for (int y = 0; y < rows; y++)
  {
    fill_sea(map, y, y, 0, x);

    if (RNG::percent_chance(PCT_CHANCE_SHIFT_DIR))
    {
      x = jiggle(x, 0, MAX_COAST_OFFSET);
    }
  }
}

int CoastlineGenerator::get_random_chance_shoals() const
{
  if (RNG::percent_chance(40))
  {
    return RNG::range(20, 60);
  }

  return 0;
}

int CoastlineGenerator::jiggle(const int val, const int min_val, const int max_val) const
{
  if (val != min_val && RNG::percent_chance(50))
  {
    return val - 1;
  }
  else if (val != max_val)
  {
    return val + 1;
  }

  return val;
}

void CoastlineGenerator::fill_sea(MapPtr map, const int y_s, const int y_e, const int x_s, const int x_e)
{
  TileGenerator tg;
  TilePtr tile;

  if (map != nullptr)
  {
    for (int y = y_s; y <= y_e; y++)
    {
      for (int x = x_s; x <= x_e; x++)
      {
        TileType tt = TileType::TILE_TYPE_SEA;

        if (RNG::x_in_y_chance(1, chance_shoals_y))
        {
          tt = TileType::TILE_TYPE_SHOALS;
        }

        tile = tg.generate(tt);
        map->insert(y, x, tile);
      }
    }
  }
}