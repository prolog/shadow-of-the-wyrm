#include <boost/algorithm/string.hpp>
#include "global_prototypes.hpp"
#include "Metadata.hpp"
#include "OptionsComponent.hpp"
#include "PromptTextKeys.hpp"
#include "StringTable.hpp"
#include "TextDisplayFormatter.hpp"
#include "TextKeys.hpp"
#include "WelcomeScreen.hpp"

using namespace std;
using namespace boost::algorithm;

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
  string title_poem = get_title_poem();

  TextDisplayFormatter tdf;
  vector<string> poem_v = tdf.format_text(title_poem);
  vector<TextComponentPtr> poem_lines;

  for (string& poem_line : poem_v)
  {
    trim_left(poem_line);
    trim_right(poem_line);

    TextComponentPtr current_line = std::make_shared<TextComponent>(poem_line);
    poem_lines.push_back(current_line);
  }

  OptionsComponentPtr options = std::make_shared<OptionsComponent>();

  int option_id = 0;

  Option new_game;
  new_game.set_id(option_id++);
  new_game.set_description(StringTable::get(TextKeys::SW_TITLE_NEW_GAME));

  Option load_game;
  load_game.set_id(option_id++);
  load_game.set_description(StringTable::get(TextKeys::SW_TITLE_LOAD_GAME));

  Option quit;
  quit.set_id(25); // 'z'
  quit.set_description(StringTable::get(TextKeys::SW_TITLE_QUIT_GAME));

  options->add_option(new_game);
  options->add_option_description("");

  options->add_option(load_game);
  options->add_option_description("");

  options->add_option(quit);
  options->add_option_description("");

  welcome_screen.push_back(game_version_synopsis);
  welcome_screen.push_back(copyright_info);

  for (TextComponentPtr poem_line : poem_lines)
  {
    ComponentAlignment ca(true, 1);

    poem_line->set_spacing_after(ca);
    welcome_screen.push_back(poem_line);
  }

  welcome_screen.push_back(options);

  add_page(welcome_screen);

  // Set the prompt
  PromptPtr any_key_prompt = std::make_shared<Prompt>(PromptLocation::PROMPT_LOCATION_LOWER_RIGHT);
  any_key_prompt->set_text_sid(PromptTextKeys::PROMPT_SELECT_AN_OPTION);
  user_prompt = any_key_prompt;
}
