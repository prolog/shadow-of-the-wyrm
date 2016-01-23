#include "DeityTextKeys.hpp"
#include "DoNothingDeityDecisionStrategyHandler.hpp"

using std::string;

DoNothingDeityDecisionStrategyHandler::DoNothingDeityDecisionStrategyHandler(const string& new_deity_id)
: DeityDecisionStrategyHandler(new_deity_id)
{
}

bool DoNothingDeityDecisionStrategyHandler::decide(CreaturePtr creature)
{
  return true;
}

DeityDecisionImplications DoNothingDeityDecisionStrategyHandler::handle_decision(CreaturePtr creature, TilePtr tile)
{
  return get_deity_decision_implications(creature, tile);
}

// You can't nag 'em forever.
int DoNothingDeityDecisionStrategyHandler::get_piety_loss() const
{
  return 100;
}

string DoNothingDeityDecisionStrategyHandler::get_message_sid() const
{
  string message_sid = DeityTextKeys::PRAYER_DO_NOTHING;
  return message_sid;
}
