#include "SkillsCommands.hpp"
#include "SkillsCommandKeys.hpp"

using namespace std;

GeneralSkillsCommand::GeneralSkillsCommand(const int key)
: Command(SkillsCommandKeys::GENERAL_SKILLS, key)
{
}

MeleeWeaponSkillsCommand::MeleeWeaponSkillsCommand(const int key)
: Command(SkillsCommandKeys::MELEE_WEAPON_SKILLS, key)
{
}

RangedWeaponSkillsCommand::RangedWeaponSkillsCommand(const int key)
: Command(SkillsCommandKeys::RANGED_WEAPON_SKILLS, key)
{
}

MagicSkillsCommand::MagicSkillsCommand(const int key)
: Command(SkillsCommandKeys::MAGIC_SKILLS, key)
{
}

SelectSkillCommand::SelectSkillCommand(const int key)
: Command(SkillsCommandKeys::SELECT_SKILL, key)
{
}

ExitSkillsCommand::ExitSkillsCommand(const int key)
  : Command(SkillsCommandKeys::EXIT_SKILLS, key)
{
}
