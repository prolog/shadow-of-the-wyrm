#include "TargetSelfShapeProcessor.hpp"

using namespace std;

// Ignore the direction provided, and just target the starting coordinates.
pair<vector<pair<Coordinate, TilePtr>>, Animation> TargetSelfShapeProcessor::get_affected_tiles_and_animation_for_spell(MapPtr map, const Coordinate& caster_coord, const Direction /*d*/, const Spell& /*spell*/)
{
  vector<pair<Coordinate, TilePtr>> affected_coords_and_tiles;
  Animation animation; // No animation for self-targetted spells.

  TilePtr caster_tile = map->at(caster_coord);
  affected_coords_and_tiles.push_back(make_pair(caster_coord, caster_tile));

  std::pair<std::vector<std::pair<Coordinate, TilePtr>>, Animation> tiles_and_animation(affected_coords_and_tiles, animation);
  return tiles_and_animation;
}

