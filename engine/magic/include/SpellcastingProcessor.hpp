#pragma once
#include "SpellShapeProcessor.hpp"

// A common class for processing a spell, whether by direct-cast, a wand,
// etc.
class SpellcastingProcessor
{
  public:
    // Returns true if the spell was identified as a result of casting it.
    bool process(SpellShapeProcessorPtr spell_processor, CreaturePtr caster, MapPtr current_map, const Coordinate& caster_coord, const Direction spell_direction, const Spell& spell, const ItemStatus effect_status) const;
};

