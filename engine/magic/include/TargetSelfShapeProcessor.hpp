#pragma once
#include "ISpellShapeProcessor.hpp"

// A class used to process the "target self" spell shape.
class TargetSelfShapeProcessor : public ISpellShapeProcessor
{
  public:
    void process(MapPtr map, const Coordinate& caster_coord, const Direction d, const Spell& spell);
};

