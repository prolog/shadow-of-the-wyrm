#include <boost/make_shared.hpp>
#include "FeatureGenerator.hpp"
#include "GardenGeneratorFactory.hpp"
#include "GeneratorUtils.hpp"
#include "GrandTempleGenerator.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

using std::string;
using boost::make_shared;

GrandTempleGenerator::GrandTempleGenerator(const string& new_deity_id, MapPtr new_base_map)
: ChurchGenerator(new_deity_id, new_base_map, TILE_TYPE_TEMPLE),
temple_width(0), temple_height(0), temple_start_row(0), temple_start_col(0), centre_row(0), centre_col(0)
{
}

MapPtr GrandTempleGenerator::generate(const Dimensions& dim)
{
  return generate();
}

MapPtr GrandTempleGenerator::generate()
{
  MapPtr map = make_shared<Map>(*base_map);
  
  generate_temple(map);
  
  return map;
}

// Generate the grand temple
void GrandTempleGenerator::generate_temple(MapPtr map)
{
  initialize_dimensions(map);
  GeneratorUtils::generate_building(map, temple_start_row, temple_start_col, temple_height, temple_width);
  generate_temple_gardens(map);
  generate_temple_features(map);
}

// Initialize the temple's dimensions
void GrandTempleGenerator::initialize_dimensions(MapPtr map)
{
  Dimensions dim = map->size();
  int rows = dim.get_y();
  int cols = dim.get_x();
  
  temple_height = RNG::range(rows * 0.7, rows * 0.85);
  temple_width  = RNG::range(cols * 0.7, cols * 0.90);
  
  // Adjusting the start row/column to an odd height/width
  // makes for easier centring of fountains.
  temple_start_row = (rows / 2) - (temple_height / 2);
  if (temple_start_row % 2 == 0) temple_start_row--;
  
  temple_start_col = (cols / 2) - (temple_width  / 2);
  if (temple_start_col % 2 == 0) temple_start_col--;

  centre_row = (temple_start_row + temple_start_row + temple_height) / 2;
  centre_col = (temple_start_col + temple_start_col + temple_width)  / 2;
}

// Generate a garden in each corner of the temple
void GrandTempleGenerator::generate_temple_gardens(MapPtr map)
{
  int garden_height = (temple_height / 2) - 3;
  int garden_width = (temple_width / 2) - 3;
  
  // Top left
  int start_row = temple_start_row + 1;
  int start_col = temple_start_col + 1;
  GardenGeneratorPtr generator = GardenGeneratorFactory::create_uniform_random_garden_generator(map, start_row, start_col, garden_height, garden_width);
  generator->generate();
  
  // Top right
  start_col = temple_start_col + temple_width - garden_width - 2;
  generator = GardenGeneratorFactory::create_uniform_random_garden_generator(map, start_row, start_col, garden_height, garden_width);
  generator->generate();
  
  // Bottom left
  start_row = temple_start_row + temple_height - garden_height - 2;
  start_col = temple_start_col + 1;
  generator = GardenGeneratorFactory::create_uniform_random_garden_generator(map, start_row, start_col, garden_height, garden_width);
  generator->generate();
  
  // Bottom right
  start_col = temple_start_col + temple_width - garden_width - 2;
  generator = GardenGeneratorFactory::create_uniform_random_garden_generator(map, start_row, start_col, garden_height, garden_width);
  generator->generate();
}

// Generate the temple's features
void GrandTempleGenerator::generate_temple_features(MapPtr map)
{
  generate_fountains(map);
  generate_altar(map);
  generate_temple_doors(map);
}

// Generate fountains halfway down each hallway to the altar.
void GrandTempleGenerator::generate_fountains(MapPtr map)
{
  // North hallway, S, E, W
  GeneratorUtils::generate_fountain(map, (temple_start_row + centre_row) / 2, centre_col);
  GeneratorUtils::generate_fountain(map, (centre_row + temple_start_row + temple_height) / 2, centre_col);
  GeneratorUtils::generate_fountain(map, centre_row, (temple_start_col + centre_col) / 2);
  GeneratorUtils::generate_fountain(map, centre_row, (centre_col + temple_start_col + temple_width) / 2);
}

// Generate the temple's altar, in the centre of all the gardens
void GrandTempleGenerator::generate_altar(MapPtr map)
{  
  TilePtr altar_tile = map->at(centre_row, centre_col); 
  FeaturePtr altar   = FeatureGenerator::generate_altar(deity_id, ALIGNMENT_RANGE_NEUTRAL);
  altar_tile->set_feature(altar);
}

// Generate doors on the N/S/E/W walls
void GrandTempleGenerator::generate_temple_doors(MapPtr map)
{
  GeneratorUtils::generate_door(map, temple_start_row, centre_col);
  GeneratorUtils::generate_door(map, temple_start_row + temple_height - 1, centre_col);
  GeneratorUtils::generate_door(map, centre_row, temple_start_col + temple_width - 1);
  GeneratorUtils::generate_door(map, centre_row, temple_start_col);
}
