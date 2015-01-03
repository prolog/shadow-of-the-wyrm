#include "FeatureGenerator.hpp"
#include "GeneratorUtils.hpp"
#include "RNG.hpp"
#include "SnakingTempleGenerator.hpp"
#include "StatueGenerator.hpp"
#include "TileGenerator.hpp"

using std::string;

SnakingTempleGenerator::SnakingTempleGenerator(const string& new_deity_id, MapPtr new_base_map)
: ChurchGenerator(new_deity_id, new_base_map, TileType::TILE_TYPE_TEMPLE),
temple_width(0), temple_height(0), temple_middle_width(0), temple_middle_height(0),
temple_row_start(0), temple_row_end(0), temple_col_start(0), temple_col_end(0), head_height(0),
temple_middle_start_row(0), temple_middle_end_row(0), temple_middle_start_col(0), temple_middle_end_col(0)
{
}

MapPtr SnakingTempleGenerator::generate(const Dimensions& dim)
{
  return generate();
}

MapPtr SnakingTempleGenerator::generate()
{
  MapPtr map = std::make_shared<Map>(*base_map);

  generate_temple(map);

  return map;
}

// Initialize the various size, width, etc., parameters used to generate
// the temple.
void SnakingTempleGenerator::initialize_temple_values(const int rows, const int cols)
{
  temple_width  = RNG::range(get_temple_width_min(cols), get_temple_width_max(cols));
  temple_height = RNG::range(get_temple_height_min(rows), get_temple_height_max(rows));

  temple_middle_width = RNG::range(temple_width * 0.5, temple_width * 0.7);
  temple_middle_height = (rows/3);
    
  // Create the top and bottom sections
  temple_row_start = (rows/2) - (temple_height/2);
  temple_row_end   = temple_row_start + temple_height;
  
  temple_col_start = (cols/2) - (temple_width/2);  
  temple_col_end = temple_col_start + temple_width;
  head_height = (rows/4);

  temple_middle_start_row = (rows/2) - (temple_middle_height/2);
  temple_middle_end_row = temple_middle_start_row + temple_middle_height;
  temple_middle_start_col = (cols/2) - (temple_middle_width/2);
  temple_middle_end_col = temple_middle_start_col + temple_middle_width;
}

void SnakingTempleGenerator::generate_temple(MapPtr map)
{
  Dimensions dim = map->size();
  int rows = dim.get_y();
  int cols = dim.get_x();
  
  initialize_temple_values(rows, cols);
  
  // Top, bottom, and middle buildings
  GeneratorUtils::generate_building(map, temple_row_start, temple_col_start, head_height, temple_width);
  GeneratorUtils::generate_building(map, temple_row_end - head_height, temple_col_start, head_height, temple_width);
  GeneratorUtils::generate_building(map, temple_middle_start_row, temple_middle_start_col, temple_middle_height, temple_middle_width);
  connect_buildings(map);

  generate_temple_doors(map);
  generate_room_of_worship(map);
  generate_fountains(map);
  generate_fire_pillars(map);
  generate_statues(map);    
}

void SnakingTempleGenerator::connect_buildings(MapPtr map)
{
  Dimensions dim = map->size();
  int rows = dim.get_y();
  int cols = dim.get_x();

  // Connect the components
  // Top to middle
  int start_row = ((rows/2) - (temple_middle_height/2) + (rows/2 + temple_middle_height/2)) / 2;
  int start_col = (cols/2) - (temple_middle_width/2) + temple_middle_width - 1;
  int end_row = temple_row_start + head_height - 2; // Need a little extra room to add connective floor and hallway walls
  int end_col = temple_col_end - 3; // Need a little extra room for the hallway walls
  generate_L_hallway(map, start_row, start_col, end_row, end_col);
  
  // Middle to bottom
  // start_row is the same
  start_col = (cols/2) - (temple_middle_width/2);
  end_row = temple_row_end - head_height + 1;
  end_col = temple_col_start+2;
  generate_L_hallway(map, start_row, start_col, end_row, end_col);  
}

