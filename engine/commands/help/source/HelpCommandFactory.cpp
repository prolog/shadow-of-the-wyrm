#include "HelpCommandFactory.hpp"
#include "HelpCommandKeys.hpp"
#include "HelpCommands.hpp"

HelpCommandFactory::HelpCommandFactory()
{
}

HelpCommandFactory::~HelpCommandFactory()
{
}

CommandPtr HelpCommandFactory::create(const int key, const std::string& command_name)
{
  CommandPtr command;

  if (command_name == HelpCommandKeys::KEYBINDINGS)
  {
    command = std::make_shared<KeybindingsCommand>(key);
  }
  else if (command_name == HelpCommandKeys::EXIT_HELP)
  {
    command = std::make_shared<ExitHelpCommand>(key);
  }

  return command;
}

CommandFactoryType HelpCommandFactory::get_factory_type() const
{
  return CommandFactoryType::COMMAND_FACTORY_TYPE_HELP;
}

CommandFactory* HelpCommandFactory::clone()
{
  return new CommandFactory(*this);
}

ClassIdentifier HelpCommandFactory::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_HELP_COMMAND_FACTORY;
}

#ifdef UNIT_TESTS
#include "unit_tests/HelpCommandFactory_test.cpp"
#endif