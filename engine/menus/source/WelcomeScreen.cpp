#include <boost/make_shared.hpp>
#include "global_prototypes.hpp"
#include "OptionsComponent.hpp"
#include "StringConstants.hpp"
#include "StringTable.hpp"
#include "WelcomeScreen.hpp"

using namespace std;

WelcomeScreen::WelcomeScreen(DisplayPtr new_display) : Menu(new_display)
{
  initialize();
}

// The Welcome screen - contains game version info and copyright
// information, and an prompt to continue
void WelcomeScreen::initialize()
{
  TextComponentPtr game_version_synopsis = boost::make_shared<TextComponent>(get_game_version_synopsis());
  TextComponentPtr copyright_info = boost::make_shared<TextComponent>(StringTable::get(TextKeys::COPYRIGHT_NOTICE));
  TextComponentPtr wanderer_excerpt = boost::make_shared<TextComponent>(get_title_poem());

  OptionsComponentPtr options = boost::make_shared<OptionsComponent>();

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

  components.push_back(game_version_synopsis);
  components.push_back(copyright_info);
  components.push_back(wanderer_excerpt);

  components.push_back(options);
}
