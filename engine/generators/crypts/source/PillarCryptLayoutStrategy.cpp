#include "PillarCryptLayoutStrategy.hpp"
#include "RNG.hpp"
#include "PillarGeneratorFactory.hpp"

using namespace std;

void PillarCryptLayoutStrategy::create_layout(MapPtr map, const tuple<Coordinate, Coordinate, Coordinate>& stair_loc_and_room_boundary)
{
  // Select a pillar type.
  PillarType pt = static_cast<PillarType>(RNG::range_endexclusive(PILLAR_TYPE_SQUARE, PILLAR_TYPE_LAST));
  IPillarGeneratorPtr p_gen = PillarGeneratorFactory::create_generator(pt);

  if (p_gen != nullptr)
  {
    int height = p_gen->get_height();
    int width = p_gen->get_width();

    // Apply the pillar generator regularly over the map to create a
    // characteristic "pillared" layout.
    //
    // ...
  }
}

