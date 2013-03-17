#include "DislikeDeityDecisionStrategyHandler.hpp"
#include "StringConstants.hpp"

using std::string;

const int DislikeDeityDecisionStrategyHandler::PIETY_LOSS = 750;

DeityDecisionImplications DislikeDeityDecisionStrategyHandler::handle_decision(CreaturePtr creature)
{
  if (creature)
  {
    Religion& religion = creature->get_religion_ref();
    DeityRelations& relations = religion.get_deity_relations_ref();
    DeityStatus& status = relations[religion.get_active_deity_id()];

    // Reduce the creature's piety.
    int original_piety = status.get_piety();
    int new_piety = original_piety - PIETY_LOSS;

    status.set_piety(new_piety);
  }

  return get_deity_decision_implications();
}

int DislikeDeityDecisionStrategyHandler::get_piety_loss() const
{
  return PIETY_LOSS;
}

string DislikeDeityDecisionStrategyHandler::get_message_sid() const
{
  return DeityTextKeys::DEITY_ACTION_DISPLEASED;
}

