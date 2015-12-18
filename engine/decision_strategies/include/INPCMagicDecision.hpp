#pragma once
#include <memory>
#include "Creature.hpp"
#include "Map.hpp"
#include "Spell.hpp"

class INPCMagicDecision
{
  public:
    virtual ~INPCMagicDecision() {};
    virtual bool decide(CreaturePtr caster, MapPtr view_map, const Spell& spell) const = 0;
};

using INPCMagicDecisionPtr = std::shared_ptr<INPCMagicDecision>;

