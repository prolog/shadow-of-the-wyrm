#include "OrderCommandFactory.hpp"
#include "OrderCommandKeys.hpp"
#include "OrderCommands.hpp"

OrderCommandFactory::OrderCommandFactory()
{
}

OrderCommandFactory::~OrderCommandFactory()
{
}

CommandPtr OrderCommandFactory::create(const int key, const std::string& command_name)
{
  CommandPtr command;

  if (command_name == OrderCommandKeys::ATTACK)
  {
    command = std::make_unique<OrderAttackCommand>(key);
  }
  else if (command_name == OrderCommandKeys::FOLLOW)
  {
    command = std::make_unique<OrderFollowCommand>(key);
  }
  else if (command_name == OrderCommandKeys::FREEZE)
  {
    command = std::make_unique<OrderFreezeCommand>(key);
  }
  else if (command_name == OrderCommandKeys::AT_EASE)
  {
    command = std::make_unique<OrderAtEaseCommand>(key);
  }
  else if (command_name == OrderCommandKeys::EXIT_ORDER)
  {
    command = std::make_unique<OrderExitCommand>(key);
  }

  return command;
}

CommandFactoryType OrderCommandFactory::get_factory_type() const
{
  return CommandFactoryType::COMMAND_FACTORY_TYPE_ORDER;
}

CommandFactory* OrderCommandFactory::clone()
{
  return new CommandFactory(*this);
}

ClassIdentifier OrderCommandFactory::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_ORDER_COMMAND_FACTORY;
}

#ifdef UNIT_TESTS
#include "unit_tests/OrderCommandFactory_test.cpp"
#endif 