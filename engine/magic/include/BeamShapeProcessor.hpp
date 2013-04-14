#pragma once
#include "ISpellShapeProcessor.hpp"

// A class for processing beam-type spells.
class BeamShapeProcessor : public ISpellShapeProcessor
{
  public:
    void process(MapPtr map, const Coordinate& caster_coord, const Direction d, const Spell& spell);
};

