#pragma once
#include "ISpellFailureConsequences.hpp"

class MarginalSpellFailureConsequences : public ISpellFailureConsequences
{
  public:
    // Each of these functions does nothing.
    void damage_caster(CreaturePtr caster);
    void inflict_status_ailments(CreaturePtr caster);
    void summon_creatures(CreaturePtr caster);
};

