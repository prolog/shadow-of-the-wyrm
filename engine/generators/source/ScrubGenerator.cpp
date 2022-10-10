#include "ScrubGenerator.hpp"
#include "Conversion.hpp"
#include "ForestGenerator.hpp"
#include "GameUtils.hpp"
#include "GeneratorUtils.hpp"
#include "MapProperties.hpp"
#include "MapUtils.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

ScrubGenerator::ScrubGenerator(const std::string& new_map_exit_id)
: Generator(new_map_exit_id, TileType::TILE_TYPE_SCRUB)
{
}

MapPtr ScrubGenerator::generate(const Dimensions& dimensions)
{
  MapPtr result_map = std::make_shared<Map>(dimensions);

  int rows = dimensions.get_y();
  int cols = dimensions.get_x();

  ForestCalculator fc;

  int world_map_height = String::to_int(get_additional_property(MapProperties::MAP_PROPERTIES_WORLD_MAP_HEIGHT));
  Coordinate world_location = MapUtils::convert_map_key_to_coordinate(get_additional_property(MapProperties::MAP_PROPERTIES_WORLD_MAP_LOCATION));

  int pct_chance_shield = fc.calculate_pct_chance_shield(world_map_height, world_location);

  for (int row = 0; row < rows; row++)
  {
    for (int col = 0; col < cols; col++)
    {
      TilePtr current_tile = generate_tile(result_map, row, col, pct_chance_shield);
      result_map->insert(row, col, current_tile);
    }
  }

  GeneratorUtils::potentially_generate_coastline(result_map, this);

  if (RNG::percent_chance(15))
  {
    int gr_row = RNG::range(0, rows - 1);
    int gr_col = RNG::range(0, cols - 1);

    TilePtr grave_or_barrow = GeneratorUtils::generate_grave_or_barrow();
    result_map->insert(gr_row, gr_col, grave_or_barrow);
    result_map->set_permanent(true);
  }

  return result_map;
}

// Scrubland is mostly dead grass with a few small bushes thrown in.
TilePtr ScrubGenerator::generate_tile(MapPtr result_map, const int row, const int col, const int pct_chance_shield)
{
  TilePtr generated_tile;

  int rand = RNG::range(1, 100);

  if (rand < 98)
  {
    if (RNG::percent_chance(pct_chance_shield))
    {
      generated_tile = tg.generate(TileType::TILE_TYPE_ROCKY_EARTH);
    }
    else
    {
      generated_tile = tg.generate(TileType::TILE_TYPE_SCRUB);
    }
  }
  else
  {
    generated_tile = tg.generate(TileType::TILE_TYPE_BUSH);
  }

  return generated_tile;
}
