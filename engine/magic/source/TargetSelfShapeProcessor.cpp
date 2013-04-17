#include "TargetSelfShapeProcessor.hpp"

using namespace std;

// Ignore the direction provided, and just target the starting coordinates.
vector<TilePtr> TargetSelfShapeProcessor::get_affected_tiles_for_spell(MapPtr map, const Coordinate& caster_coord, const Direction d, const Spell& spell)
{
  vector<TilePtr> affected_tiles;

  TilePtr caster_tile = map->at(caster_coord);
  affected_tiles.push_back(caster_tile);

  return affected_tiles;
}

