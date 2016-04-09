#include "SkillsCommandFactory.hpp"
#include "SkillsCommandKeys.hpp"
#include "SkillsCommands.hpp"

SkillsCommandFactory::SkillsCommandFactory()
{
}

SkillsCommandFactory::~SkillsCommandFactory()
{
}

CommandPtr SkillsCommandFactory::create(const int key, const std::string& command_name)
{
  CommandPtr command;
  
  if (command_name == SkillsCommandKeys::GENERAL_SKILLS)
  {
    command = std::make_shared<GeneralSkillsCommand>(key);
  }
  else if (command_name == SkillsCommandKeys::MELEE_WEAPON_SKILLS)
  {
    command = std::make_shared<MeleeWeaponSkillsCommand>(key);
  }
  else if (command_name == SkillsCommandKeys::RANGED_WEAPON_SKILLS)
  {
    command = std::make_shared<RangedWeaponSkillsCommand>(key);
  }
  else if (command_name == SkillsCommandKeys::MAGIC_SKILLS)
  {
    command = std::make_shared<MagicSkillsCommand>(key);
  }
  else if (command_name == SkillsCommandKeys::SELECT_SKILL)
  {
    command = std::make_shared<SelectSkillCommand>(key);
  }
  else if (command_name == SkillsCommandKeys::EXIT_SKILLS)
  {
    command = std::make_shared<ExitSkillsCommand>(key);
  }

  return command;
}

CommandFactoryType SkillsCommandFactory::get_factory_type() const
{
  return CommandFactoryType::COMMAND_FACTORY_TYPE_HELP;
}

CommandFactory* SkillsCommandFactory::clone()
{
  return new CommandFactory(*this);
}

ClassIdentifier SkillsCommandFactory::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILLS_COMMAND_FACTORY;
}

#ifdef UNIT_TESTS
#include "unit_tests/SkillsCommandFactory_test.cpp"
#endif
