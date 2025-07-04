#include "Game.hpp"
#include "GainSkillsCommandProcessor.hpp"
#include "MessageManagerFactory.hpp"
#include "SkillsAction.hpp"
#include "SkillProcessorFactory.hpp"
#include "SkillTextKeys.hpp"
#include "SkillsCommandKeys.hpp"
#include "SkillsCommands.hpp"
#include "TextMessages.hpp"

using namespace std;

bool GainSkillsCommandProcessor::can_process(CreaturePtr creature)
{
  int skill_pts = 0;
  Skills skills;

  if (creature)
  {
    skill_pts = creature->get_skill_points();
    skills = creature->get_skills();
  }

  return (skill_pts > 0 && skills.has_trainable_skill());
}

ActionCostValue GainSkillsCommandProcessor::process(CreaturePtr creature, Command* command, MapPtr /*map*/, const SkillType st)
{
  ActionCostValue process_result = ActionCostConstants::NO_ACTION;
  Game& game = Game::instance();
  SkillsAction& sa = game.get_action_manager_ref().get_skills_action_ref();

  if (creature && command)
  {
    string command_name = command->get_name();

    if (command_name == SkillsCommandKeys::GENERAL_SKILLS)
    {
      return sa.show_general_skills(creature);
    }
    else if (command_name == SkillsCommandKeys::MELEE_WEAPON_SKILLS)
    {
      return sa.show_melee_weapon_skills(creature);
    }
    else if (command_name == SkillsCommandKeys::RANGED_WEAPON_SKILLS)
    {
      return sa.show_ranged_weapon_skills(creature);
    }
    else if (command_name == SkillsCommandKeys::MAGIC_SKILLS)
    {
      return sa.show_magic_skills(creature);
    }
    else if (command_name == SkillsCommandKeys::SELECT_SKILL)
    {
      return sa.improve_skill(creature, st);
    }
    else if (command_name == SkillsCommandKeys::SKILL_DESCRIPTION)
    {
      return sa.describe_skill(creature, st);
    }
    else if (command_name == SkillsCommandKeys::EXIT_SKILLS)
    {
      process_result = -1;

      if (creature != nullptr && creature->get_is_player())
      {
        int skill_pts = creature->get_skill_points();

        if (skill_pts > 0)
        {
          // Add an alert, as we're in a separate window.
          IMessageManager& manager = MMF::instance();
          ostringstream ss;
          ss << StringTable::get(SkillTextKeys::SKILLS_EXIT_IMPROVEMENT_POINTS_REMAIN);


          if (creature->get_level() == CreatureConstants::MAX_CREATURE_LEVEL)
          {
            ss << " " << StringTable::get(SkillTextKeys::SKILLS_EXIT_MAX_LEVEL);
          }

          manager.alert_text(TextMessages::get_confirmation_message(ss.str()));
          bool quit_improve = creature->get_decision_strategy()->get_confirmation();
          manager.clear_if_necessary();

          // Change process_result based on the answer from the player.
          if (quit_improve == false)
          {
            process_result = 0;
          }
        }
      }
    }
  }

  return process_result;
}

#ifdef UNIT_TESTS
#include "unit_tests/GainSkillsCommandProcessor_test.cpp"
#endif