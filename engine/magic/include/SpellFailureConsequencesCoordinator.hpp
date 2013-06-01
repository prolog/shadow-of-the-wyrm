#pragma once
#include "Creature.hpp"
#include "SpellFailureConsequences.hpp"

// The SpellFailureConsequencesCoordinator creates an
// ISpellFailureConsequencesPtr based on the severity of the failure, as
// represented by the spell_learning_difference.  It then selects a
// consequence (damage, status ailments, or summoned creatures) based on
// a uniform probability distribution, and applies that consequence to
// the creature.
class SpellFailureConsequencesCoordinator
{
  public:
    // If this returns true, the spellbook is destroyed as a result of the
    // consequences.
    bool coordinate_failure_consequences(CreaturePtr caster, const int spell_learning_difference);

  protected:
    SpellFailureConsequencesPtr create_spell_failure_consequences(const int spell_failure_difference);
};

