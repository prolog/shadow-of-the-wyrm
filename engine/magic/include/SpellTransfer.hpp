#pragma once
#include "Scroll.hpp"
#include "Spell.hpp"
#include "Potion.hpp"
#include "Wand.hpp"

// Used to transfer spell details from spells to player-created wands, scrolls,
// potions, and so on.
class SpellTransfer
{
  public:
    bool to_scroll(const Spell& spell, ScrollPtr scroll);
    bool to_potion(const Spell& spell, PotionPtr potion);
    bool to_wand(const Spell& spell, WandPtr wand);

  protected:
    bool to_item(const Spell& spell, ItemPtr item);
};