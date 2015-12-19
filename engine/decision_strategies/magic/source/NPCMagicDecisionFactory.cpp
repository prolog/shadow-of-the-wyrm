#include "NPCMagicDecisionFactory.hpp"
#include "NullNPCMagicDecision.hpp"
#include "AttackNPCMagicDecision.hpp"
#include "HealingNPCMagicDecision.hpp"
#include "DefaultNPCMagicDecision.hpp"

using namespace std;

INPCMagicDecisionPtr NPCMagicDecisionFactory::create_npc_magic_decision(const MagicClassification mc)
{
  INPCMagicDecisionPtr decide = make_shared<NullNPCMagicDecision>();

  switch(mc)
  {
    case MagicClassification::MAGIC_CLASSIFICATION_ATTACK:
      decide = make_shared<AttackNPCMagicDecision>();
      break;
    case MagicClassification::MAGIC_CLASSIFICATION_HEALING:
      decide = make_shared<HealingNPCMagicDecision>();
      break;
    case MagicClassification::MAGIC_CLASSIFICATION_BUFF:
    case MagicClassification::MAGIC_CLASSIFICATION_UTILITY:
      decide = make_shared<DefaultNPCMagicDecision>();
      break;
    case MagicClassification::MAGIC_CLASSIFICATION_UNDEFINED:
      decide = make_shared<NullNPCMagicDecision>();
      break;
  }

  return decide;
}

