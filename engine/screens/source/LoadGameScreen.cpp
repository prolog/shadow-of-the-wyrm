#include <vector>
#include "Conversion.hpp"
#include "Game.hpp"
#include "LoadGameScreen.hpp"
#include "OptionsComponent.hpp"
#include "PromptTextKeys.hpp"
#include "Serialization.hpp"
#include "Setting.hpp"
#include "StringTable.hpp"
#include "TextComponent.hpp"
#include "TextKeys.hpp"

using namespace std;

LoadGameScreen::LoadGameScreen(DisplayPtr new_display)
: Screen(new_display)
{
  initialize();
}

void LoadGameScreen::initialize()
{
  vector<ScreenComponentPtr> load_game_screen;

  screen_selection_to_filename_map.clear();

  TextComponentPtr game_selection_text = std::make_shared<TextComponent>(StringTable::get(TextKeys::SELECT_SAVED_GAME));

  OptionsComponentPtr options = std::make_shared<OptionsComponent>();

  Settings& settings = Game::instance().get_settings_ref();
  bool single_user_mode = settings.get_setting_as_bool(Setting::SINGLE_USER_MODE);
  bool skip_metadata_verification = settings.get_setting_as_bool(Setting::SKIP_SAVEFILE_METADATA_VERIFICATION);

  vector<pair<string, string>> filenames = Serialization::get_save_file_names(single_user_mode, skip_metadata_verification);

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

    char option_c = 'a' + static_cast<char>(current_id);
    string option_s = string(1, option_c);
    screen_selection_to_filename_map.insert(make_pair(option_s, save_file_name));

    current_id++;
  }

  Option current_option;
  current_option.set_id(25);
  current_option.set_description(StringTable::get(TextKeys::EXIT));

  // "(z) Exit"
  options->add_option(current_option);
  options->add_option_description("");

  load_game_screen.push_back(game_selection_text);
  load_game_screen.push_back(options);

  add_page(load_game_screen);

  // Set the prompt
  PromptPtr any_key_prompt = std::make_unique<Prompt>(PromptLocation::PROMPT_LOCATION_LOWER_RIGHT);
  any_key_prompt->set_text_sid(PromptTextKeys::PROMPT_SELECT_AN_OPTION);
  user_prompt = std::move(any_key_prompt);
}

string LoadGameScreen::get_file_name(const string& option) const
{
  string filename;

  map<string, string>::const_iterator m_it = screen_selection_to_filename_map.find(option);

  if (m_it != screen_selection_to_filename_map.end())
  {
    filename = m_it->second;
  }

  return filename;
}
