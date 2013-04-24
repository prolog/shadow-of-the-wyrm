#pragma once
#include "SpellShapeProcessor.hpp"

// A class used to process the "target self" spell shape.
class TargetSelfShapeProcessor : public SpellShapeProcessor
{
  protected:
    virtual std::vector<std::pair<Coordinate, TilePtr> > get_affected_tiles_for_spell(MapPtr map, const Coordinate& caster_coord, const Direction d, const Spell& spell);
};

