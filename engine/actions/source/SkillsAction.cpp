#include <vector>
#include "Game.hpp"
#include "SkillsAction.hpp"
#include "SkillsCommandFactory.hpp"
#include "SkillsCommandProcessorFactory.hpp"
#include "SkillsKeyboardCommandMap.hpp"
#include "SkillsScreen.hpp"
#include "TextDisplayScreen.hpp"

using namespace std;

SkillsAction::SkillsAction()
: category(SkillCategory::SKILL_CATEGORY_GENERAL)
{
}

bool SkillsAction::operator==(const SkillsAction& ssa) const
{
  return (category == ssa.category);
}

ActionCostValue SkillsAction::show_skills(CreaturePtr creature, const SkillsSelectionType sst)
{
  ActionCostValue action_cost_value = 0;
  int cur_page = 1;

  DecisionStrategyPtr decision_strategy = creature->get_decision_strategy();
  CommandFactoryPtr command_factory = std::make_shared<SkillsCommandFactory>();
  KeyboardCommandMapPtr kb_command_map = std::make_shared<SkillsKeyboardCommandMap>();
  Game& game = Game::instance();
  MapPtr map = game.get_current_map();

  if (decision_strategy)
  {
    ISkillsCommandProcessorPtr scp = SkillsCommandProcessorFactory::create(sst);

    // If we've received an action that actually has a cost (> 0), or an exit
    // action (-1), then exit and return the cost.
    while (action_cost_value == 0 && scp->can_process(creature))
    {
      SkillsScreen ss(game.get_display(), creature, category, sst);
      ss.set_current_page_number(cur_page);

      string display_s = ss.display();
      int input = display_s.at(0);
      char screen_selection = display_s.at(0);

      SkillType st = ss.get_selected_skill(screen_selection);
      cur_page = ss.get_current_page_number();

      CommandPtr skills_command = decision_strategy->get_nonmap_decision(false, creature->get_id(), command_factory, kb_command_map, &input);
      action_cost_value = scp->process(creature, skills_command, map, st);
    }
  }

  // Reset the category for the next time Show Skills is called.
  category = SkillCategory::SKILL_CATEGORY_GENERAL;
  return action_cost_value;
}

ActionCostValue SkillsAction::show_general_skills(CreaturePtr creature)
{
  category = SkillCategory::SKILL_CATEGORY_GENERAL;
  return get_action_cost_value(creature);
}

ActionCostValue SkillsAction::show_melee_weapon_skills(CreaturePtr creature)
{
  category = SkillCategory::SKILL_CATEGORY_MELEE;
  return get_action_cost_value(creature);
}

ActionCostValue SkillsAction::show_ranged_weapon_skills(CreaturePtr creature)
{
  category = SkillCategory::SKILL_CATEGORY_RANGED;
  return get_action_cost_value(creature);
}

ActionCostValue SkillsAction::show_magic_skills(CreaturePtr creature)
{
  category = SkillCategory::SKILL_CATEGORY_MAGIC;
  return get_action_cost_value(creature);
}

ActionCostValue SkillsAction::improve_skill(CreaturePtr creature, const SkillType st)
{
  if (creature != nullptr)
  {
    SkillPtr skill = creature->get_skills().get_skill(st);

    if (skill != nullptr)
    {
      int val = skill->get_value();

      if (val < Skills::MAX_SKILL_VALUE)
      {
        val++;
        skill->set_value(val);

        creature->set_skill_points(creature->get_skill_points() - 1);
      }
    }
  }

  return get_action_cost_value(creature);
}

// Looking at/improving skills is always free.
ActionCostValue SkillsAction::get_action_cost_value(CreaturePtr creature) const
{
  return 0;
}

