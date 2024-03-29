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
    command = std::make_unique<SelectSpellCommand>(key - 'a', key);
  }
  else if (command_name == MagicCommandKeys::ARCANA)
  {
    command = std::make_unique<ArcanaCommand>(key - 'a', key);
  }
  else if (command_name == MagicCommandKeys::NEXT_PAGE)
  {
    command = std::make_unique<NextPageMagicCommand>(key);
  }
  else if (command_name == MagicCommandKeys::PREVIOUS_PAGE)
  {
    command = std::make_unique<PreviousPageMagicCommand>(key);
  }
  else if (command_name == MagicCommandKeys::EXIT_MAGIC)
  {
    command = std::make_unique<ExitMagicCommand>(key);
  }

  return command;
}

CommandFactoryType MagicCommandFactory::get_factory_type() const
{
  return CommandFactoryType::COMMAND_FACTORY_TYPE_MAGIC;
}

CommandFactory* MagicCommandFactory::clone()
{
  return new CommandFactory(*this);
}

ClassIdentifier MagicCommandFactory::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_MAGIC_COMMAND_FACTORY;
}

#ifdef UNIT_TESTS
#include "unit_tests/MagicCommandFactory_test.cpp"
#endif