#include <vector>
#include <boost/make_shared.hpp>
#include "Game.hpp"
#include "LoadGameScreen.hpp"
#include "OptionsComponent.hpp"
#include "Serialization.hpp"
#include "StringTable.hpp"
#include "TextComponent.hpp"

using namespace std;

LoadGameScreen::LoadGameScreen(DisplayPtr new_display)
: Menu(new_display)
{
  initialize();
}

void LoadGameScreen::initialize()
{
  Game* game = Game::instance();

  if (game)
  {
    TextComponentPtr game_selection_text = boost::make_shared<TextComponent>(StringTable::get(TextKeys::SELECT_SAVED_GAME));

    OptionsComponentPtr options = boost::make_shared<OptionsComponent>();

    vector<pair<string, string>> filenames = Serialization::get_save_file_names();

    int current_id = 0;
    for (vector<pair<string,string>>::iterator f_it = filenames.begin(); (f_it != filenames.end() && current_id < 25); f_it++)
    {
      pair<string,string> save_file = *f_it;
      string save_file_name = save_file.first;
      string save_file_desc = save_file.second;

      Option current_option;
      current_option.set_id(current_id++);
      current_option.set_description(save_file_name);

      options->add_option(current_option);
      options->add_option_description(save_file_desc);
    }

    Option exit_option;
    Option current_option;
    current_option.set_id(25);
    current_option.set_description(StringTable::get(TextKeys::EXIT));

    // "(z) Exit"
    options->add_option(current_option);
    options->add_option_description("");

    components.push_back(game_selection_text);
    components.push_back(options);
  }
}