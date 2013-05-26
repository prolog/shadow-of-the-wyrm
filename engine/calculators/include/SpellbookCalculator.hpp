#pragma once
#include "Creature.hpp"

// A class used to determine whether a creature learns a spell, based on
// the difficulty, the creature's skills and statistics, and other
// factors.
class SpellbookCalculator
{
  public:
    SpellbookCalculator();

    // The first member of the pair is whether the spell was learned; the second
    // is the difference between the random value (with creature factors) and the
    // spell's difficulty.
    std::pair<bool, int> learn_spell(CreaturePtr creature, const SkillType magic_category, const int difficulty);

    // After successfully learning a spell from the spellbook, get a random
    // number of castings based on the spellbook status and the difficulty.
    int get_num_castings(CreaturePtr creature, const SkillType magic_category, const ItemStatus spellbook_status, const int difficulty);

    // Determine whether the spellbook is destroyed after successfully learning
    // the spell.
    bool get_is_spellbook_destroyed(const ItemStatus spellbook_status);

  protected:
    void initialize_status_failure_levels();
    void initialize_status_casting_multipliers();

    std::map<ItemStatus, int> status_failure_levels;
    std::map<ItemStatus, float> status_casting_multipliers;
};

