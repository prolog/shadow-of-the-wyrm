#include <boost/make_shared.hpp>
#include "MagicCommandFactory.hpp"
#include "MagicCommandKeys.hpp"
#include "MagicCommands.hpp"

MagicCommandFactory::MagicCommandFactory()
{
}

MagicCommandFactory::~MagicCommandFactory()
{
}

CommandPtr MagicCommandFactory::create(const int key, const std::string& command_name)
{
  CommandPtr command;

  if (command_name == MagicCommandKeys::SELECT_SPELL)
  {
    command = boost::make_shared<SelectSpellCommand>();
  }
  else if (command_name == MagicCommandKeys::NEXT_PAGE)
  {
    command = boost::make_shared<NextPageMagicCommand>();
  }
  else if (command_name == MagicCommandKeys::PREVIOUS_PAGE)
  {
    command = boost::make_shared<PreviousPageMagicCommand>();
  }
  else if (command_name == MagicCommandKeys::EXIT_MAGIC)
  {
    command = boost::make_shared<ExitMagicCommand>();
  }

  return command;
}

CommandFactoryType MagicCommandFactory::get_factory_type() const
{
  return COMMAND_FACTORY_TYPE_MAGIC;
}

CommandFactory* MagicCommandFactory::clone()
{
  return new CommandFactory(*this);
}

ClassIdentifier MagicCommandFactory::internal_class_identifier() const
{
  return CLASS_ID_MAGIC_COMMAND_FACTORY;
}

#ifdef UNIT_TESTS
#include "unit_tests/MagicCommandFactory_test.cpp"
#endif