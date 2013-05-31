#pragma once
#include "Spell.hpp"

// A class for creating spells set up for certain tasks (e.g., for creating
// temporary spells to be used by potions/scrolls, etc.)
class SpellFactory
{
  public:
    // Create a self-targetted spell that does not allow the bonus to be
    // used.
    static Spell create_self_targetted_item_spell();

  protected:
    SpellFactory();
};

