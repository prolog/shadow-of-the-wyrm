#include "Conversion.hpp"
#include "SkillsScreen.hpp"
#include "OptionsComponent.hpp"
#include "Prompt.hpp"
#include "TextComponent.hpp"
#include "PromptTextKeys.hpp"
#include "SkillTextKeys.hpp"

using namespace std;

SkillsScreen::SkillsScreen(DisplayPtr new_display, CreaturePtr new_creature, const SkillCategory sc)
: Screen(new_display)
, creature(new_creature)
, category(sc)
, screen_titles({{SkillCategory::SKILL_CATEGORY_GENERAL, SkillTextKeys::SKILLS_GENERAL},
                 {SkillCategory::SKILL_CATEGORY_MELEE, SkillTextKeys::SKILLS_WEAPON},
                 {SkillCategory::SKILL_CATEGORY_RANGED, SkillTextKeys::SKILLS_RANGED_WEAPON},
                 {SkillCategory::SKILL_CATEGORY_MAGIC, SkillTextKeys::SKILLS_MAGIC}})
, skills_for_category({{SkillCategory::SKILL_CATEGORY_GENERAL, {SkillType::SKILL_GENERAL_ARCHERY, SkillType::SKILL_GENERAL_WEAVING}},
                       {SkillCategory::SKILL_CATEGORY_MELEE, {SkillType::SKILL_MELEE_AXES, SkillType::SKILL_MELEE_EXOTIC}},
                       {SkillCategory::SKILL_CATEGORY_RANGED, {SkillType::SKILL_RANGED_AXES, SkillType::SKILL_RANGED_EXOTIC}},
                       {SkillCategory::SKILL_CATEGORY_MAGIC, {SkillType::SKILL_MAGIC_ARCANE, SkillType::SKILL_MAGIC_CANTRIPS}}})
{
  initialize();
}

void SkillsScreen::initialize()
{
  vector<ScreenComponentPtr> sk_screen;
  auto s_it = screen_titles.find(category);

  if (s_it != screen_titles.end())
  {
    title_text_sid = s_it->second;
  }

  // JCD FIXME: Set the skills/pages.
  auto sty_it = skills_for_category.find(category);
  SkillType min = SkillType::SKILL_GENERAL_ARCHERY;
  SkillType max = SkillType::SKILL_GENERAL_WEAVING;

  if (sty_it != skills_for_category.end())
  {
    pair<SkillType, SkillType> min_max = sty_it->second;

    min = min_max.first;
    max = min_max.second;
  }

  int cnt = 0;
  int current_id = 0;

  if (creature != nullptr)
  {
    for (int i = static_cast<int>(min); i <= static_cast<int>(max); i++)
    {
      OptionsComponentPtr options = std::make_shared<OptionsComponent>();
      Option current_option;
      TextComponentPtr option_text_component = current_option.get_description();

      SkillPtr skill = creature->get_skills().get_skill(static_cast<SkillType>(i));

      if (skill != nullptr && skill->get_value() > 0)
      {
        string skill_desc = StringTable::get(skill->get_skill_name_sid());
        option_text_component->add_text(skill_desc);

        current_option.set_id(current_id);
        current_option.set_external_id(to_string(i));

        options->add_option(current_option);
        options->add_option_description("");

        cnt++;

        add_options_component(sk_screen, options, cnt, current_id);

        current_id++;
      }
    }
  }

  add_page(sk_screen);

  // Set the prompt
  PromptPtr inv_prompt = std::make_shared<Prompt>(PromptLocation::PROMPT_LOCATION_LOWER_RIGHT);

  // Accept any input to the inventory manager will take care of sorting out
  // what's a valid command and what is not.
  inv_prompt->set_accept_any_input(true);
  inv_prompt->set_text_sid(PromptTextKeys::PROMPT_SKILLS);
  user_prompt = inv_prompt;
  line_increment = 1;
}

