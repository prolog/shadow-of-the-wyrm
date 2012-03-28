#include "FeatureGenerator.hpp"
#include "RNG.hpp"
#include "SimpleChurchGenerator.hpp"
#include "TileGenerator.hpp"

using std::string;

SimpleChurchGenerator::SimpleChurchGenerator(const string& new_deity_id, MapPtr new_base_map)
: ChurchGenerator(new_deity_id, new_base_map)
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

void SimpleChurchGenerator::generate_church(MapPtr map)
{
  Dimensions dim = map->size();
  int rows = dim.get_y();
  int cols = dim.get_x();

  int church_height = 3 * (RNG::range(4, 5));
  int church_width  = church_height + 3;
  if ((church_width%2)==0) church_width++; // An odd number ensures the same number of pews on both sides.

  int start_row = (rows / 2) - (church_height / 2);
  int start_col = (cols / 2) - (church_width / 2);

  // Generate the church.
  generate_building(map, start_row, start_col, church_height, church_width);

  // Generate the doorway.
  FeaturePtr doorway = FeatureGenerator::generate_door();
  TilePtr door_entryway = TileGenerator::generate(TILE_TYPE_DUNGEON);
  door_entryway->set_feature(doorway);
  map->insert(start_row + church_height - 1, start_col + (church_width / 2), door_entryway);

  // Generate the altar.  Always right near the north of the church.
  FeaturePtr altar = FeatureGenerator::generate_altar(deity_id, ALIGNMENT_RANGE_GOOD);
  int altar_row = start_row + 2;
  TilePtr altar_tile = map->at(start_row+2, start_col + (church_width / 2));
  altar_tile->set_feature(altar);

  // Generate the pews.
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
