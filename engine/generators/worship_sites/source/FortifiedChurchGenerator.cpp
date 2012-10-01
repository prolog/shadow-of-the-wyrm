#include <boost/make_shared.hpp>
#include "FeatureGenerator.hpp"
#include "FortifiedChurchGenerator.hpp"
#include "GeneratorUtils.hpp"
#include "RNG.hpp"
#include "StatueGenerator.hpp"
#include "TileGenerator.hpp"

using std::string;

FortifiedChurchGenerator::FortifiedChurchGenerator(const string& new_deity_id, MapPtr new_base_map)
: ChurchGenerator(new_deity_id, new_base_map, TILE_TYPE_CHURCH),
start_row(0), start_col(0), church_height(0), church_width(0), altar_row(0), altar_col(0)
{
}

MapPtr FortifiedChurchGenerator::generate(const Dimensions& dim)
{
  return generate();
}

MapPtr FortifiedChurchGenerator::generate()
{
  MapPtr map = boost::make_shared<Map>(*base_map);

  generate_church(map);

  return map;
}

// Initialize the church's dimensions
void FortifiedChurchGenerator::initialize_dimensions(MapPtr map)
{
  Dimensions dim = map->size();
  int rows = dim.get_y();
  int cols = dim.get_x();

  church_height = 2 * RNG::range(6, 7);
  church_width  = 3 * RNG::range(8, 9);

  start_row = (rows / 2) - (church_height / 2);
  start_col = (cols / 2) - (church_width  / 2);  
}
// Generate the fortified church.
void FortifiedChurchGenerator::generate_church(MapPtr map)
{
  initialize_dimensions(map);
  GeneratorUtils::generate_building(map, start_row, start_col, church_height, church_width);
  generate_parapets(map);
  generate_features(map);
}

// Generate the church's parapets.
void FortifiedChurchGenerator::generate_parapets(MapPtr map)
{
  int parapet_size = (church_height / 3);

  // Top left, top right, bottom left, bottom right
  create_parapet(map, start_row - (parapet_size / 2), start_col - (parapet_size / 2), parapet_size);
  create_parapet(map, start_row - (parapet_size / 2), start_col + church_width - (parapet_size / 2), parapet_size);
  create_parapet(map, start_row + church_height - (parapet_size / 2), start_col - (parapet_size / 2), parapet_size);
  create_parapet(map, start_row + church_height - (parapet_size / 2), start_col + church_width - (parapet_size / 2), parapet_size);
}

// Create the parapet.
void FortifiedChurchGenerator::create_parapet(MapPtr map, const int parapet_start_row, const int parapet_start_col, const int parapet_size)
{
  for (int row = parapet_start_row; row < parapet_start_row + parapet_size; row++)
  {
    for (int col = parapet_start_col; col < parapet_start_col + parapet_size; col++)
    {
      if (row == parapet_start_row || row == (parapet_start_row + parapet_size - 1)
        ||col == parapet_start_col || col == (parapet_start_col + parapet_size - 1))
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

void FortifiedChurchGenerator::generate_features(MapPtr map)
{
  // Altar near the north wall
  generate_altar(map);
    
  // Statues of knights/warlords leading up to the altar.
  generate_statues(map);
  
  // Front doors.  Two of them - looks more impressive.
  generate_doors(map);
}

// Generate an altar near the centre of the north wall
void FortifiedChurchGenerator::generate_altar(MapPtr map)
{
  altar_row = start_row + 2;
  altar_col = start_col + (church_width / 2);
  TilePtr centre_tile = map->at(altar_row, altar_col);
  FeaturePtr altar = FeatureGenerator::generate_altar(deity_id, ALIGNMENT_RANGE_GOOD);
  centre_tile->set_feature(altar);
}

// Generate statues leading up to the altar.  Requires that the altar has been created
// already, as this initializes the altar_row and altar_col class members.
void FortifiedChurchGenerator::generate_statues(MapPtr map)
{
  DecorativeStatueType statue_type;
  int end_row = start_row + church_height - 1; // Skip the wall
  for (int cur_row = altar_row+1; cur_row < end_row; cur_row++)
  {
    if (cur_row % 2 == 0)
    {
      statue_type = DECORATIVE_STATUE_TYPE_KNIGHT;
      
      int val = RNG::range(1, 100);
      if (val < 50)
      {
        statue_type = DECORATIVE_STATUE_TYPE_WARLORD;
      }
      
      FeaturePtr west_statue = StatueGenerator::generate_decorative_statue(statue_type);
      TilePtr west_tile = map->at(cur_row, altar_col-1);
      west_tile->set_feature(west_statue);
      
      FeaturePtr east_statue = StatueGenerator::generate_decorative_statue(statue_type);
      TilePtr east_tile = map->at(cur_row, altar_col+1);
      east_tile->set_feature(east_statue);
    }
  }
}

// Generate a pair of front doors, side by side, on the south wall
void FortifiedChurchGenerator::generate_doors(MapPtr map)
{
  TilePtr first_door_tile  = TileGenerator::generate(TILE_TYPE_DUNGEON);
  TilePtr second_door_tile = TileGenerator::generate(TILE_TYPE_DUNGEON);
  FeaturePtr first_door    = FeatureGenerator::generate_door();
  FeaturePtr second_door   = FeatureGenerator::generate_door();
  first_door_tile->set_feature(first_door);
  second_door_tile->set_feature(second_door);
  
  map->insert(start_row + church_height-1, start_col + (church_width/2)-1, first_door_tile);
  map->insert(start_row + church_height-1, start_col + (church_width/2), second_door_tile);
}
