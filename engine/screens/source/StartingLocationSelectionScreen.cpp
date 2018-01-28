#include <string>
#include "Game.hpp"
#include "OptionsComponent.hpp"
#include "PromptTextKeys.hpp"
#include "StartingLocationSelectionScreen.hpp"
#include "TextComponent.hpp"
#include "TextKeys.hpp"

using namespace std;

StartingLocationSelectionScreen::StartingLocationSelectionScreen(DisplayPtr new_display, const string& creature_synop, const StartingLocationMap& new_sm)
: Screen(new_display), creature_synopsis(creature_synop), sm(new_sm)
{
  initialize();
}

// The starting location screen displays a list of possible starting locations
// to the player.  The choice determines where the character is placed when
// the game begins.
void StartingLocationSelectionScreen::initialize()
{
  ostringstream synop;
  synop << "[" << creature_synopsis << "]";

  TextComponentPtr sl_selection_text = std::make_shared<TextComponent>(StringTable::get(TextKeys::SELECT_STARTING_LOCATION));
  OptionsComponentPtr options = std::make_shared<OptionsComponent>();

  int current_id = 0;
  for (auto sm_it = sm.begin(); sm_it != sm.end(); sm_it++)
  {
    string sl_id = sm_it->first;
    StartingLocation sl = sm_it->second;

    if (options != nullptr)
    {
      Option current_option;
      current_option.set_id(current_id);
      current_option.set_description(StringTable::get(sl.get_description_sid()));

      options->add_option(current_option);
      options->add_option_description("");
      current_id++;
    }
  }

  // Random selection (use '*')
  Option random_option;
  random_option.set_id(random_option.get_id_for_random());
  random_option.set_description(StringTable::get(TextKeys::RANDOM_SELECTION));

  options->add_option(random_option);
  options->add_option_description("");

  vector<ScreenComponentPtr> cur_page;
  cur_page.push_back(make_shared<TextComponent>(synop.str()));
  cur_page.push_back(sl_selection_text);
  cur_page.push_back(options);

  add_page(cur_page);

  // Set the prompt
  PromptPtr any_key_prompt = std::make_shared<Prompt>(PromptLocation::PROMPT_LOCATION_LOWER_RIGHT);
  any_key_prompt->set_text_sid(PromptTextKeys::PROMPT_SELECT_AN_OPTION);
  user_prompt = any_key_prompt;
}
