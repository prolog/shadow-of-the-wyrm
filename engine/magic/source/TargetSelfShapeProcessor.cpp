#include "TargetSelfShapeProcessor.hpp"

using namespace std;

// Ignore the direction provided, and just target the starting coordinates.
pair<vector<TilePtr>, Animation> TargetSelfShapeProcessor::get_affected_tiles_and_animation_for_spell(MapPtr map, const Coordinate& caster_coord, const Direction d, const Spell& spell)
{
  vector<TilePtr> affected_tiles;
  Animation animation; // No animation for self-targetted spells.

  TilePtr caster_tile = map->at(caster_coord);
  affected_tiles.push_back(caster_tile);

  std::pair<std::vector<TilePtr>, Animation> tiles_and_animation(affected_tiles, animation);
  return tiles_and_animation;
}

