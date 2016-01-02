#pragma once
#include "INPCMagicDecision.hpp"

class AttackNPCMagicDecision : public INPCMagicDecision
{
  public:
    std::pair<bool, Direction> decide(CreaturePtr caster, MapPtr map, const Spell& spell, const std::set<std::string>& creature_threats) const override;
};

