#include "FeatureGenerator.hpp"
#include "FortifiedChurchGenerator.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

using std::string;

FortifiedChurchGenerator::FortifiedChurchGenerator(const string& new_deity_id, MapPtr new_base_map)
: ChurchGenerator(new_deity_id, new_base_map)
{
}

MapPtr FortifiedChurchGenerator::generate(const Dimensions& dim)
{
  return generate();
}

MapPtr FortifiedChurchGenerator::generate()
{
  MapPtr map = MapPtr(new Map(*base_map));

  generate_church(map);

  return map;
}

// Generate the fortified church.
void FortifiedChurchGenerator::generate_church(MapPtr map)
{
  Dimensions dim = map->size();
  int rows = dim.get_y();
  int cols = dim.get_x();

  int church_height = 2 * RNG::range(6, 7);
  int church_width  = 3 * RNG::range(8, 9);

  int start_row = (rows / 2) - (church_height / 2);
  int start_col = (cols / 2) - (church_width  / 2);

  // Church itself.
  generate_building(map, start_row, start_col, church_height, church_width);

  // Parapets.
  generate_parapets(map, church_height, church_width);

  // Altar in the very centre.
  TilePtr centre_tile = map->at(start_row + (church_height / 2), start_col + (church_width / 2));
  FeaturePtr altar = FeatureGenerator::generate_altar(deity_id, ALIGNMENT_RANGE_GOOD);
  centre_tile->set_feature(altar);

  // No Pews.
  // Front doors.  Two of them - looks more impressive.
  TilePtr first_door_tile  = TileGenerator::generate(TILE_TYPE_DUNGEON);
  TilePtr second_door_tile = TileGenerator::generate(TILE_TYPE_DUNGEON);
  FeaturePtr first_door    = FeatureGenerator::generate_door();
  FeaturePtr second_door   = FeatureGenerator::generate_door();
  first_door_tile->set_feature(first_door);
  second_door_tile->set_feature(second_door);
  
  map->insert(start_row + church_height-1, start_col + (church_width/2)-1, first_door_tile);
  map->insert(start_row + church_height-1, start_col + (church_width/2), second_door_tile);
}

// Generate the church's parapets.
void FortifiedChurchGenerator::generate_parapets(MapPtr map, const int church_height, const int church_width)
{
  Dimensions dim = map->size();
  int rows = dim.get_y();
  int cols = dim.get_x();

  int parapet_size = (church_height / 3);

  int start_row = (rows / 2) - (church_height / 2);
  int start_col = (cols / 2) - (church_width  / 2);

  // Top left
  create_parapet(map, start_row - (parapet_size / 2), start_col - (parapet_size / 2), parapet_size);

  // Top right
  create_parapet(map, start_row - (parapet_size / 2), start_col + church_width - (parapet_size / 2), parapet_size);

  // Bottom left
  create_parapet(map, start_row + church_height - (parapet_size / 2), start_col - (parapet_size / 2), parapet_size);

  // Bottom right
  create_parapet(map, start_row + church_height - (parapet_size / 2), start_col + church_width - (parapet_size / 2), parapet_size);
}

// Create the parapet.
void FortifiedChurchGenerator::create_parapet(MapPtr map, const int start_row, const int start_col, const int parapet_size)
{
  for (int row = start_row; row < start_row + parapet_size; row++)
  {
    for (int col = start_col; col < start_col + parapet_size; col++)
    {
      if (row == start_row || row == (start_row + parapet_size - 1)
        ||col == start_col || col == (start_col + parapet_size - 1))
      {
        // Check the current tile.  If it's DUNGEON, we're on the church
        // floor.  Don't generate a wall in this case - the parapet should
        // be accessible within the church for defense purposes.
        // If it's ROCK, replace it with DUNGEON.
        TilePtr current_tile = map->at(row, col);

        if (current_tile)
        {
          TileType tile_type = current_tile->get_tile_type();
                    
          if (tile_type != TILE_TYPE_DUNGEON)
          {
            TilePtr new_tile;
            new_tile = TileGenerator::generate(TILE_TYPE_ROCK);
            map->insert(row, col, new_tile);
          }
        }
      }
      else
      {
        // If there's a non-floor tile here, replace it.
        TilePtr current_tile = map->at(row, col);
        if (current_tile && current_tile->get_tile_type() != TILE_TYPE_DUNGEON)
        {
          TilePtr new_floor_tile = TileGenerator::generate(TILE_TYPE_DUNGEON);
          map->insert(row, col, new_floor_tile);
        }
      }
    }
  }
}
