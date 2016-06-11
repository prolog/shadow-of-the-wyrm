#include "HillsGenerator.hpp"
#include "Game.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

using std::string;

HillsGenerator::HillsGenerator(const string& new_map_exit_id)
: Generator(new_map_exit_id, TileType::TILE_TYPE_HILLS)
{
}

MapPtr HillsGenerator::generate(const Dimensions& dim)
{
  Game& game = Game::instance();
  TileGenerator tg;
  MapPtr result_map = std::make_shared<Map>(dim);

  int rows = dim.get_y();
  int cols = dim.get_x();

  TilePtr tile;
  TileType tile_type;
  int rand;

  for (int row = 0; row < rows; row++)
  {
    for (int col = 0; col < cols; col++)
    {
      rand = RNG::range(1, 100);

      if (rand < 2)
      {
        tile_type = TileType::TILE_TYPE_WEEDS;
      }
      else if (rand < 5)
      {
        tile_type = TileType::TILE_TYPE_SCRUB;
      }
      else if (rand < 6)
      {
        tile_type = TileType::TILE_TYPE_CAIRN;
      }
      else if (rand < 7)
      {
        tile_type = TileType::TILE_TYPE_BUSH;
      }
      else
      {
        tile_type = TileType::TILE_TYPE_FIELD;
      }

      tile = tg.generate(tile_type);
      result_map->insert(row, col, tile);
    }
  }

  // The early hill-people made barrows instead of using grave-markers.
  if (RNG::percent_chance(15))
  {
    int gr_row = RNG::range(0, rows - 1);
    int gr_col = RNG::range(0, cols - 1);

    TilePtr barrow = tg.generate(TileType::TILE_TYPE_BARROW);
    result_map->insert(gr_row, gr_col, barrow);
    result_map->set_permanent(true);
  }

  return result_map;
}
