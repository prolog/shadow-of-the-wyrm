#include "global_prototypes.hpp"
#include "Metadata.hpp"
#include "OptionsComponent.hpp"
#include "PromptTextKeys.hpp"
#include "StringTable.hpp"
#include "TextKeys.hpp"
#include "WelcomeScreen.hpp"

using namespace std;

WelcomeScreen::WelcomeScreen(DisplayPtr new_display) : Screen(new_display)
{
  initialize();
}

// The Welcome screen - contains game version info and copyright
// information, and an prompt to continue
void WelcomeScreen::initialize()
{
  Metadata meta;

  vector<ScreenComponentPtr> welcome_screen;

  TextComponentPtr game_version_synopsis = std::make_shared<TextComponent>(meta.get_game_version_synopsis());
  TextComponentPtr copyright_info = std::make_shared<TextComponent>(StringTable::get(TextKeys::COPYRIGHT_NOTICE));
  TextComponentPtr wanderer_excerpt = std::make_shared<TextComponent>(get_title_poem());

  OptionsComponentPtr options = std::make_shared<OptionsComponent>();

  int option_id = 0;

  Option new_game;
  new_game.set_id(option_id++);
  new_game.set_description(StringTable::get(TextKeys::SL_TITLE_NEW_GAME));

  Option load_game;
  load_game.set_id(option_id++);
  load_game.set_description(StringTable::get(TextKeys::SL_TITLE_LOAD_GAME));

  Option quit;
  quit.set_id(25); // 'z'
  quit.set_description(StringTable::get(TextKeys::SL_TITLE_QUIT_GAME));

  options->add_option(new_game);
  options->add_option_description("");

  options->add_option(load_game);
  options->add_option_description("");

  options->add_option(quit);
  options->add_option_description("");

  welcome_screen.push_back(game_version_synopsis);
  welcome_screen.push_back(copyright_info);
  welcome_screen.push_back(wanderer_excerpt);

  welcome_screen.push_back(options);

  add_page(welcome_screen);

  // Set the prompt
  PromptPtr any_key_prompt = std::make_shared<Prompt>(PromptLocation::PROMPT_LOCATION_LOWER_RIGHT);
  any_key_prompt->set_text_sid(PromptTextKeys::PROMPT_SELECT_AN_OPTION);
  user_prompt = any_key_prompt;
}
