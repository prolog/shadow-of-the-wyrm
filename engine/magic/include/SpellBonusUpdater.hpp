#pragma once
#include "IndividualSpellKnowledge.hpp"

class SpellBonusUpdater
{
  public:
    // Increment the "current" counter.  If the current then equals the
    // base, increment the base, reset the current to 0, and return true
    // so that the UI can be updated if necessary.
    bool add_successful_casting(IndividualSpellKnowledge& isk) const;
};

