#pragma once
#include "SpellShapeProcessor.hpp"

class ConeShapeProcessor : public SpellShapeProcessor
{
  public:
    virtual std::pair<std::vector<TilePtr>, Animation> get_affected_tiles_and_animation_for_spell(MapPtr map, const Coordinate& caster_coord, const Direction d, const Spell& spell);
};
