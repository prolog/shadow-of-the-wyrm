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

OrderFreezeCommand::OrderFreezeCommand(const int key)
: Command(OrderCommandKeys::FREEZE, key)
{
}

OrderAtEaseCommand::OrderAtEaseCommand(const int key)
: Command(OrderCommandKeys::AT_EASE, key)
{
}

OrderSummonCommand::OrderSummonCommand(const int key)
: Command(OrderCommandKeys::SUMMON, key)
{
}

OrderExitCommand::OrderExitCommand(const int key)
: Command(OrderCommandKeys::EXIT_ORDER, key)
{ 
}
