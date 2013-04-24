#include "TargetSelfShapeProcessor.hpp"

using namespace std;

// Ignore the direction provided, and just target the starting coordinates.
vector<pair<Coordinate, TilePtr> > TargetSelfShapeProcessor::get_affected_tiles_for_spell(MapPtr map, const Coordinate& caster_coord, const Direction d, const Spell& spell)
{
  vector<pair<Coordinate, TilePtr> > affected_tiles;

  TilePtr caster_tile = map->at(caster_coord);
  affected_tiles.push_back(make_pair(caster_coord, caster_tile));

  return affected_tiles;
}

