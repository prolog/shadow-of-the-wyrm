#include "RectangularShrineGenerator.hpp"
#include "FeatureGenerator.hpp"
#include "GeneratorUtils.hpp"
#include "RNG.hpp"
#include "StatueGenerator.hpp"

using namespace std;

RectangularShrineGenerator::RectangularShrineGenerator(MapPtr new_base_map)
: ShrineGenerator(new_base_map)
{
}

MapPtr RectangularShrineGenerator::generate(const Dimensions& dim)
{
  return generate();
}

MapPtr RectangularShrineGenerator::generate()
{
  MapPtr map = make_shared<Map>(*base_map);

  Dimensions dim = map->size();

  int num_rows = dim.get_y();
  int mid_row = num_rows / 2;
  int start_row = RNG::range(mid_row * 0.2, mid_row * 0.4);
  int shrine_height = 2 * std::abs(mid_row - start_row);

  int num_cols = dim.get_x();
  int mid_col = num_cols / 2;
  int start_col = RNG::range(mid_col * 0.2, mid_col * 0.4);
  int shrine_width = 2 * std::abs(mid_col - start_col);

  GeneratorUtils::generate_building(map, start_row, start_col, shrine_height, shrine_width);
  create_entrances(map, start_row, start_col, shrine_height, shrine_width, mid_row, mid_col);
  place_pillars_and_statues(map, start_row, start_col, shrine_height, shrine_width, mid_row, mid_col);
  place_relic(map, mid_row, mid_col);
  add_dungeon_tiles_to_preset_locations(map);

  return map;
}

void RectangularShrineGenerator::create_entrances(MapPtr map, const int start_row, const int start_col, const int height, const int width, const int mid_row, const int mid_col)
{
  // Create entrances north, south, east, and west.
  // Each entrance is 3-wide, to prevent the player from bottling up monsters.
  if (map != nullptr)
  {
    // N, S
    vector<int> rows = {start_row, start_row + height - 1};

    for (int row : rows)
    {
      for (int col = mid_col - 1; col <= (mid_col + 1); col++)
      {
        TilePtr floor_tile = tg.generate(TileType::TILE_TYPE_DUNGEON);
        map->insert(row, col, floor_tile);
      }
    }

    // E, W
    vector<int> cols = {start_col, start_col + width - 1};

    for (int col : cols)
    {
      for (int row = mid_row - 1; row <= (mid_row + 1); row++)
      {
        TilePtr floor_tile = tg.generate(TileType::TILE_TYPE_DUNGEON);
        map->insert(row, col, floor_tile);
      }
    }
  }
}

// From the one door to another, place pillars and statues.
// Alternate pillars and statues to break up the monotony a bit.
void RectangularShrineGenerator::place_pillars_and_statues(MapPtr map, const int start_row, const int start_col, const int height, const int width, const int mid_row, const int mid_col)
{
  if (map != nullptr)
  {
    int end_row = start_row + height;
    bool pillar = true;

    // Generate from north to south.
    for (int row = start_row+1; (row+2) <= end_row; row += 2)
    {
      // Keep the centre empty.
      if (row != mid_row)
      {
        generate_pillar_or_statue(map, { { row, mid_col - 1 },{ row, mid_col + 1 } }, pillar);
        pillar = !pillar;
      }
    }

    int end_col = start_col + width;
    pillar = true;

    // Generate from west to east, making sure not to generate in a particular
    // column when the previous and next have one. (no uglies)
    for (int col = start_col+1; (col+2) <= end_col; col += 2)
    {
      // The centre of the shrine needs to remain open.
      if (col != mid_col)
      {
        TilePtr prev = map->at(mid_row - 1, col - 1);
        TilePtr next = map->at(mid_row - 1, col + 1);

        if (prev && next && (!prev->has_feature()) && (!next->has_feature()))
        {
          generate_pillar_or_statue(map, { { mid_row - 1, col },{ mid_row + 1, col } }, pillar);
          pillar = !pillar;
        }
      }
    }
  }
}

void RectangularShrineGenerator::generate_pillar_or_statue(MapPtr map, const vector<Coordinate>& coords, const bool pillar)
{
  FeaturePtr feature;
  
  if (pillar)
  {
    feature = FeatureGenerator::generate_fire_pillar();
  }
  else
  {
    feature = StatueGenerator::generate_decorative_statue(DecorativeStatueType::DECORATIVE_STATUE_TYPE_HIGH_PRIEST);
  }

  for (const Coordinate& c : coords)
  {
    TilePtr tile = map->at(c);

    if (tile != nullptr)
    {
      tile->set_feature(feature);
    }
  }
}
