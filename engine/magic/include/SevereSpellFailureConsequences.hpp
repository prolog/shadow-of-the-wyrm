#pragma once
#include "ISpellFailureConsequences.hpp"

class SevereSpellFailureConsequences : public ISpellFailureConsequences
{
  // Inflict heavy damage (80% of current)
  virtual void damage_caster(CreaturePtr caster);

  // Inflict dangerous (deadly within a few turns) status ailments such 
  // as stoning.
  virtual void inflict_status_ailments(CreaturePtr caster);

  // Summon deadliest undead, such as dracoliches, nightmares, etc.
  virtual void summon_creatures(CreaturePtr creature);
};

