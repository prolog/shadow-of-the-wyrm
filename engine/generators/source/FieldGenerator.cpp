#include <iostream>
#include "Conversion.hpp"
#include "Dimensions.hpp"
#include "FieldCalculator.hpp"
#include "FieldGenerator.hpp"
#include "ForestCalculator.hpp"
#include "Game.hpp"
#include "GeneratorUtils.hpp"
#include "MapProperties.hpp"
#include "MapUtils.hpp"
#include "RNG.hpp"
#include "StreamGenerator.hpp"
#include "TileGenerator.hpp"
#include "tiles.hpp"

using namespace std;

FieldGenerator::FieldGenerator(const std::string& new_map_exit_id)
: Generator(new_map_exit_id, TileType::TILE_TYPE_FIELD)
{
}

// Routines for generating a map that should roughly resemble a field.
MapPtr FieldGenerator::generate(const Dimensions& dimensions)
{
  MapPtr result_map = std::make_shared<Map>(dimensions);

  int rows = dimensions.get_y();
  int columns = dimensions.get_x();

  ForestCalculator fc;
  FieldCalculator fi_c;

  int world_map_height = String::to_int(get_additional_property(MapProperties::MAP_PROPERTIES_WORLD_MAP_HEIGHT));
  Coordinate world_location = MapUtils::convert_map_key_to_coordinate(get_additional_property(MapProperties::MAP_PROPERTIES_WORLD_MAP_LOCATION));

  int pct_chance_shield = fc.calculate_pct_chance_shield(world_map_height, world_location);
  bool wild_grain = RNG::percent_chance(fi_c.calc_pct_chance_wild_grains(Game::instance().get_current_player(), world_map_height, world_location));

  for (int row = 0; row < rows; row++)
  {
    for (int col = 0; col < columns; col++)
    {
      TilePtr current_tile = generate_tile(result_map, row, col, pct_chance_shield, wild_grain);
      result_map->insert(row, col, current_tile);
    }
  }

  GeneratorUtils::potentially_generate_coastline(result_map, this);

  if (RNG::percent_chance(40))
  {
    StreamGenerator::generate(result_map);
  }

  if (RNG::percent_chance(25))
  {
    int gr_row = RNG::range(0, rows - 1);
    int gr_col = RNG::range(0, columns - 1);

    TilePtr grave_or_barrow = GeneratorUtils::generate_grave_or_barrow();
    result_map->insert(gr_row, gr_col, grave_or_barrow);
    result_map->set_permanent(true);
  }

  return result_map;
}

TilePtr FieldGenerator::generate_tile(MapPtr /*map*/, const int row, const int /*col*/, const int pct_chance_shield, const bool wild_grain)
{
  TilePtr generated_tile;
  
  // Ensure the first row is reachable.
  if ( row == 0 )
  {
    generated_tile = tg.generate(TileType::TILE_TYPE_FIELD);
  }
  else
  {
    int rand = RNG::range(1, 100);

    if (rand < 96)
    {
      if (RNG::percent_chance(pct_chance_shield))
      {
        if (RNG::percent_chance(90))
        {
          generated_tile = tg.generate(TileType::TILE_TYPE_ROCKY_EARTH);
        }
        else
        {
          generated_tile = tg.generate(TileType::TILE_TYPE_MARSH);
        }
      }
      else
      {
        generated_tile = tg.generate(TileType::TILE_TYPE_FIELD);
      }
    }
    else if (rand < 97)
    {
      generated_tile = tg.generate(TileType::TILE_TYPE_BUSH);
    }
    else if (rand < 98)
    {
      generated_tile = tg.generate(TileType::TILE_TYPE_WEEDS);
    }
    else
    {
      if (wild_grain && RNG::percent_chance(50))
      {
        generated_tile = tg.generate(TileType::TILE_TYPE_WHEAT);
      }
      else
      {
        generated_tile = tg.generate(TileType::TILE_TYPE_TREE);
      }
    }
  }

  return generated_tile;
}
