#include <boost/foreach.hpp>
#include "ActionManager.hpp"
#include "CombatManager.hpp"
#include "EffectFactory.hpp"
#include "SpellShapeProcessor.hpp"

using namespace std;

SpellShapeProcessor::~SpellShapeProcessor()
{
}

// Process the shape.  This is done by generating all the affected tiles,
// and then applying damage and spell effects to each.
void SpellShapeProcessor::process(CreaturePtr caster, MapPtr map, const Coordinate& caster_coord, const Direction d, const Spell& spell, ActionManager * const am)
{
  // Call out to the implementing class's function to get the tiles in the correct order.
  vector<TilePtr> affected_tiles = get_affected_tiles_for_spell(map, caster_coord, d, spell);

  // Apply the spell's damage/effect to the tiles in order.
  apply_damage_and_effect(caster, affected_tiles, spell, am);
}

// Apply a spell to a particular tile by applying its damage and spell effect.
void SpellShapeProcessor::apply_damage_and_effect(CreaturePtr caster, const vector<TilePtr>& affected_tiles, const Spell& spell, ActionManager * const am)
{
  BOOST_FOREACH(TilePtr tile, affected_tiles)
  {
    apply_damage(caster, tile, spell, am);
    apply_effect(caster, tile, spell, am);
  }
}

// Apply a spell's damage to a particular tile.
void SpellShapeProcessor::apply_damage(CreaturePtr caster, TilePtr tile, const Spell& spell, ActionManager * const am)
{
  CreaturePtr tile_creature = tile->get_creature();
  if (tile && spell.get_has_damage() && tile_creature)
  {
    CombatManager cm;
    DamagePtr damage = boost::make_shared<Damage>(spell.get_damage());
    cm.attack(caster, tile_creature, ATTACK_TYPE_MAGICAL, damage);
  }
}

// Apply a spell effect to a particular tile.
void SpellShapeProcessor::apply_effect(CreaturePtr caster, TilePtr tile, const Spell& spell, ActionManager * const am)
{
  if (tile)
  {
    EffectType effect_type = spell.get_effect();

    EffectPtr effect = EffectFactory::create_effect(effect_type);
    CreaturePtr creature = tile->get_creature();

    if (effect && creature)
    {
      effect->effect(creature, am, ITEM_STATUS_UNCURSED);
    }
  }
}
