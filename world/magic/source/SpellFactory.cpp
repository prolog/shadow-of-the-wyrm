#include "SpellFactory.hpp"
#include "SpellShapeFactory.hpp"

SpellFactory::SpellFactory()
{
}

// Create a spell with reasonable defaults for a self-targetted, item-based, temporary spell.
Spell SpellFactory::create_self_targetted_item_spell()
{
  Spell spell;

  spell.set_has_damage(false);
  spell.set_range(0);
  spell.set_shape(SpellShapeFactory::create_spell_shape(SPELL_SHAPE_TARGET_SELF));
  spell.set_allows_bonus(false);

  return spell;
}