void SnakingTempleGenerator::generate_L_hallway(MapPtr map, const int start_row, const int start_col, const int end_row, const int end_col)
{
  TileGenerator tg;

  int x_offset = 1;
  if (start_col > end_col)
  {
    x_offset = -1;
  }
  
  // Start at (start_row, start_col)
  // Generate a hallway to (start_row, end_col)
  for (int col = start_col; col != end_col; col += x_offset)
  {
    TilePtr current_tile = tg.generate(TileType::TILE_TYPE_ROCK);
    map->insert(start_row-1, col, current_tile);
    
    current_tile = tg.generate(TileType::TILE_TYPE_DUNGEON);
    map->insert(start_row, col, current_tile);
    
    current_tile = tg.generate(TileType::TILE_TYPE_ROCK);
    map->insert(start_row+1, col, current_tile);
  }
  
  // Generate the L-joint
  TilePtr current_tile = tg.generate(TileType::TILE_TYPE_DUNGEON);
  map->insert(start_row, end_col, current_tile);
  
  current_tile = tg.generate(TileType::TILE_TYPE_ROCK);
  map->insert(start_row, end_col+x_offset, current_tile);    

  // Adjust the offset to determine whether to put the walls above/below the joint.
  int y_offset = 1;
  if (start_row > end_row)
  {
    y_offset = -1;
  }

  for (int col = end_col; col != end_col+(x_offset*2); col += x_offset)
  {
    current_tile = tg.generate(TileType::TILE_TYPE_ROCK);
    
    if (start_row > end_row)
    {
      map->insert(start_row+1, col, current_tile);
    }
    else
    {
      map->insert(start_row-1, col, current_tile);
    }
  }
    
  // Generate a hallway to (end_row, end_col)
  for (int row = start_row + y_offset; row != end_row; row += y_offset)
  {
    current_tile = tg.generate(TileType::TILE_TYPE_ROCK);
    map->insert(row, end_col-1, current_tile);
    
    current_tile = tg.generate(TileType::TILE_TYPE_DUNGEON);
    map->insert(row, end_col, current_tile);
    
    current_tile = tg.generate(TileType::TILE_TYPE_ROCK);
    map->insert(row, end_col+1, current_tile);
  }
}

// Generate the doors of the temple.  These should look vaguely teeth-like:
void SnakingTempleGenerator::generate_temple_doors(MapPtr map)
{
  TileGenerator tg;

  TilePtr door_tile_1 = tg.generate(TileType::TILE_TYPE_DUNGEON);
  TilePtr door_tile_2 = tg.generate(TileType::TILE_TYPE_DUNGEON);
  FeaturePtr door_1   = FeatureGenerator::generate_door();
  FeaturePtr door_2   = FeatureGenerator::generate_door();
  door_tile_1->set_feature(door_1);
  door_tile_2->set_feature(door_2);
  map->insert(temple_row_start+1, temple_col_start, door_tile_1);
  map->insert(temple_row_start+head_height-2, temple_col_start, door_tile_2);
}

// Generate the room of worship at the tail-end of the temple:
// pews, dais, altar.
void SnakingTempleGenerator::generate_room_of_worship(MapPtr map)
{
  int dais_row = (temple_row_end - head_height + temple_row_end) / 2;
  int dais_col = (temple_col_end - 4);

  generate_pews(map);
  generate_dais(map, dais_row, dais_col);  
  generate_altar(map, dais_row, dais_col);
}

// Generate the pews.  Use the EAST/WEST pews.
void SnakingTempleGenerator::generate_pews(MapPtr map)
{
  int centre_row = (temple_row_end - head_height + temple_row_end) / 2;
  for (int col = temple_col_start+4; col < temple_col_end - 8; col++)
  {
    if (col % 3 == 0)
    {
      for (int row = temple_row_end-head_height+1; row < temple_row_end-1; row++)
      {
        // Leave the centre open to walk through
        if (row != centre_row)
        {
          TilePtr current_tile = map->at(row, col);
          FeaturePtr pew = FeatureGenerator::generate_pew(PEW_DIRECTION_EAST_WEST);
          current_tile->set_feature(pew);
        }
      }
    }
  }  
}

void SnakingTempleGenerator::generate_dais(MapPtr map, const int dais_row, const int dais_col)
{
  TileGenerator tg;

  int dais_start_col = temple_col_end - 6;
  int dais_end_col   = temple_col_end - 3;
  for (int cur_dais_col = dais_start_col; cur_dais_col < dais_end_col; cur_dais_col++)
  {
    TilePtr dais_tile = tg.generate(TileType::TILE_TYPE_DAIS);
    map->insert(dais_row, cur_dais_col, dais_tile); 
  }
  
  for (int cur_dais_row = temple_row_end - head_height + 1; cur_dais_row < temple_row_end-1; cur_dais_row++)
  {
    TilePtr dais_tile = tg.generate(TileType::TILE_TYPE_DAIS);
    map->insert(cur_dais_row, dais_col, dais_tile);
  }  
}

void SnakingTempleGenerator::generate_altar(MapPtr map, const int dais_row, const int dais_col)
{
  TilePtr centre_dais_tile = map->at(dais_row, dais_col);
  FeaturePtr altar = FeatureGenerator::generate_altar(deity_id, ALIGNMENT_RANGE_NEUTRAL);
  centre_dais_tile->set_feature(altar);  
}

void SnakingTempleGenerator::generate_fountains(MapPtr map)
{
  // Fountains fill the top room
  int fountain_row = (temple_row_start + (temple_row_start + head_height)) /2;
  for (int col = temple_col_start+3; col < temple_col_end-3; col++)
  {
    if (col % 5 == 0)
    {
      FeaturePtr fountain = FeatureGenerator::generate_fountain();
      TilePtr current_tile = map->at(fountain_row, col);
      current_tile->set_feature(fountain);
    }
  }  
}

