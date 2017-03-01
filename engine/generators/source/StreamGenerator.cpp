#include <iostream>
#include <boost/math/common_factor.hpp>
#include "TileGenerator.hpp"
#include "StreamGenerator.hpp"
#include "Dimensions.hpp"
#include "RNG.hpp"

using namespace std;

//const int StreamGenerator::MIN_STREAM_WIDTH;
//const int StreamGenerator::MAX_STREAM_WIDTH;

void StreamGenerator::generate(MapPtr map)
{
  Dimensions dimensions = map->size();
  generate_stream(map, RNG::range(0, dimensions.get_x()));
}

void StreamGenerator::generate_stream(MapPtr result_map, const int start_col)
{
  TileGenerator tg;
  Dimensions d = result_map->size();

  int max_rows = d.get_y();
  int max_cols = d.get_x();

  int current_row = max_rows;
  int current_col = start_col;

  int modifier = RNG::range(0, 1);

  if (modifier == 0) modifier--;

  while (current_row >= 0 && current_col <= max_cols)
  {
    int rand = RNG::range(1, 100);
    if (rand < 40)
    {
      current_row--;
    }

    result_map->insert(current_row, current_col, tg.generate(TileType::TILE_TYPE_RIVER));

    current_col += modifier;
  }
}
