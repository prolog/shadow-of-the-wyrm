#include "XRoomGenerator.hpp"
#include "BasicRoomGenerator.hpp"
#include "TileGenerator.hpp"

using namespace std;

// Generate a room with X-shaped walls meeting at the center.
void XRoomGenerator::generate(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col)
{
  // First, generate the room.
  IRoomGeneratorPtr brg = std::make_shared<BasicRoomGenerator>();
  brg->generate(map, start_row, end_row, start_col, end_col);

  generate_x(map, start_row, end_row, start_col, end_col);
}

// Generate the initial "X" of walls
void XRoomGenerator::generate_x(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col)
{
  TileGenerator tg;

  int xr_1 = start_row;
  int xr_2 = end_row - 1;
  int xc_1 = start_col;
  int xc_2 = end_col - 1;
  TilePtr rock_tile;

  while (xr_1 <= xr_2)
  {
    set<Coordinate> coords = { { xr_1, xc_1 }, { xr_1, xc_2 }, { xr_2, xc_1 }, { xr_2, xc_2 } };

    for (const Coordinate& coord : coords)
    {
      rock_tile = tg.generate(TileType::TILE_TYPE_ROCK);
      map->insert(coord.first, coord.second, rock_tile);
    }

    // Ensure there's enough room for creatures to move.
    // Also ensure the basic "X" shape is maintained.
    if (xc_1 < end_col && xc_2 > start_col && (xc_1 < (xc_2 - 1)))
    {
      xc_1++;
      xc_2--;
    }

    // Next pair of rows.
    xr_1++;
    xr_2--;
  }
}

