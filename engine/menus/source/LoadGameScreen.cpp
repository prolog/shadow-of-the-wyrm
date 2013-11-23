#include <vector>
#include "Conversion.hpp"
#include "Game.hpp"
#include "LoadGameScreen.hpp"
#include "OptionsComponent.hpp"
#include "Serialization.hpp"
#include "StringTable.hpp"
#include "TextComponent.hpp"
#include "TextKeys.hpp"

using namespace std;

LoadGameScreen::LoadGameScreen(DisplayPtr new_display)
: Menu(new_display)
{
  initialize();
}

void LoadGameScreen::initialize()
{
  Game& game = Game::instance();

  menu_selection_to_filename_map.clear();

  TextComponentPtr game_selection_text = std::make_shared<TextComponent>(StringTable::get(TextKeys::SELECT_SAVED_GAME));

  OptionsComponentPtr options = std::make_shared<OptionsComponent>();

  vector<pair<string, string>> filenames = Serialization::get_save_file_names();

  int current_id = 0;
  for (vector<pair<string,string>>::iterator f_it = filenames.begin(); (f_it != filenames.end() && current_id < 25); f_it++)
  {
    pair<string,string> save_file = *f_it;
    string save_file_name = save_file.first;
    string save_file_desc = save_file.second;

    Option current_option;
    current_option.set_id(current_id);
    current_option.set_description(save_file_desc);

    options->add_option(current_option);
    options->add_option_description("");

    char option_c = 'a' + current_id;
    string option_s = Char::to_string(option_c);
    menu_selection_to_filename_map.insert(make_pair(option_s, save_file_name));

    current_id++;
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

string LoadGameScreen::get_file_name(const string& option) const
{
  string filename;

  map<string, string>::const_iterator m_it = menu_selection_to_filename_map.find(option);

  if (m_it != menu_selection_to_filename_map.end())
  {
    filename = m_it->second;
  }

  return filename;
}