#include "PillarCryptLayoutStrategy.hpp"
#include "RNG.hpp"
#include "PillarGeneratorFactory.hpp"

using namespace std;

void PillarCryptLayoutStrategy::create_layout(MapPtr map, const tuple<Coordinate, Coordinate, Coordinate>& stair_loc_and_room_boundary)
{
  // Select a pillar type.
  PillarType pt = static_cast<PillarType>(RNG::range(static_cast<int>(PillarType::PILLAR_TYPE_SQUARE), static_cast<int>(PillarType::PILLAR_TYPE_LAST)-1));
  IPillarGeneratorPtr p_gen = PillarGeneratorFactory::create_generator(pt);

  if (p_gen != nullptr)
  {
    Coordinate top_left = std::get<1>(stair_loc_and_room_boundary);
    Coordinate bottom_right = std::get<2>(stair_loc_and_room_boundary);

    int p_height = p_gen->get_height();
    int p_width = p_gen->get_width();

    // Apply the pillar generator regularly over the map to create a
    // characteristic "pillared" layout.

    // First, ensure that the pillars don't appear around the edges
    // of the room.
    int start_y = top_left.first + 1;
    int start_x = top_left.second + 1;
    int end_y = bottom_right.first - 1;
    int end_x = bottom_right.second - 1;

    // Create an offset so that there's enough room for the player to 
    // move around.
    int row_offset = 1;
    int col_offset = 1;

    for (int row = start_y; row <= end_y; row += p_height + row_offset)
    {
      for (int col = start_x; col <= end_x; col += p_width + col_offset)
      {
        // If the current pillar doesn't violated height and width constraints,
        // add it to the crypt.
        if ((row + p_height <= end_y) && (col + p_width <= end_x))
        {
          p_gen->generate(map, row, col);
        }
      }
    }
  }
}

