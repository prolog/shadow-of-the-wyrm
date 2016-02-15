#include "SewerGenerator.hpp"
#include "CoordUtils.hpp"
#include "Log.hpp"
#include "MapUtils.hpp"
#include "RNG.hpp"

using namespace std;

const int SewerGenerator::MIN_WIDTH = 5;
const int SewerGenerator::MAX_WIDTH = 27;
const int SewerGenerator::MIN_HEIGHT = 3;
const int SewerGenerator::MAX_HEIGHT = 7;
const int SewerGenerator::Y_INCR = 2;
const int SewerGenerator::X_INCR = 2;

SewerGenerator::SewerGenerator(const std::string& new_map_exit_id)
: Generator(new_map_exit_id, TileType::TILE_TYPE_SCRUB)
{
}

MapPtr SewerGenerator::generate(const Dimensions& dimensions)
{
  MapPtr result_map = std::make_shared<Map>(dimensions);

  fill(result_map, TileType::TILE_TYPE_ROCK);

  // Generate the sewer sections, and then connect them together.
  generate_sewer_sections(result_map);
  connect_sewer_sections(result_map);

  // Place up and potentially down staircases as appropriate.
  // ...

  return result_map;
}

void SewerGenerator::generate_sewer_sections(MapPtr result_map)
{
  Dimensions dimensions = result_map->size();

  int rows = dimensions.get_y();
  int cols = dimensions.get_x();

  int length = 0;

  int cur_row = 1;

  // For each row:
  while (cur_row < rows - 1)
  {
    int start_x = RNG::range(1, 5);
    int length = RNG::range(MIN_WIDTH, MAX_WIDTH);

    while (start_x + length < cols - 1)
    {
      // Generate a sewer piece, and place it on the map
      for (int i = start_x; i <= start_x + length; i++)
      {
        TilePtr tile = tg.generate(TileType::TILE_TYPE_SEWER);
        result_map->insert(cur_row, i, tile);
      }

      // Track it.
      Coordinate start(cur_row, start_x);
      Coordinate end(cur_row, start_x + length);

      sections[cur_row].push_back(make_pair(start, end));

      start_x += (length + X_INCR);
      length = RNG::range(MIN_WIDTH, MAX_WIDTH);
    }

    cur_row += Y_INCR;
  }
}

void SewerGenerator::connect_sewer_sections(MapPtr result_map)
{
  // Now we've got a bunch of horizontal sections, and need to connect them.
  // Iterate through each row in the sections map.  For each section, if
  // it overlaps any sections in the row below, we need a connection,
  // somewhere along the intersecting coordinates.
  for (const auto& row_pair : sections)
  {
    int row_num = row_pair.first;
    vector<pair<Coordinate, Coordinate>> pipe_sections = row_pair.second;

    int next_row = row_num += Y_INCR;
    auto r_it = sections.find(next_row);

    // If we're on the last row, we can stop, as there'll be nothing below.
    if (r_it == sections.end())
    {
      break;
    }
    else
    {
      for (const auto& ps : pipe_sections)
      {
        // Have we stopped overlapping?
        vector<pair<Coordinate, Coordinate>> lower_coords = r_it->second;

        for (const auto& lc : lower_coords)
        {
          if (CoordUtils::starts_after(lc, ps))
          {
            break;
          }
          // Any overlap?
          else
          {
            pair<bool, vector<Coordinate>> overlap = CoordUtils::are_segments_joinable(ps, lc);

            // There's some overlap - take a random coordinate and dig there.
            if (overlap.first == true && !overlap.second.empty())
            {
              vector<Coordinate> overlap_coords = overlap.second;
              Coordinate dig_coord = overlap_coords.at(RNG::range(0, overlap_coords.size() - 1));

              if (!MapUtils::adjacent_tiles_match_type(result_map, dig_coord, { Direction::DIRECTION_NORTH, Direction::DIRECTION_SOUTH }, TileType::TILE_TYPE_SEWER))
              {
                Log::instance().error("Bad sewer connection!");
              }

              TilePtr connector = tg.generate(TileType::TILE_TYPE_SEWER);
              result_map->insert(dig_coord, connector);
            }
          }
        }
      }
    }
  }
}