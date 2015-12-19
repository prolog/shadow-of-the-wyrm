#pragma once
#include "INPCMagicDecision.hpp"

class NullNPCMagicDecision : public INPCMagicDecision
{
  public:
    std::pair<bool, Direction> decide(CreaturePtr caster, MapPtr view_map, const Spell& spell, const std::set<std::string>& creature_threats) const override;
};

