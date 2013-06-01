#pragma once
#include "ISpellFailureConsequences.hpp"

class SpellFailureConsequences : public ISpellFailureConsequences
{
  // Inflict mild damage (2d6ish)
  virtual void damage_caster(CreaturePtr caster);

  // Inflict lesser status ailments, such as slowness, poison, etc.
  virtual void inflict_status_ailments(CreaturePtr caster);

  // Summon lesser undead, such as thralls, skeletons, ghouls, etc.
  virtual void summon_creatures(CreaturePtr creature);
};

