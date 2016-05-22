#include "Game.hpp"
#include "MessageManagerFactory.hpp"
#include "SkillsAction.hpp"
#include "SkillProcessorFactory.hpp"
#include "SkillTextKeys.hpp"
#include "SkillsCommandKeys.hpp"
#include "GainSkillsCommandProcessor.hpp"
#include "SkillsCommands.hpp"

using namespace std;

ActionCostValue GainSkillsCommandProcessor::process(CreaturePtr creature, CommandPtr command, MapPtr map, const SkillType st)
{
  ActionCostValue process_result = 0;
  Game& game = Game::instance();
  SkillsAction& ssa = game.get_action_manager_ref().get_skills_action_ref();

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
      // Functionality here!
      process_result = 0;
    }
    else if (command_name == SkillsCommandKeys::EXIT_SKILLS)
    {
      // JCD TODO: Confirmation message.
      process_result = -1;
    }
  }

  return process_result;
}
