#include "CathedralGenerator.hpp"
#include "FeatureGenerator.hpp"
#include "Game.hpp"
#include "GeneratorUtils.hpp"
#include "ItemGenerationManager.hpp"
#include "LibrarySectorFeature.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

using namespace std;

CathedralGenerator::CathedralGenerator(const string& new_deity_id, MapPtr new_base_map)
: ChurchGenerator(new_deity_id, new_base_map, TileType::TILE_TYPE_CHURCH), start_row(0), start_col(0), church_height(0), church_width(0)
{
}

MapPtr CathedralGenerator::generate(const Dimensions& dim)
{
  return generate();
}

// Generate the cathedral
MapPtr CathedralGenerator::generate()
{
  MapPtr map = std::make_shared<Map>(*base_map);

  generate_cathedral(map);

  return map;
}

// Generate the cathedral
void CathedralGenerator::generate_cathedral(MapPtr map)
{
  Dimensions dim = map->size();
  int rows = dim.get_y();
  int cols = dim.get_x();
  
  int church_height_min = rows - 8;
  int church_height_max = rows - 4;
  
  int church_width_min = cols - 30;
  int church_width_max = cols - 10; // Again, we always assume 80x20 minimum
  
  church_height = RNG::range(church_height_min, church_height_max);
  church_width  = RNG::range(church_width_min, church_width_max);

  start_row = (rows / 2) - (church_height / 2);
  start_col = (cols / 2) - (church_width / 2);
  
  int pew_end_col = (start_col + (church_width/2));
  int pew_end_row = (start_row + church_height - 2);
  
  int dais_height = 3;
  int dais_width  = 5;
  int dais_start_row = start_row + (church_height/2) - (dais_height/2);
  int dais_start_col = pew_end_col + 2; // Need some space between the pews and the dais.  
  
  // Generate a long building, unlike most of other other churches, which are taller in the N-S direction.
  GeneratorUtils::generate_building(map, start_row, start_col, church_height, church_width);
  generate_doors(map);
  generate_fountains(map);
  generate_pews(map, pew_end_row, pew_end_col);
  generate_dais_and_altar(map, dais_start_row, dais_start_col, dais_height, dais_width);
  generate_feature_behind_dais(map, dais_start_row, dais_start_col, dais_height, dais_width);
  generate_back_rooms(map, dais_start_col + dais_width + 3, start_row, start_row + church_height, start_col + church_width);
}

// Generate a 5x5 dais, placing an altar in the centre.
void CathedralGenerator::generate_dais_and_altar(MapPtr map, const int dais_start_row, const int dais_start_col, const int dais_height, const int dais_width)
{
  TileGenerator tg;
  TilePtr dais_tile;
  
  for (int row = dais_start_row; row < dais_start_row + dais_height; row++)
  {
    for (int col = dais_start_col; col < dais_start_col + dais_width; col++)
    {
      dais_tile = tg.generate(TileType::TILE_TYPE_DAIS);
      map->insert(row, col, dais_tile);
    }
  }
  
  // Get the centre tile and generate a GoodAltar.
  int altar_row = dais_start_row + (dais_height/2);
  int altar_col = dais_start_col + (dais_width/2);
  dais_tile = map->at(altar_row, altar_col);
  
  FeaturePtr altar = FeatureGenerator::generate_altar(deity_id, AlignmentRange::ALIGNMENT_RANGE_GOOD);
  dais_tile->set_feature(altar);
}

void CathedralGenerator::generate_feature_behind_dais(MapPtr map, const int dais_start_row, const int dais_start_col, const int dais_height, const int dais_width)
{
  int feature_start_row = dais_start_row - 1;
  int feature_end_row = dais_start_row + dais_height + 1;
  int feature_col = dais_start_col + dais_width + 2;

  vector<ClassIdentifier> dais_features = { ClassIdentifier::CLASS_ID_FIRE_PILLAR, ClassIdentifier::CLASS_ID_FOUNTAIN, ClassIdentifier::CLASS_ID_SARCOPHAGUS, ClassIdentifier::CLASS_ID_HIGH_PRIEST_DECORATIVE_STATUE };
  ClassIdentifier ci = dais_features[RNG::range(0, dais_features.size() - 1)];

  for (int row = feature_start_row; row <= feature_end_row; row += 2)
  {
    FeaturePtr feature = FeatureGenerator::create_feature(ci);
    map->at(row, feature_col)->set_feature(feature);
  }
}

