#pragma once
#include "INPCMagicDecision.hpp"

class NullNPCMagicDecision : public INPCMagicDecision
{
  public:
    bool decide(CreaturePtr caster, MapPtr view_map, const Spell& spell) const override;
};

