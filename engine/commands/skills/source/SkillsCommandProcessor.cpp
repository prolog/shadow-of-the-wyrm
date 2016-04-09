#include "Game.hpp"
#include "ShowSkillsAction.hpp"
#include "SkillsCommandKeys.hpp"
#include "SkillsCommandProcessor.hpp"
#include "SkillsCommands.hpp"

using namespace std;

SkillsCommandProcessor::SkillsCommandProcessor()
{
}

SkillsCommandProcessor::~SkillsCommandProcessor()
{
}

ActionCostValue SkillsCommandProcessor::process(CreaturePtr creature, CommandPtr command)
{
  ActionCostValue process_result = 1;
  Game& game = Game::instance();
  ShowSkillsAction& ssa = game.get_action_manager_ref().get_show_skills_action_ref();

  if (creature && command)
  {
    string command_name = command->get_name();

    if (command_name == SkillsCommandKeys::GENERAL_SKILLS)
    {
      return ssa.show_general_skills(creature);
    }
    else if (command_name == SkillsCommandKeys::MELEE_WEAPON_SKILLS)
    {
      return ssa.show_melee_weapon_skills(creature);
    }
    else if (command_name == SkillsCommandKeys::RANGED_WEAPON_SKILLS)
    {
      return ssa.show_ranged_weapon_skills(creature);
    }
    else if (command_name == SkillsCommandKeys::MAGIC_SKILLS)
    {
      return ssa.show_magic_skills(creature);
    }
    else if (command_name == SkillsCommandKeys::SELECT_SKILL)
    {
      // JCD FIXME
      int x = 1;
    }
    else if (command_name == SkillsCommandKeys::EXIT_SKILLS)
    {
      process_result = -1;
    }
  }

  return process_result;
}
