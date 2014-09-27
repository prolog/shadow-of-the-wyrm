#include "DislikeDeityDecisionStrategyHandler.hpp"
#include "DeityTextKeys.hpp"

using std::string;

DislikeDeityDecisionStrategyHandler::DislikeDeityDecisionStrategyHandler()
{
}

DislikeDeityDecisionStrategyHandler::DislikeDeityDecisionStrategyHandler(DeityPtr new_deity)
: deity(new_deity)
{
}

// The Nine only dislike those with negative piety.
//
// They're very scientific, and it makes it easy to model.
bool DislikeDeityDecisionStrategyHandler::decide(CreaturePtr creature)
{
  bool decision = false;

  if (creature)
  {
    Religion& religion = creature->get_religion_ref();
    DeityRelations& relations = religion.get_deity_relations_ref();
    DeityStatus& status = relations[religion.get_active_deity_id()];
    
    decision = (status.get_piety() < 0);
  }

  return decision;
}

DeityDecisionImplications DislikeDeityDecisionStrategyHandler::handle_decision(CreaturePtr creature, TilePtr tile)
{
  return get_deity_decision_implications(creature, tile);
}

int DislikeDeityDecisionStrategyHandler::get_piety_loss() const
{
  return 750;
}

string DislikeDeityDecisionStrategyHandler::get_message_sid() const
{
  if (deity != nullptr)
  {
    return deity->get_anger_message_sid();
  }
  else
  {
    return DeityTextKeys::DEITY_ACTION_DISPLEASED;
  }
}

