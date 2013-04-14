#pragma once
#include <boost/shared_ptr.hpp>
#include "common.hpp"
#include "Directions.hpp"
#include "Map.hpp"
#include "Spell.hpp"

// An abstract class for representing shape processing in a particular
// direction.  As an example, a beam processor would handle iterating over
// the points north (or east, etc) for a particular range, applying the
// damage/effect to each tile, determining when to stop, etc.
class ISpellShapeProcessor
{
  public:
    virtual void process(MapPtr map, const Coordinate& caster_coord, const Direction d, const Spell& spell) = 0;
};

typedef boost::shared_ptr<ISpellShapeProcessor> ISpellShapeProcessorPtr;
