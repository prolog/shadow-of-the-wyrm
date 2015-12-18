#pragma once
#include "INPCMagicDecision.hpp"

class AttackNPCMagicDecision : public INPCMagicDecision
{
  public:
    bool decide(CreaturePtr caster, MapPtr map, const Spell& spell) const override;
};

