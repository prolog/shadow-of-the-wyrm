#include "CoastlineCalculator.hpp"
#include "SeaGenerator.hpp"
#include "MapProperties.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

SeaGenerator::SeaGenerator(const std::string& new_map_exit_id)
: Generator(new_map_exit_id, TileType::TILE_TYPE_SEA)
{
}

MapPtr SeaGenerator::generate(const Dimensions& dimensions)
{
  MapPtr result_map = std::make_shared<Map>(dimensions);
 
  fill(result_map, TileType::TILE_TYPE_SEA);
  result_map->set_property(MapProperties::MAP_PROPERTIES_SHALLOW_WATER, std::to_string(false));

  CoastlineCalculator cc;
  if (RNG::percent_chance(cc.calc_pct_chance_shoals(adjacent_tile_types)))
  {
    generate_shoals(result_map);
  }

  return result_map;
}

void SeaGenerator::generate_shoals(MapPtr map)
{
  if (map != nullptr)
  {
    Dimensions dim = map->size();
    int num_clusters = RNG::range(3, 8);
    TileGenerator tg;
    TilePtr tile;

    for (int i = 0; i < num_clusters; i++)
    {
      int width = RNG::range(8, 20);
      int height = RNG::range(4, 7);

      int start_y = RNG::range(0, dim.get_y() - height - 1);
      int start_x = RNG::range(0, dim.get_x() - width  - 1);

      for (int y = start_y; y < start_y + height; y++)
      {
        for (int x = start_x; x < start_x + width; x++)
        {
          // Generally: add shoals.
          // But potentially don't add shoals to the beginning and end of
          // rows - this will give it a more ragged/natural look.
          if ((x > start_x && (x < start_x + width - 1)) || RNG::percent_chance(60))
          {
            tile = tg.generate(TileType::TILE_TYPE_SHOALS);
            map->insert(y, x, tile);
          }
        }
      }
    }
  }
}
