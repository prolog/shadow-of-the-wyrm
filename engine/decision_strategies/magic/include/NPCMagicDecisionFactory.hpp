#pragma once
#include "INPCMagicDecision.hpp"
#include "SpellTypes.hpp"

class NPCMagicDecisionFactory
{
  public:
    static INPCMagicDecisionPtr create_npc_magic_decision(const MagicClassification mc);
};

