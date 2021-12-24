#include "Game.hpp"
#include "Setting.hpp"
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
    command = std::make_unique<GeneralSkillsCommand>(key);
  }
  else if (command_name == SkillsCommandKeys::MELEE_WEAPON_SKILLS)
  {
    command = std::make_unique<MeleeWeaponSkillsCommand>(key);
  }
  else if (command_name == SkillsCommandKeys::RANGED_WEAPON_SKILLS)
  {
    command = std::make_unique<RangedWeaponSkillsCommand>(key);
  }
  else if (command_name == SkillsCommandKeys::MAGIC_SKILLS)
  {
    command = std::make_unique<MagicSkillsCommand>(key);
  }
  else if (command_name == SkillsCommandKeys::SELECT_SKILL)
  {
    command = std::make_unique<SelectSkillCommand>(key);
  }
  else if (command_name == SkillsCommandKeys::SKILL_DESCRIPTION)
  {
    command = std::make_unique<DescribeSkillCommand>(key);
  }
  else if (command_name == SkillsCommandKeys::EXIT_SKILLS)
  {
    command = std::make_unique<ExitSkillsCommand>(key);
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
