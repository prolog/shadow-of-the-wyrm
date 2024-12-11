#include <vector>
#include "Conversion.hpp"
#include "Game.hpp"
#include "ScreenTitleTextKeys.hpp"
#include "SkillProcessorFactory.hpp"
#include "SkillsAction.hpp"
#include "SkillsCommandFactory.hpp"
#include "SkillsCommandProcessorFactory.hpp"
#include "SkillsKeyboardCommandMap.hpp"
#include "SkillsScreen.hpp"
#include "TextDisplayFormatter.hpp"
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
  ActionCostValue action_cost_value = ActionCostConstants::NO_ACTION;
  int cur_page = 1;

  DecisionStrategy* decision_strategy = creature->get_decision_strategy();
  CommandFactoryPtr command_factory = std::make_unique<SkillsCommandFactory>();
  KeyboardCommandMapPtr kb_command_map = std::make_unique<SkillsKeyboardCommandMap>();
  Game& game = Game::instance();
  MapPtr map = game.get_current_map();

  if (decision_strategy)
  {
    ISkillsCommandProcessorPtr scp = SkillsCommandProcessorFactory::create(sst);

    // If we've received an action that actually has a cost (> 0), or an exit
    // action (-1), then exit and return the cost.
    while (action_cost_value == 0 && scp->can_process(creature))
    {
      int input = 0;
      string display_s;
      char screen_selection = '?';
      SkillType st = SkillType::SKILL_UNDEFINED;

      {
        SkillsScreen ss(game.get_display(), creature, category, sst);
        ss.set_current_page_number(cur_page);

        display_s = ss.display();
        input = display_s.at(0);
        screen_selection = display_s.at(0);

        st = ss.get_selected_skill(screen_selection);
        cur_page = ss.get_current_page_number();
      }

      CommandPtr skills_command = decision_strategy->get_nonmap_decision(false, creature->get_id(), command_factory.get(), kb_command_map.get(), &input, false);
      action_cost_value = scp->process(creature, skills_command.get(), map, st);
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
    SkillProcessorPtr sp = SkillProcessorFactory::create(st);
    Skill* skill = creature->get_skills().get_skill(st);

    if (skill != nullptr && sp && sp->is_skill_implemented())
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

ActionCostValue SkillsAction::describe_skill(CreaturePtr creature, const SkillType st)
{
  if (st != SkillType::SKILL_UNDEFINED && creature != nullptr)
  {
    Skill* skill = creature->get_skills().get_skill(st);

    if (skill != nullptr)
    {
      Game& game = Game::instance();
      vector<pair<Colour, string>> skill_text;
      uint width = Game::instance().get_display()->get_width();
      string separator;

      string skill_name = String::centre(StringTable::get(skill->get_skill_name_sid()), width);
      skill_text.push_back(make_pair(Colour::COLOUR_WHITE, skill_name));
      skill_text.push_back(make_pair(Colour::COLOUR_BLACK, separator));

      TextDisplayFormatter tdf;
      string skill_details = StringTable::get(skill->get_skill_description_sid());
      vector<string> sktext = tdf.format_text(skill_details);

      for (const string& line_of_text : sktext)
      {
        skill_text.push_back(make_pair(Colour::COLOUR_WHITE, line_of_text));
      }

      TextDisplayScreen tds(game.get_display(), ScreenTitleTextKeys::SCREEN_TITLE_SKILL_DETAILS, skill_text, true, {});
      tds.display();
    }
  }

  return get_action_cost_value(creature);
}

// Looking at/improving skills is always free.
ActionCostValue SkillsAction::get_action_cost_value(CreaturePtr /* creature */) const
{
  return 0;
}

