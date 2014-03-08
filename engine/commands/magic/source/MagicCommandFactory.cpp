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
    command = std::make_shared<SelectSpellCommand>(key - 'a', key);
  }
  else if (command_name == MagicCommandKeys::NEXT_PAGE)
  {
    command = std::make_shared<NextPageMagicCommand>(key);
  }
  else if (command_name == MagicCommandKeys::PREVIOUS_PAGE)
  {
    command = std::make_shared<PreviousPageMagicCommand>(key);
  }
  else if (command_name == MagicCommandKeys::EXIT_MAGIC)
  {
    command = std::make_shared<ExitMagicCommand>(key);
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