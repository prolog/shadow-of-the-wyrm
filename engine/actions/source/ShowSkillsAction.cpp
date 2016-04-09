#include <vector>
#include "Game.hpp"
#include "ShowSkillsAction.hpp"
#include "SkillsCommandFactory.hpp"
#include "SkillsCommandProcessor.hpp"
#include "SkillsKeyboardCommandMap.hpp"
#include "SkillsScreen.hpp"
#include "TextDisplayScreen.hpp"

using namespace std;

ActionCostValue ShowSkillsAction::show_skills(CreaturePtr creature)
{
  ActionCostValue action_cost_value = 0;

  DecisionStrategyPtr decision_strategy = creature->get_decision_strategy();
  CommandFactoryPtr command_factory = std::make_shared<SkillsCommandFactory>();
  KeyboardCommandMapPtr kb_command_map = std::make_shared<SkillsKeyboardCommandMap>();
  Game& game = Game::instance();

  if (decision_strategy)
  {
    while (action_cost_value > -1)
    {
      SkillsScreen ss(game.get_display(), creature, SkillCategory::SKILL_CATEGORY_GENERAL);
      string display_s = ss.display();
      int input = display_s.at(0);
      char screen_selection = display_s.at(0);

      CommandPtr skills_command = decision_strategy->get_nonmap_decision(false, creature->get_id(), command_factory, kb_command_map, &input);
      action_cost_value = SkillsCommandProcessor::process(creature, skills_command);
    }
  }

  return get_action_cost_value(creature);
}

ActionCostValue ShowSkillsAction::show_general_skills(CreaturePtr creature)
{
  return get_action_cost_value(creature);
}

ActionCostValue ShowSkillsAction::show_melee_weapon_skills(CreaturePtr creature)
{
  return get_action_cost_value(creature);
}

ActionCostValue ShowSkillsAction::show_ranged_weapon_skills(CreaturePtr creature)
{
  return get_action_cost_value(creature);
}

ActionCostValue ShowSkillsAction::show_magic_skills(CreaturePtr creature)
{
  return get_action_cost_value(creature);
}

ActionCostValue ShowSkillsAction::get_action_cost_value(CreaturePtr creature) const
{
  return 0;
}
