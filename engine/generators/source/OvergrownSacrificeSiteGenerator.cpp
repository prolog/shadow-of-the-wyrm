#include "FeatureGenerator.hpp"
#include "GeneratorUtils.hpp"
#include "OvergrownSacrificeSiteGenerator.hpp"
#include "RNG.hpp"

using std::string;

OvergrownSacrificeSiteGenerator::OvergrownSacrificeSiteGenerator(const string& new_deity_id, MapPtr new_base_map)
: ChurchGenerator(new_deity_id, new_base_map)
{
}

// Generate the overgrown sacrifice site
MapPtr OvergrownSacrificeSiteGenerator::generate(const Dimensions& dim)
{
  return generate();
}

MapPtr OvergrownSacrificeSiteGenerator::generate()
{
  MapPtr map = MapPtr(new Map(*base_map));

  generate_site(map);
  
  return map;
}

void OvergrownSacrificeSiteGenerator::generate_site(MapPtr map)
{
  generate_additional_brush(map);
  generate_altar(map);
}

// Generate the additional brush throughout the map
void OvergrownSacrificeSiteGenerator::generate_additional_brush(MapPtr map)
{
  Dimensions dim = map->size();
  int rows = dim.get_y();
  int cols = dim.get_x();
  int num_additional_brush = RNG::range(300, 500);
  
  int rand_y, rand_x;
  TileType tile_type;
  TilePtr brush_tile;
  
  for (int i = 0; i < num_additional_brush; i++)
  {
    rand_y = RNG::range(0, rows-1);
    rand_x = RNG::range(0, cols-1);
    
    if (RNG::percent_chance(50))
    {
      tile_type = TILE_TYPE_TREE;
    }
    else
    {
      tile_type = TILE_TYPE_WEEDS;
    }
    
    GeneratorUtils::generate_tile(map, rand_y, rand_x, tile_type);
  }
}

// Centre an altar.
void OvergrownSacrificeSiteGenerator::generate_altar(MapPtr map)
{
  Dimensions dim = map->size();
  
  TilePtr centre_tile = map->at(dim.get_y()/2, dim.get_x()/2);
  FeaturePtr altar = FeatureGenerator::generate_altar(deity_id, ALIGNMENT_RANGE_EVIL);
  centre_tile->set_feature(altar);
}
