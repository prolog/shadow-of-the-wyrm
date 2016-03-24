#include "HelpScreen.hpp"
#include "PromptTextKeys.hpp"
#include "ScreenTitleTextKeys.hpp"
#include "StringTable.hpp"
#include "TextKeys.hpp"

using namespace std;

HelpScreen::HelpScreen(DisplayPtr new_display)
: Screen(new_display)
{
  initialize();
}

// Initialize the deity selection screen.  Deities must have been
// read in, and set into the Game object by this point.  As well,
// a valid RacePtr must have been provided to the constructor, so
// that we know what deities can be selected.
void HelpScreen::initialize()
{
  title_text_sid = ScreenTitleTextKeys::SCREEN_TITLE_HELP;

  vector<ScreenComponentPtr> help_screen;
  OptionsComponentPtr options = std::make_shared<OptionsComponent>();

  string keybindings = StringTable::get(TextKeys::KEYBINDINGS);

  Option current_option;
  current_option.set_id(0);
  current_option.set_description(keybindings);

  options->add_option(current_option);
  options->add_option_description("");

  help_screen.push_back(options);
  add_page(help_screen);

  PromptPtr help_prompt = std::make_shared<Prompt>(PromptLocation::PROMPT_LOCATION_LOWER_RIGHT);
  help_prompt->set_text_sid(PromptTextKeys::PROMPT_HELP);
  help_prompt->set_accept_any_input(true);
  user_prompt = help_prompt;
}
