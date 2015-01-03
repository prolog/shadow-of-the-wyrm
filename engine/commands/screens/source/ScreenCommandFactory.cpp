#include "ScreenCommandFactory.hpp"
#include "ScreenCommandKeys.hpp"
#include "ScreenCommands.hpp"

ScreenCommandFactory::ScreenCommandFactory()
{
}

ScreenCommandFactory::~ScreenCommandFactory()
{
}

CommandPtr ScreenCommandFactory::create(const int key, const std::string& command_name)
{
  CommandPtr command;

  if (command_name == ScreenCommandKeys::NEXT_PAGE)
  {
    command = std::make_shared<NextPageScreenCommand>(key);
  }
  else if (command_name == ScreenCommandKeys::PREVIOUS_PAGE)
  {
    command = std::make_shared<PreviousPageScreenCommand>(key);
  }

  return command;
}

CommandFactoryType ScreenCommandFactory::get_factory_type() const
{
  return CommandFactoryType::COMMAND_FACTORY_TYPE_SCREEN;
}

CommandFactory* ScreenCommandFactory::clone()
{
  return new ScreenCommandFactory(*this);
}

ClassIdentifier ScreenCommandFactory::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SCREEN_COMMAND_FACTORY;
}

#ifdef UNIT_TESTS
#include "unit_tests/ScreenCommandFactory_test.cpp"
#endif
