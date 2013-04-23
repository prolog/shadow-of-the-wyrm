#include "BeamShapeProcessor.hpp"
#include "CoordUtils.hpp"
#include "TileMagicChecker.hpp"

using namespace std;

vector<TilePtr> BeamShapeProcessor::get_affected_tiles_for_spell(MapPtr map, const Coordinate& caster_coord, const Direction d, const Spell& spell)
{
  vector<TilePtr> affected_tiles;
  uint range = spell.get_range();
  Coordinate current_coord = caster_coord;
  TileMagicChecker tmc;

  for (uint i = 0; i < range; i++)
  {
    Coordinate c = CoordUtils::get_new_coordinate(current_coord, d);
    TilePtr tile = map->at(c);

    // Check to see if the tile blocks the spell.
    if (tmc.does_tile_block_spell(tile))
    {
      break;
    }

    // Update the current coordinate in the beam, and add the tile to the
    // list of affected tiles.
    current_coord = c;
    affected_tiles.push_back(tile);
  }

  return affected_tiles;
}

