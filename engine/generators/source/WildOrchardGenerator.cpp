#include <vector>
#include "Directions.hpp"
#include "GeneratorUtils.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"
#include "WildOrchardGenerator.hpp"

using namespace std;

WildOrchardGenerator::WildOrchardGenerator(const std::string& new_map_exit_id)
: Generator(new_map_exit_id, TileType::TILE_TYPE_WILD_ORCHARD)
{
}

MapPtr WildOrchardGenerator::generate()
{
  MapPtr result_map;
  Dimensions default_dimensions;
  result_map = generate(default_dimensions);
  return result_map;
}

MapPtr WildOrchardGenerator::generate(const Dimensions& dimensions)
{
  MapPtr result_map = std::make_shared<Map>(dimensions);

  add_map_features(result_map);
  GeneratorUtils::potentially_generate_coastline(result_map, this);

  return result_map;
}

void WildOrchardGenerator::add_map_features(MapPtr map)
{
  TileGenerator tg;

  Dimensions dim = map->size();
  int rows = dim.get_y();
  int cols = dim.get_x();

  for (int row = 0; row < rows; row++)
  {
    for (int col = 0; col < cols; col++)
    {
      TilePtr tile = map->at(row, col);

      if (tile && tile->get_water_type() != WaterType::WATER_TYPE_UNDEFINED)
      {
        continue;
      }

      TilePtr current_tile;

      int shrub = RNG::range(1, 100);

      // Must have an else clause here, otherwise the map will be incomplete.
      if (shrub < 2)
      {
        current_tile = tg.generate(TileType::TILE_TYPE_BUSH);
      }
      else if (shrub < 4)
      {
        current_tile = tg.generate(TileType::TILE_TYPE_WEEDS);
      }
      else if (shrub < 12)
      {
        current_tile = tg.generate(TileType::TILE_TYPE_TREE);        
      }
      else if (shrub < 15)
      {
        current_tile = tg.generate(TileType::TILE_TYPE_FRUIT_TREE);
      }
      // Wild Orchards are much sparser than regular forests, and require
      // a lot of sunlight - therefore, they are mostly fields.
      else
      {
        current_tile = tg.generate(TileType::TILE_TYPE_FIELD);
      }

      map->insert(row, col, current_tile);
    }
  }
}

