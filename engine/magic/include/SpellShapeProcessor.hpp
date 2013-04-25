#pragma once
#include <vector>
#include <boost/shared_ptr.hpp>
#include "Animation.hpp"
#include "common.hpp"
#include "Directions.hpp"
#include "Map.hpp"
#include "Spell.hpp"
#include "Tile.hpp"

class ActionManager;

// An abstract class for representing shape processing in a particular
// direction.  As an example, a beam processor would handle iterating over
// the points north (or east, etc) for a particular range, applying the
// damage/effect to each tile, determining when to stop, etc.
class SpellShapeProcessor
{
  public:
    virtual ~SpellShapeProcessor();

    // Pure virtual function to get the affected tiles for a particular spell.
    // This will be dependant on the shape: beams generate a line, balls are
    // centered on the caster, etc.
    virtual std::pair<std::vector<TilePtr>, Animation> get_affected_tiles_and_animation_for_spell(MapPtr map, const Coordinate& caster_coord, const Direction d, const Spell& spell) = 0;
    virtual void process_damage_and_effect(CreaturePtr caster, const std::vector<TilePtr>& affected_tiles, const Spell& spell, ActionManager * const am);

  protected:
    virtual void apply_damage_and_effect(CreaturePtr caster, const std::vector<TilePtr>& affected_tiles, const Spell& spell, ActionManager * const am);
    virtual void apply_damage(CreaturePtr caster, TilePtr tile, const Spell& spell, ActionManager * const am);
    virtual void apply_effect(CreaturePtr caster, TilePtr tile, const Spell& spell, ActionManager * const am);
};

typedef boost::shared_ptr<SpellShapeProcessor> SpellShapeProcessorPtr;