// Generate the various pillars of flame throughout the temple
void SnakingTempleGenerator::generate_fire_pillars(MapPtr map)
{
  generate_fire_pillars_in_entrance(map);
  generate_fire_pillars_in_hall_of_heroes(map);
  generate_fire_pillars_in_room_of_worship(map);
}

// Generate the pillars in the entrance room
void SnakingTempleGenerator::generate_fire_pillars_in_entrance(MapPtr map)
{
  for (int row = temple_row_start+1; row < temple_row_start + head_height-1; row++)
  {
    // Place it on the left if it's not blocking a door
    if (row > (temple_row_start+1) && row < (temple_row_start + head_height - 2))
    {
      FeaturePtr fire_pillar_left = FeatureGenerator::generate_fire_pillar();
      TilePtr tile_left = map->at(row, temple_col_start+1);
      tile_left->set_feature(fire_pillar_left);
    }
    
    // Always place on right
    FeaturePtr fire_pillar_right = FeatureGenerator::generate_fire_pillar();
    TilePtr right_tile = map->at(row, temple_col_end-2);
    right_tile->set_feature(fire_pillar_right);
  }
}

// Generate the pillars in the middle hall
void SnakingTempleGenerator::generate_fire_pillars_in_hall_of_heroes(MapPtr map)
{
  // Fire pillars - middle
  // Place in corners
  TilePtr top_left_tile     = map->at(temple_middle_start_row+1, temple_middle_start_col+1);
  TilePtr top_right_tile    = map->at(temple_middle_start_row+1, temple_middle_end_col-2);
  TilePtr bottom_left_tile  = map->at(temple_middle_end_row-2, temple_middle_start_col+1);
  TilePtr bottom_right_tile = map->at(temple_middle_end_row-2, temple_middle_end_col-2);
  
  FeaturePtr pillar_tl = FeatureGenerator::generate_fire_pillar();
  FeaturePtr pillar_tr = FeatureGenerator::generate_fire_pillar();
  FeaturePtr pillar_bl = FeatureGenerator::generate_fire_pillar();
  FeaturePtr pillar_br = FeatureGenerator::generate_fire_pillar();
  
  top_left_tile->set_feature(pillar_tl);
  top_right_tile->set_feature(pillar_tr);
  bottom_left_tile->set_feature(pillar_bl);
  bottom_right_tile->set_feature(pillar_br);
}

// Generate the pillars in the room of worship
void SnakingTempleGenerator::generate_fire_pillars_in_room_of_worship(MapPtr map)
{
  for (int row = temple_row_end - head_height + 1; row < temple_row_end - 1; row++)
  {
    FeaturePtr fire_pillar_left  = FeatureGenerator::generate_fire_pillar();
    FeaturePtr fire_pillar_right = FeatureGenerator::generate_fire_pillar();
    
    TilePtr left_tile  = map->at(row, temple_col_start+1);
    TilePtr right_tile = map->at(row, temple_col_end-2);
    
    left_tile->set_feature(fire_pillar_left);
    right_tile->set_feature(fire_pillar_right);
  }
}

// Generate the statues in the hall of heroes
void SnakingTempleGenerator::generate_statues(MapPtr map)
{
  for (int col = temple_middle_start_col+3; col < temple_middle_end_col-3; col++)
  {
    if (col % 2 == 0)
    {
      FeaturePtr statue_1 = StatueGenerator::generate_decorative_statue(static_cast<DecorativeStatueType>(RNG::range(DecorativeStatueType::DECORATIVE_STATUE_TYPE_FIRST, DecorativeStatueType::DECORATIVE_STATUE_TYPE_LAST)));
      FeaturePtr statue_2 = StatueGenerator::generate_decorative_statue(static_cast<DecorativeStatueType>(RNG::range(DecorativeStatueType::DECORATIVE_STATUE_TYPE_FIRST, DecorativeStatueType::DECORATIVE_STATUE_TYPE_LAST)));
      TilePtr tile_top    = map->at(temple_middle_start_row+1, col);
      TilePtr tile_bottom = map->at(temple_middle_end_row-2, col);
      
      tile_top->set_feature(statue_1);
      tile_bottom->set_feature(statue_2);
    }
  }  
}

// For the following methods, the assumption is, as always, a minimum map size of 80x20
int SnakingTempleGenerator::get_temple_width_min(const int cols)
{
  return static_cast<int>(cols * 0.66);
}

int SnakingTempleGenerator::get_temple_width_max(const int cols)
{
  return static_cast<int>(cols * 0.85);
}

int SnakingTempleGenerator::get_temple_height_min(const int rows)  
{
  return static_cast<int>(rows * 0.9);
}

int SnakingTempleGenerator::get_temple_height_max(const int rows)
{
  return static_cast<int>(rows * 0.9);
}
