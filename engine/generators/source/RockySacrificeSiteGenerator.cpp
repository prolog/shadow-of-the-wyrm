#include "FeatureGenerator.hpp"
#include "GeneratorUtils.hpp"
#include "RockySacrificeSiteGenerator.hpp"
#include "RNG.hpp"

using std::string;

RockySacrificeSiteGenerator::RockySacrificeSiteGenerator(const string& new_deity_id, MapPtr new_base_map)
: ChurchGenerator(new_deity_id, new_base_map)
{
}

// Generate the site of sacrifice
MapPtr RockySacrificeSiteGenerator::generate(const Dimensions& dim)
{
  return generate();
}

MapPtr RockySacrificeSiteGenerator::generate()
{
  MapPtr map = MapPtr(new Map(*base_map));

  generate_site(map);

  return map;
}

// Generate a ring of cairns with a sacrificial altar in the centre.
// It's like Stonehenge, but for goblins.
void RockySacrificeSiteGenerator::generate_site(MapPtr map)
{
  generate_stones(map);
  generate_features(map);
}

void RockySacrificeSiteGenerator::generate_stones(MapPtr map)
{
  Dimensions dim = map->size();
  int radius = RNG::range(6, 8);
  GeneratorUtils::generate_circle(map, dim.get_y() / 2, dim.get_x() / 2, radius, TILE_TYPE_CAIRN);  
}

void RockySacrificeSiteGenerator::generate_features(MapPtr map)
{
  generate_pillars(map);
  generate_altar(map);
}

void RockySacrificeSiteGenerator::generate_pillars(MapPtr map)
{
  Dimensions dim = map->size();
  int rows = dim.get_y();
  int cols = dim.get_x();
  
  int centre_row = rows / 2;
  int centre_col = cols / 2;
  
  GeneratorUtils::generate_fire_pillar(map, centre_row-1, centre_col-1);
  GeneratorUtils::generate_fire_pillar(map, centre_row-1, centre_col+1);
  GeneratorUtils::generate_fire_pillar(map, centre_row+1, centre_col-1);
  GeneratorUtils::generate_fire_pillar(map, centre_row+1, centre_col+1);
}

void RockySacrificeSiteGenerator::generate_altar(MapPtr map)
{
  Dimensions dim = map->size();
  int rows = dim.get_y();
  int cols = dim.get_x();
  
  FeaturePtr altar = FeatureGenerator::generate_altar(deity_id, ALIGNMENT_RANGE_EVIL);
  TilePtr centre_tile = map->at(rows/2, cols/2);
  
  if (centre_tile)
  {
    centre_tile->set_feature(altar);
  }
}
