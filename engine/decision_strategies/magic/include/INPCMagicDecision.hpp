#pragma once
#include <memory>
#include "Creature.hpp"
#include "Directions.hpp"
#include "Map.hpp"
#include "Spell.hpp"

class INPCMagicDecision
{
  public:
    virtual ~INPCMagicDecision() {};
    virtual std::pair<bool, Direction> decide(CreaturePtr caster, MapPtr view_map, const Spell& spell, const std::set<std::string>& creature_threats) const = 0;
};

using INPCMagicDecisionPtr = std::shared_ptr<INPCMagicDecision>;

