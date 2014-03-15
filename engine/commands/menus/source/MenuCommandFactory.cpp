#include "MenuCommandFactory.hpp"
#include "MenuCommandKeys.hpp"
#include "MenuCommands.hpp"

MenuCommandFactory::MenuCommandFactory()
{
}

MenuCommandFactory::~MenuCommandFactory()
{
}

CommandPtr MenuCommandFactory::create(const int key, const std::string& command_name)
{
  CommandPtr command;

  if (command_name == MenuCommandKeys::NEXT_PAGE)
  {
    command = std::make_shared<NextPageMenuCommand>(key);
  }
  else if (command_name == MenuCommandKeys::PREVIOUS_PAGE)
  {
    command = std::make_shared<PreviousPageMenuCommand>(key);
  }

  return command;
}

CommandFactoryType MenuCommandFactory::get_factory_type() const
{
  return COMMAND_FACTORY_TYPE_MENU;
}

CommandFactory* MenuCommandFactory::clone()
{
  return new MenuCommandFactory(*this);
}

ClassIdentifier MenuCommandFactory::internal_class_identifier() const
{
  return CLASS_ID_MENU_COMMAND_FACTORY;
}

#ifdef UNIT_TESTS
#include "unit_tests/MenuCommandFactory_test.cpp"
#endif
