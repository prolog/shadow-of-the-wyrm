#include <boost/algorithm/string.hpp>
#include "global_prototypes.hpp"
#include "Metadata.hpp"
#include "OptionsComponent.hpp"
#include "PromptTextKeys.hpp"
#include "StringTable.hpp"
#include "TextDisplayFormatter.hpp"
#include "TextKeys.hpp"
#include "OptionScreen.hpp"

using namespace std;
using namespace boost::algorithm;

OptionScreen::OptionScreen(DisplayPtr new_display, const string& new_title_sid, const map<string, string>& new_options) : Screen(new_display), title_sid(new_title_sid), options(new_options)
{
  initialize();
}

void OptionScreen::initialize()
{
  title_text_sid = title_sid;
  int i = 0;

  std::map<char, std::string> selection_map;
  OptionsComponentPtr scr_options = std::make_shared<OptionsComponent>();
  vector<ScreenComponentPtr> opt_screen;

  for (const auto& option : options)
  {
    scr_options->set_show_option_descriptions(false);
    int line_number = i + 1;

    if (can_add_component(line_number) == false)
    {
      i = 0;
      line_number = 1;
      screen_selection_to_id_map.push_back(selection_map);
      selection_map.clear();

      add_page(opt_screen);
      opt_screen.clear();
    }

    selection_map.insert(make_pair('a' + i, option.first));

    Option current_option;
    current_option.set_id(i);

    // Assumption is that the value in the map is always translated
    // (or dynamic, or whatever) and therefore no need to look it up
    // in the StringTable.
    current_option.set_description(option.second);

    scr_options->add_option(current_option);
    add_component(opt_screen, scr_options, line_number);
    
    scr_options = std::make_shared<OptionsComponent>();
    i++;
  }

  // Make sure that, at the very end, there is always the opportunity to
  // exit.
  Option current_option;
  current_option.set_id(25);
  current_option.set_description(StringTable::get(TextKeys::EXIT));
  selection_map.insert(make_pair('a' + 25, ""));

  // "(z) Exit"
  scr_options->add_option(current_option);

  screen_selection_to_id_map.push_back(selection_map);
  opt_screen.push_back(scr_options);
  add_page(opt_screen);

  // Set the prompt
  PromptPtr any_key_prompt = std::make_shared<Prompt>(PromptLocation::PROMPT_LOCATION_LOWER_RIGHT);
  any_key_prompt->set_text_sid(PromptTextKeys::PROMPT_SELECT_AN_OPTION);
  user_prompt = any_key_prompt;
}

string OptionScreen::get_option(const char selection)
{
  string option_id;

  auto& selection_map = screen_selection_to_id_map.at(get_cur_page_idx());
  map<char, string>::const_iterator selection_map_it = selection_map.find(selection);

  if (selection_map_it != selection_map.end())
  {
    option_id = selection_map_it->second;
  }

  return option_id;
}
