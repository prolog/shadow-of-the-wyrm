#pragma once
#include "INPCMagicDecision.hpp"

class DefaultNPCMagicDecision : public INPCMagicDecision
{
  public:
    std::pair<bool, Direction> decide(CreaturePtr caster, MapPtr view_map, const Spell& spell, const std::set<std::string>& creature_threats) const override;

  protected:
    static const int PCT_CHANCE_CAST_WHILE_UNDER_THREAT;
};

