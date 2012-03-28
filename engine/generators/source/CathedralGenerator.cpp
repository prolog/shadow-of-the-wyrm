#include "CathedralGenerator.hpp"
#include "FeatureGenerator.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

using std::string;

CathedralGenerator::CathedralGenerator(const string& new_deity_id, MapPtr new_base_map)
: ChurchGenerator(new_deity_id, new_base_map)
{
}

MapPtr CathedralGenerator::generate(const Dimensions& dim)
{
  return generate();
}

// Generate the cathedral
MapPtr CathedralGenerator::generate()
{
  MapPtr map = MapPtr(new Map(*base_map));

  generate_cathedral(map);

  return map;
}

// Generate the cathedral, in the style of Chichester Cathedral.
void CathedralGenerator::generate_cathedral(MapPtr map)
{
  Dimensions dim = map->size();
  int rows = dim.get_y();
  int cols = dim.get_x();
  
  int church_height_min = rows - 8;
  int church_height_max = rows - 4;
  
  int church_width_min = cols - 30;
  int church_width_max = cols - 10; // Again, we always assume 80x20 minimum
  
  int church_height = RNG::range(church_height_min, church_height_max);
  int church_width  = RNG::range(church_width_min, church_width_max);
  
  // Generate a long building, unlike most of other other churches, which are taller in the N-S direction.
  generate_building(map, (rows / 2) - (church_height / 2), (cols / 2) - (church_width / 2), church_height, church_width);

  // Generate rooms/doors inside the cathedral.
  // Generate pews
  // Generate fountains
  // Generate altar
  // Generate doors  
}
