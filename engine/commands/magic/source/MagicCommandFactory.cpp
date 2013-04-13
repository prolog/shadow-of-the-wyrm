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
    // Store the pressed key.  This will always be a letter for spells,
    // so subtracting 'a' gets us the numeric index that the map uses
    // to look up the spell ID.
    command = boost::make_shared<SelectSpellCommand>(key - 'a');
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