#include <vector>
#include "Game.hpp"
#include "ShowSkillsAction.hpp"
#include "SkillsCommandFactory.hpp"
#include "SkillsCommandProcessor.hpp"
#include "SkillsKeyboardCommandMap.hpp"
#include "SkillsScreen.hpp"
#include "TextDisplayScreen.hpp"

using namespace std;

ShowSkillsAction::ShowSkillsAction()
: category(SkillCategory::SKILL_CATEGORY_GENERAL)
{
}

bool ShowSkillsAction::operator==(const ShowSkillsAction& ssa) const
{
  return (category == ssa.category);
}

ActionCostValue ShowSkillsAction::show_skills(CreaturePtr creature)
{
  ActionCostValue action_cost_value = 0;

  DecisionStrategyPtr decision_strategy = creature->get_decision_strategy();
  CommandFactoryPtr command_factory = std::make_shared<SkillsCommandFactory>();
  KeyboardCommandMapPtr kb_command_map = std::make_shared<SkillsKeyboardCommandMap>();
  Game& game = Game::instance();
  MapPtr map = game.get_current_map();

  if (decision_strategy)
  {
    // If we've received an action that actually has a cost (> 0), or an exit
    // action (-1), then exit and return the cost.
    while (action_cost_value == 0)
    {
      SkillsScreen ss(game.get_display(), creature, category);
      string display_s = ss.display();
      int input = display_s.at(0);
      char screen_selection = display_s.at(0);

      SkillType st = ss.get_selected_skill(screen_selection);
      CommandPtr skills_command = decision_strategy->get_nonmap_decision(false, creature->get_id(), command_factory, kb_command_map, &input);
      action_cost_value = SkillsCommandProcessor::process(creature, skills_command, map, st);
    }
  }

  // Reset the category for the next time Show Skills is called.
  category = SkillCategory::SKILL_CATEGORY_GENERAL;
  return action_cost_value;
}

ActionCostValue ShowSkillsAction::show_general_skills(CreaturePtr creature)
{
  category = SkillCategory::SKILL_CATEGORY_GENERAL;
  return get_action_cost_value(creature);
}

ActionCostValue ShowSkillsAction::show_melee_weapon_skills(CreaturePtr creature)
{
  category = SkillCategory::SKILL_CATEGORY_MELEE;
  return get_action_cost_value(creature);
}

ActionCostValue ShowSkillsAction::show_ranged_weapon_skills(CreaturePtr creature)
{
  category = SkillCategory::SKILL_CATEGORY_RANGED;
  return get_action_cost_value(creature);
}

ActionCostValue ShowSkillsAction::show_magic_skills(CreaturePtr creature)
{
  category = SkillCategory::SKILL_CATEGORY_MAGIC;
  return get_action_cost_value(creature);
}

// Looking at skills is always free.
ActionCostValue ShowSkillsAction::get_action_cost_value(CreaturePtr creature) const
{
  return 0;
}
