#include "OrderAction.hpp"
#include "OrderCommandKeys.hpp"
#include "OrderCommandProcessor.hpp"
#include "OrderCommands.hpp"

using namespace std;

OrderCommandProcessor::OrderCommandProcessor()
{
}

OrderCommandProcessor::~OrderCommandProcessor()
{
}

ActionCostValue OrderCommandProcessor::process(CreaturePtr creature, Command* command, const string& follower_ids)
{
  ActionCostValue process_result = ActionCostConstants::NO_ACTION;
  OrderAction oa;

  if (creature && command)
  {
    string command_name = command->get_name();

    if (command_name == OrderCommandKeys::ATTACK)
    {
      return oa.order_attack(creature, follower_ids);
    }
    else if (command_name == OrderCommandKeys::EXIT_ORDER)
    {
      process_result = -1;
    }
    else if (command_name == OrderCommandKeys::FOLLOW)
    {
      return oa.order_follow(creature, follower_ids);
    }
    else if (command_name == OrderCommandKeys::FREEZE)
    {
      return oa.order_freeze(creature, follower_ids);
    }
    else if (command_name == OrderCommandKeys::AT_EASE)
    {
      return oa.order_at_ease(creature, follower_ids);
    }
    else if (command_name == OrderCommandKeys::SUMMON)
    {
      return oa.order_summon(creature, follower_ids);
    }
  }

  return process_result;
}
