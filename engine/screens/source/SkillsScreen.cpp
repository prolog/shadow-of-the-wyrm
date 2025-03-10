#include "Conversion.hpp"
#include "Game.hpp"
#include "SkillsScreen.hpp"
#include "OptionsComponent.hpp"
#include "Prompt.hpp"
#include "Setting.hpp"
#include "TextComponent.hpp"
#include "PromptTextKeys.hpp"
#include "SkillProcessorFactory.hpp"
#include "SkillTextKeys.hpp"

using namespace std;

SkillsScreen::SkillsScreen(DisplayPtr new_display, CreaturePtr new_creature, const SkillCategory sc, const SkillsSelectionType s_type)
: Screen(new_display)
, creature(new_creature)
, category(sc)
, sst(s_type)
, skills_for_category({{SkillCategory::SKILL_CATEGORY_GENERAL, {SkillType::SKILL_GENERAL_ARCHERY, SkillType::SKILL_GENERAL_WEAVING}},
                       {SkillCategory::SKILL_CATEGORY_MELEE, {SkillType::SKILL_MELEE_AXES, SkillType::SKILL_MELEE_EXOTIC}},
                       {SkillCategory::SKILL_CATEGORY_RANGED, {SkillType::SKILL_RANGED_AXES, SkillType::SKILL_RANGED_EXOTIC}},
                       {SkillCategory::SKILL_CATEGORY_MAGIC, {SkillType::SKILL_MAGIC_ARCANE, SkillType::SKILL_MAGIC_CANTRIPS}}})
{
  initialize();
}

void SkillsScreen::initialize()
{
  screen_titles = { {SkillCategory::SKILL_CATEGORY_GENERAL, {make_pair(SkillsSelectionType::SKILLS_SELECTION_SELECT_SKILL, SkillTextKeys::SKILLS_GENERAL), make_pair(SkillsSelectionType::SKILLS_SELECTION_IMPROVE_SKILL, SkillTextKeys::SKILLS_IMPROVE_GENERAL)}},
                    {SkillCategory::SKILL_CATEGORY_MELEE,   {make_pair(SkillsSelectionType::SKILLS_SELECTION_SELECT_SKILL, SkillTextKeys::SKILLS_WEAPON), make_pair(SkillsSelectionType::SKILLS_SELECTION_IMPROVE_SKILL, SkillTextKeys::SKILLS_IMPROVE_WEAPON)}},
                    {SkillCategory::SKILL_CATEGORY_RANGED,  {make_pair(SkillsSelectionType::SKILLS_SELECTION_SELECT_SKILL, SkillTextKeys::SKILLS_RANGED_WEAPON), make_pair(SkillsSelectionType::SKILLS_SELECTION_IMPROVE_SKILL, SkillTextKeys::SKILLS_IMPROVE_RANGED_WEAPON)}},
                    {SkillCategory::SKILL_CATEGORY_MAGIC,   {make_pair(SkillsSelectionType::SKILLS_SELECTION_SELECT_SKILL, SkillTextKeys::SKILLS_MAGIC), make_pair(SkillsSelectionType::SKILLS_SELECTION_IMPROVE_SKILL, SkillTextKeys::SKILLS_IMPROVE_MAGIC)}}};

  vector<ScreenComponentPtr> sk_screen;
  auto s_it = screen_titles.find(category);

  if (s_it != screen_titles.end())
  {
    title_text_sid = s_it->second[sst];

    if (sst == SkillsSelectionType::SKILLS_SELECTION_IMPROVE_SKILL && creature != nullptr)
    {
      int skill_pts_remaining = creature->get_skill_points();
      title_text_sid = SkillTextKeys::get_skill_improvement_message(title_text_sid, skill_pts_remaining);
    }
  }

  auto sty_it = skills_for_category.find(category);
  SkillType min = SkillType::SKILL_GENERAL_ARCHERY;
  SkillType max = SkillType::SKILL_GENERAL_WEAVING;
  std::map<char, SkillType> selection_map;
  bool selection_require_uppercase = Game::instance().get_settings_ref().get_setting_as_bool(Setting::SKILL_SELECTION_REQUIRE_CAPITALIZATION);
  
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

      SkillType st = static_cast<SkillType>(i);
      Skill* skill = creature->get_skills().get_skill(st);

      if (skill != nullptr && (skill->get_value() > 0 || skill->can_train_from_unlearned()))
      {
        string skill_desc = StringTable::get(skill->get_skill_name_sid());

        ostringstream ss;
        ss << skill_desc << " (" << skill->get_value() << ")";

        option_text_component->add_text(ss.str());
        options->add_option_description("");

        cnt++;

        if (can_add_component(cnt) == false)
        {
          current_id = 0;
          cnt = 1;
          screen_selection_to_skill_map.push_back(selection_map);
          selection_map.clear();

          add_page(sk_screen);
          sk_screen.clear();
        }

        bool enabled = true;

        if (sst == SkillsSelectionType::SKILLS_SELECTION_IMPROVE_SKILL)
        {
          SkillProcessorPtr sp = SkillProcessorFactory::create(st);
          if (sp && !sp->is_skill_implemented())
          {
            enabled = false;
          }
        }

        // Set the ID after we've done a check on whether or not we can
        // add the component so that if a new page was added, and the
        // current id updated, we aren't setting the old value.
        current_option.set_id(current_id);
        current_option.set_external_id(to_string(i));
        current_option.set_uppercase(selection_require_uppercase);
        current_option.set_enabled(enabled);
        options->add_option(current_option);

        add_options_component(sk_screen, options, cnt, current_id);

        // Add to the selection map after the option component has been added
        // so that if we've started a new page, the skill is added to the
        // correct place.
        //
        // Do both uppercase and lowercase.
        if (selection_require_uppercase)
        {
          selection_map['A' + static_cast<char>(current_id)] = st;
        }
        else
        {
          selection_map['a' + static_cast<char>(current_id)] = st;
        }

        current_id++;
      }
    }
  }

  screen_selection_to_skill_map.push_back(selection_map);
  add_page(sk_screen);

  // Set the prompt
  PromptPtr inv_prompt = std::make_unique<Prompt>(PromptLocation::PROMPT_LOCATION_LOWER_RIGHT);

  // Accept any input to the inventory manager will take care of sorting out
  // what's a valid command and what is not.
  inv_prompt->set_accept_any_input(true);
  inv_prompt->set_text_sid(PromptTextKeys::PROMPT_SKILLS);
  user_prompt = std::move(inv_prompt);
  line_increment = 1;
}

SkillType SkillsScreen::get_selected_skill(const char selection) const
{
  SkillType st = SkillType::SKILL_UNDEFINED;
  char selection_approp_case = static_cast<char>(tolower(selection));
  bool req_caps = Game::instance().get_settings_ref().get_setting_as_bool(Setting::SKILL_SELECTION_REQUIRE_CAPITALIZATION);

  if (req_caps)
  {
    selection_approp_case = static_cast<char>(toupper(selection));
  }

  const auto& selection_map = screen_selection_to_skill_map.at(get_cur_page_idx());
  map<char, SkillType>::const_iterator selection_map_it = selection_map.find(selection_approp_case);

  if (selection_map_it != selection_map.end())
  {
    st = selection_map_it->second;
  }
  
  return st;
}