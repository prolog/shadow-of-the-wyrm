#include "Game.hpp"
#include "MessageManagerFactory.hpp"
#include "ShowSkillsAction.hpp"
#include "SkillProcessorFactory.hpp"
#include "SkillTextKeys.hpp"
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

ActionCostValue SkillsCommandProcessor::process(CreaturePtr creature, CommandPtr command, MapPtr map, const SkillType st)
{
  ActionCostValue process_result = 0;
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
      SkillProcessorPtr sp = SkillProcessorFactory::create(st);

      if (sp != nullptr)
      {
        if (creature && creature->get_is_player() && map->get_map_type() == MapType::MAP_TYPE_WORLD)
        {
          process_result = -1;

          IMessageManager& manager = MessageManagerFactory::instance();
          manager.add_new_message(StringTable::get(SkillTextKeys::SKILL_USAGE_WORLD_MAP));
          manager.send();
        }
        else
        {
          process_result = sp->process(creature, map);
        }
      }
    }
    else if (command_name == SkillsCommandKeys::EXIT_SKILLS)
    {
      process_result = -1;
    }
  }

  return process_result;
}
