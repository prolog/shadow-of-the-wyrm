#include "DeityTextKeys.hpp"
#include "DoNothingDeityDecisionStrategyHandler.hpp"

using std::string;

const int DoNothingDeityDecisionStrategyHandler::DO_NOTHING_PIETY_LOSS = 100;

bool DoNothingDeityDecisionStrategyHandler::decide(CreaturePtr creature)
{
  return true;
}

DeityDecisionImplications DoNothingDeityDecisionStrategyHandler::handle_decision(CreaturePtr creature)
{
  return get_deity_decision_implications();
}

int DoNothingDeityDecisionStrategyHandler::get_piety_loss() const
{
  return DO_NOTHING_PIETY_LOSS;
}

string DoNothingDeityDecisionStrategyHandler::get_message_sid() const
{
  string message_sid = DeityTextKeys::PRAYER_DO_NOTHING;
  return message_sid;
}
