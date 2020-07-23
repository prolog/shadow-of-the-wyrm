#include "OrderCommandFactory.hpp"
//#include "OrderCommandKeys.hpp"
//#include "OrderCommands.hpp"

OrderCommandFactory::OrderCommandFactory()
{
}

OrderCommandFactory::~OrderCommandFactory()
{
}

CommandPtr OrderCommandFactory::create(const int key, const std::string& command_name)
{
  CommandPtr command;

/*  if (command_name == OrderCommandKeys::KEYBINDINGS)
  {
    command = std::make_unique<KeybindingsCommand>(key);
  }
  else if (command_name == OrderCommandKeys::EXIT_HELP)
  {
    command = std::make_unique<ExitOrderCommand>(key);
  }
  else if (command_name == OrderCommandKeys::INTRODUCTION_ROGUELIKES)
  {
    command = std::make_unique<IntroductionRoguelikesCommand>(key);
  }
  else if (command_name == OrderCommandKeys::SOTW_HISTORY)
  {
    command = std::make_unique<SOTWHistoryCommand>(key);
  }
  else if (command_name == OrderCommandKeys::STRATEGY_BASICS)
  {
    command = std::make_unique<StrategyBasicsCommand>(key);
  }
  else if (command_name == OrderCommandKeys::CASINO_GAMES)
  {
    command = std::make_unique<CasinoGamesCommand>(key);
  } */

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