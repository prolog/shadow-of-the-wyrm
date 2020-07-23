#include "OrderCommands.hpp"
#include "OrderCommandKeys.hpp"

OrderAttackCommand::OrderAttackCommand(const int key)
: Command(OrderCommandKeys::ATTACK, key)
{
}

OrderFollowCommand::OrderFollowCommand(const int key)
: Command(OrderCommandKeys::FOLLOW, key)
{
}

OrderGuardCommand::OrderGuardCommand(const int key)
: Command(OrderCommandKeys::GUARD, key)
{
}

OrderFreezeCommand::OrderFreezeCommand(const int key)
: Command(OrderCommandKeys::FREEZE, key)
{
}

OrderExitCommand::OrderExitCommand(const int key)
: Command(OrderCommandKeys::EXIT_ORDER, key)
{ 
}
