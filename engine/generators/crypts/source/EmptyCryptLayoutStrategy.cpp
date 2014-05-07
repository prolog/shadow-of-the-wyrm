#include "CoordUtils.hpp"
#include "EmptyCryptLayoutStrategy.hpp"
#include "OrderedGraveyardGenerator.hpp"
#include "RNG.hpp"

using namespace std;

void EmptyCryptLayoutStrategy::create_layout(MapPtr map, const tuple<Coordinate, Coordinate, Coordinate>& stair_loc_and_room_boundary)
{
  // 50% chance of graves within the crypt
  if (RNG::percent_chance(50))
  { 
    Coordinate top_left = std::get<1>(stair_loc_and_room_boundary);
    Coordinate bottom_right = std::get<2>(stair_loc_and_room_boundary);

    // Adjust top-left and bottom-right for the graves:
    top_left.first +=1;
    top_left.second +=1;
    bottom_right.first -= 1;
    bottom_right.second -= 1;

    OrderedGraveyardGenerator ogg(map->get_map_id());
    ogg.add_graves(map, top_left.first, bottom_right.first, top_left.second, bottom_right.second);
  }
}

