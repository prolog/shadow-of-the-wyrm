#include "DeityTextKeys.hpp"
#include "DoNothingDeityDecisionStrategyHandler.hpp"

using std::string;

bool DoNothingDeityDecisionStrategyHandler::decide(CreaturePtr creature)
{
  return true;
}

DeityDecisionImplications DoNothingDeityDecisionStrategyHandler::handle_decision(CreaturePtr creature)
{
  return get_deity_decision_implications();
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
