#include <iostream>
#include "TileGenerator.hpp"
#include "FieldGenerator.hpp"
#include "Dimensions.hpp"
#include "tiles.hpp"
#include "RNG.hpp"

using namespace std;

FieldGenerator::FieldGenerator(const std::string& new_map_exit_id)
: Generator(new_map_exit_id, TILE_TYPE_FIELD)
{
}

/*
 **********************************************************************

  Routines for generating a map that should roughly resemble a field.

 **********************************************************************/
MapPtr FieldGenerator::generate(const Dimensions& dimensions)
{
  MapPtr result_map = std::make_shared<Map>(dimensions);

  int rows = dimensions.get_y();
  int columns = dimensions.get_x();

  for (int row = 0; row < rows; row++)
  {
    for (int col = 0; col < columns; col++)
    {
      TilePtr current_tile = generate_tile(result_map, row, col);
      result_map->insert(row, col, current_tile);
    }
  }
  return result_map;
}

TilePtr FieldGenerator::generate_tile(MapPtr map, int row, int col)
{
  TilePtr generated_tile;

  // Ensure the first row is reachable.
  if ( row == 0 )
  {
    generated_tile = tg.generate(TILE_TYPE_FIELD);
  }
  else
  {
    int rand = RNG::range(1, 100);

    if (rand < 96)
    {
      generated_tile = tg.generate(TILE_TYPE_FIELD);
    }
    else if (rand < 97)
    {
      generated_tile = tg.generate(TILE_TYPE_BUSH);
    }
    else if (rand < 98)
    {
      generated_tile = tg.generate(TILE_TYPE_WEEDS);
    }
    else
    {
      generated_tile = tg.generate(TILE_TYPE_TREE);
    }
  }

  return generated_tile;
}