// Generate a pair of fountains by the entrance.
void CathedralGenerator::generate_fountains(MapPtr map)
{
  TilePtr fountain_tile_1 = map->at(start_row+2, start_col+2);
  TilePtr fountain_tile_2 = map->at(start_row+church_height-3, start_col+2);
  FeaturePtr fountain_1 = FeatureGenerator::generate_fountain();
  FeaturePtr fountain_2 = FeatureGenerator::generate_fountain();
  fountain_tile_1->set_feature(fountain_1);
  fountain_tile_2->set_feature(fountain_2);
}

// Generate east-west pews, up to the midway point of the cathedral.
void CathedralGenerator::generate_pews(MapPtr map, const int pew_end_row, const int pew_end_col)
{
  for (int pew_col = start_col + 4; pew_col < pew_end_col; pew_col++)
  {
    for (int pew_row = start_row+2; pew_row < pew_end_row; pew_row++)
    {
      if (pew_row == (start_row + (church_height / 2)) || pew_row == (start_row + (church_height / 2 - 1)))
      {
        continue;
      }
      // Space the pews nicely.
      else if (pew_col % 2 == 0)
      {
        FeaturePtr pew = FeatureGenerator::generate_pew(PewDirection::PEW_DIRECTION_EAST_WEST);
        TilePtr current_tile = map->at(pew_row, pew_col);
        current_tile->set_feature(pew);
      }
    }
  }
}

// Generate a pair of doors that lead into the cathedral, as well as statues
// outside.
void CathedralGenerator::generate_doors(MapPtr map)
{
  TileGenerator tg;
  TilePtr first_door_tile  = tg.generate(TileType::TILE_TYPE_DUNGEON);
  TilePtr second_door_tile = tg.generate(TileType::TILE_TYPE_DUNGEON);
  FeaturePtr first_door    = FeatureGenerator::generate_door();
  FeaturePtr second_door   = FeatureGenerator::generate_door();
  first_door_tile->set_feature(first_door);
  second_door_tile->set_feature(second_door);
  
  int door_row_1 = start_row + (church_height / 2 - 1);
  int door_row_2 = start_row + (church_height / 2);

  map->insert(door_row_1, start_col, first_door_tile);
  map->insert(door_row_2, start_col, second_door_tile);

  vector<Coordinate> statue_coords = { {door_row_1 - 1, start_col - 2}, {door_row_2 + 1, start_col - 2} };
  for (const Coordinate& c : statue_coords)
  {
    FeaturePtr statue = FeatureGenerator::generate_decorative_statue(DecorativeStatueType::DECORATIVE_STATUE_TYPE_HIGH_PRIEST);
    map->at(c)->set_feature(statue);
  }
}

// Generate the back rooms: treasure room (potentially), crypt entrance (potentially), priest's quarters
void CathedralGenerator::generate_back_rooms(MapPtr map, const int room_start_col, const int start_row, const int end_row, const int end_col)
{
  // Create the treasure room and stairs to the crypt, or the library.
  int back_room_wall_row = generate_secondary_back_room(map, room_start_col, start_row, end_row, end_col);

  // Generate the priest's quarters
  generate_priest_quarters(map, room_start_col, start_row, end_row, end_col, back_room_wall_row); 
}

