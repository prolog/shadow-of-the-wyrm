#include "FeatureGenerator.hpp"
#include "GeneratorUtils.hpp"
#include "IslandSacrificeSiteGenerator.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

using namespace std;

const string IslandSacrificeSiteGenerator::ISLAND_SACRIFICE_SITE_GENERATOR_FILTER = "IslandSacrificeSite";

IslandSacrificeSiteGenerator::IslandSacrificeSiteGenerator(const string& new_deity_id, const MapPtr new_base_map)
: ChurchGenerator(new_deity_id, new_base_map, TileType::TILE_TYPE_CHURCH)
{
}

// Generate the patch of land and the moat.
MapPtr IslandSacrificeSiteGenerator::generate(const Dimensions& dim)
{
  return generate();
}

MapPtr IslandSacrificeSiteGenerator::generate()
{
  MapPtr map = std::make_shared<Map>(*base_map);

  generate_site(map);

  return map;
}

// Generate the site by generating the moat, the island, and the
// features on the island.
void IslandSacrificeSiteGenerator::generate_site(MapPtr map)
{
  generate_island(map);
  generate_features(map);
}

void IslandSacrificeSiteGenerator::generate_island(MapPtr map)
{
  TileGenerator tg;

  Dimensions dim = map->size();
  int rows = dim.get_y();
  int cols = dim.get_x();
  
  int centre_row = rows / 2;
  int centre_col = cols / 2;
  
  int moat_size = RNG::range(rows / 4, (rows / 4) + 2);
  
  if (moat_size % 2 != 0) moat_size++;  
  
  int building_size = rows / 4;
  
  // Generate the island
  GeneratorUtils::generate_circle(map, centre_row, centre_col, moat_size, TileType::TILE_TYPE_RIVER);
  
  // Generate the small building
  GeneratorUtils::generate_building(map, centre_row - building_size / 2, centre_col - building_size / 2, building_size, building_size);
  GeneratorUtils::generate_door(map, centre_row - building_size / 2 + building_size - 1, centre_col);
  
  // Dig an entryway to the island.
  for (int i = rows / 2; i < rows; i++)
  {
    TilePtr current_tile = map->at(i, centre_col);
    
    if (current_tile->get_tile_type() == TileType::TILE_TYPE_RIVER)
    {
      TilePtr new_tile = tg.generate(TileType::TILE_TYPE_FIELD);
      map->insert(i, centre_col, new_tile);
    }
  }
}

void IslandSacrificeSiteGenerator::generate_features(MapPtr map)
{
  Dimensions dim = map->size();
  TilePtr centre_tile = map->at(dim.get_y() / 2, dim.get_x() / 2);
  FeaturePtr altar = FeatureGenerator::generate_altar(deity_id, AlignmentRange::ALIGNMENT_RANGE_EVIL);
  centre_tile->set_feature(altar);
}

vector<string> IslandSacrificeSiteGenerator::get_generator_filters() const
{
  vector<string> filters = { ISLAND_SACRIFICE_SITE_GENERATOR_FILTER };
  return filters;
}
