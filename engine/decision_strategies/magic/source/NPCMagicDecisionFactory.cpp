#include "NPCMagicDecisionFactory.hpp"
#include "NullNPCMagicDecision.hpp"
#include "AttackNPCMagicDecision.hpp"
#include "HealingNPCMagicDecision.hpp"
#include "DefaultNPCMagicDecision.hpp"

using namespace std;

INPCMagicDecisionPtr NPCMagicDecisionFactory::create_npc_magic_decision(const MagicClassification mc)
{
  INPCMagicDecisionPtr decide = make_unique<NullNPCMagicDecision>();

  switch(mc)
  {
    case MagicClassification::MAGIC_CLASSIFICATION_ATTACK:
      decide = make_unique<AttackNPCMagicDecision>();
      break;
    case MagicClassification::MAGIC_CLASSIFICATION_HEALING:
      decide = make_unique<HealingNPCMagicDecision>();
      break;
    case MagicClassification::MAGIC_CLASSIFICATION_BUFF:
    case MagicClassification::MAGIC_CLASSIFICATION_UTILITY:
      decide = make_unique<DefaultNPCMagicDecision>();
      break;
    case MagicClassification::MAGIC_CLASSIFICATION_UNDEFINED:
      decide = make_unique<NullNPCMagicDecision>();
      break;
  }

  return decide;
}