// Generate the priest's quarters in the back of the Cathedral
void CathedralGenerator::generate_priest_quarters(MapPtr map, const int room_start_col, const int start_row, const int end_row, const int end_col, int back_room_wall_row)
{
  TileGenerator tg;
  TilePtr current_tile;

  for (int row = start_row + 1; row < start_row + church_height; row++)
  {
    if (row != start_row+2)
    {
      current_tile = tg.generate(TileType::TILE_TYPE_ROCK);
      map->insert(row, room_start_col, current_tile);
    }
    else
    {
      FeaturePtr priest_door = FeatureGenerator::generate_door();
      current_tile = map->at(row, room_start_col);
      current_tile->set_feature(priest_door);
    }
  }

  // Always a bed.
  int row = RNG::range(start_row + 1, back_room_wall_row - 2);
  FeaturePtr bed = FeatureGenerator::generate_bed();
  map->at({ row, room_start_col + 2 })->set_feature(bed);

  // A couple of fire pillars in two corners.
  vector<Coordinate> corners = { {start_row + 1, end_col - 2}, {back_room_wall_row - 1, room_start_col + 1} };
  for (const Coordinate& c : corners)
  {
    FeaturePtr fp = FeatureGenerator::generate_fire_pillar();
    map->at(c)->set_feature(fp);
  }

  // Sometimes: table, bench
  if (RNG::percent_chance(65))
  {
    FeaturePtr table = FeatureGenerator::generate_table();
    add_feature_to_middle_of_priest_quarters(map, room_start_col, start_row, end_row, end_col, back_room_wall_row, table);
  }

  if (RNG::percent_chance(65))
  {
    FeaturePtr bench = FeatureGenerator::generate_bench();
    add_feature_to_middle_of_priest_quarters(map, room_start_col, start_row, end_row, end_col, back_room_wall_row, bench);
  }
}

void CathedralGenerator::add_feature_to_middle_of_priest_quarters(MapPtr map, const int room_start_col, const int start_row, const int end_row, const int end_col, const int back_room_wall_row, FeaturePtr feature)
{
  if (map != nullptr)
  {
    int row = RNG::range(start_row + 2, back_room_wall_row - 2);
    int col = RNG::range(start_col + 2, end_col - 2);

    map->at({ row, col })->set_feature(feature);
  }
}

int CathedralGenerator::generate_secondary_back_room(MapPtr map, const int room_start_col, const int start_row, const int end_row, const int end_col)
{
  TileGenerator tg;
  TilePtr current_tile;
  int door_col = 0;
  int wall_row = start_row + church_height - static_cast<int>((church_height/2.5));
  for (int col = room_start_col; col < start_col + church_width; col++)
  {
    if (col == start_col + church_width-3)
    {
      FeaturePtr door = FeatureGenerator::generate_door();
      current_tile = map->at(wall_row, col);
      current_tile->set_feature(door);
      door_col = col;
    }
    else
    {
      current_tile = tg.generate(TileType::TILE_TYPE_ROCK);
      map->insert(wall_row, col, current_tile);
    }
  }  
  
  // 50% chance of a treasure room and crypt
  int generate_treasure_room_and_crypt = RNG::range(0, 1);
  
  if (generate_treasure_room_and_crypt)
  {
    // Sarcophagi
    vector<Coordinate> corners = { {wall_row + 1, room_start_col + 1}, {wall_row + 1, end_col - 2}, {end_row - 2, room_start_col + 1}, {end_row - 2, end_col - 2} };
    for (Coordinate& c : corners)
    {
      FeaturePtr sarcophagus = FeatureGenerator::generate_sarcophagus();
      map->at(c)->set_feature(sarcophagus);
    }
    
    // Generate the stairs down to the crypt
    Coordinate c = { (wall_row + start_row + church_height) / 2, (room_start_col + start_col + church_width) / 2 };
    place_staircase(map, c.first, c.second, TileType::TILE_TYPE_DOWN_STAIRCASE, TileType::TILE_TYPE_CRYPT, Direction::DIRECTION_DOWN, false, false);
  }
  else
  {
    LibrarySectorFeature lsf;
    lsf.generate_interior(map, { wall_row, room_start_col }, { end_row-1, end_col-1 }, { wall_row, door_col });
  }

  return wall_row;
}
