#include "FeatureGenerator.hpp"
#include "GeneratorUtils.hpp"
#include "RNG.hpp"
#include "SimpleChurchGenerator.hpp"
#include "TileGenerator.hpp"

using std::string;

SimpleChurchGenerator::SimpleChurchGenerator(const string& new_deity_id, MapPtr new_base_map)
: ChurchGenerator(new_deity_id, new_base_map),
start_row(0), start_col(0), church_height(0), church_width(0), altar_row(0)
{
}

// Generate a simple stone church on the base map.
// Ignore dimensions for now.
MapPtr SimpleChurchGenerator::generate(const Dimensions& dim)
{
  return generate();
}

// Generate a simple stone church on the base map.
MapPtr SimpleChurchGenerator::generate()
{
  MapPtr church_map = MapPtr(new Map(*base_map));

  generate_church(church_map);

  return church_map;
}

// Initialize the church's dimensions
void SimpleChurchGenerator::initialize_dimensions(MapPtr map)
{
  Dimensions dim = map->size();
  int rows = dim.get_y();
  int cols = dim.get_x();

  church_height = 3 * (RNG::range(4, 5));
  church_width  = church_height + 3;
  if ((church_width%2)==0) church_width++; // An odd number ensures the same number of pews on both sides.

  start_row = (rows / 2) - (church_height / 2);
  start_col = (cols / 2) - (church_width / 2);  
}

// Create the church
void SimpleChurchGenerator::generate_church(MapPtr map)
{
  // Generate the church.
  GeneratorUtils::generate_building(map, start_row, start_col, church_height, church_width);
  
  // Generate the altar, pews, and doorway.
  generate_features(map);  
}

// Generate the church's features: altar, pews, and door.
void SimpleChurchGenerator::generate_features(MapPtr map)
{
  generate_door(map);
  generate_altar(map);
  generate_pews(map);
}

void SimpleChurchGenerator::generate_altar(MapPtr map)
{
  FeaturePtr altar = FeatureGenerator::generate_altar(deity_id, ALIGNMENT_RANGE_GOOD);
  altar_row = start_row + 2;
  TilePtr altar_tile = map->at(start_row+2, start_col + (church_width / 2));
  altar_tile->set_feature(altar);  
}

void SimpleChurchGenerator::generate_pews(MapPtr map)
{
  for (int row = altar_row+3; row < start_row + church_height-3; row = row + 2)
  {
    for (int col = start_col+2; col < start_col + church_width-2; col++)
    {
      // Leave the centre open for aesthetic purposes.
      if (col != (start_col + church_width / 2))
      {
        FeaturePtr pew = FeatureGenerator::generate_pew();
        TilePtr current_tile = map->at(row, col);
        current_tile->set_feature(pew);
      }
    }
  }  
}

void SimpleChurchGenerator::generate_door(MapPtr map)
{
  FeaturePtr doorway = FeatureGenerator::generate_door();
  TilePtr door_entryway = TileGenerator::generate(TILE_TYPE_DUNGEON); // Ensure that the doorway is situated on a floor.
  door_entryway->set_feature(doorway);
  map->insert(start_row + church_height - 1, start_col + (church_width / 2), door_entryway);
}
