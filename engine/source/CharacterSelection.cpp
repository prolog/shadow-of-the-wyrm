#include "Conversion.hpp"
#include "Game.hpp"
#include "OptionsComponent.hpp"
#include "RNG.hpp"
#include "CharacterSelection.hpp"
#include "CreatureUtils.hpp"
#include "RaceSelectionScreen.hpp"
#include "Setting.hpp"
#include "SexSelectionScreen.hpp"
#include "StringTable.hpp"
#include "TextDisplayFormatter.hpp"
#include "TextDisplayScreen.hpp"
#include "TextMessages.hpp"
#include "TextKeys.hpp"

using namespace std;

void CharacterSelection::select_sex(DisplayPtr display, CreatureSex& sex)
{
  bool select_sex = true;
  Option opt;
  Game& game = Game::instance();
  string default_sex = game.get_settings_ref().get_setting(Setting::DEFAULT_SEX);
  bool prompt_user_for_sex = true;

  if (!default_sex.empty())
  {
    int sex_i = String::to_int(default_sex);
    sex = static_cast<CreatureSex>(sex_i);
    prompt_user_for_sex = false;
  }

  if (prompt_user_for_sex)
  {
    while (display != nullptr && select_sex)
    {
      SexSelectionScreen sex_selection(display);
      string sex_selection_s = sex_selection.display();

      if (!sex_selection_s.empty())
      {
        int keyboard_selection = Char::keyboard_selection_char_to_int(sex_selection_s.at(0));
        bool lowercase = std::islower(sex_selection_s[0]);

        if (opt.is_random_option(sex_selection_s.at(0)))
        {
          sex = static_cast<CreatureSex>(RNG::range(static_cast<int>(CreatureSex::CREATURE_SEX_MALE), static_cast<int>(CreatureSex::CREATURE_SEX_FEMALE)));
          select_sex = false;
        }
        else
        {
          if (lowercase &&
            (keyboard_selection == static_cast<int>(CreatureSex::CREATURE_SEX_FEMALE) || keyboard_selection == static_cast<int>(CreatureSex::CREATURE_SEX_MALE)))
          {
            sex = static_cast<CreatureSex>(keyboard_selection);
            select_sex = false;
          }
          else if (!lowercase)
          {
            // refactor the hell out of this big ugly block and everything around it
            if (keyboard_selection == static_cast<int>(CreatureSex::CREATURE_SEX_FEMALE) || keyboard_selection == static_cast<int>(CreatureSex::CREATURE_SEX_MALE))
            {
              TextDisplayFormatter tdf;

              std::map<int, std::string> titles = { {0, TextKeys::SEX_MALE}, {1, TextKeys::SEX_FEMALE} };
              vector<pair<Colour, string>> sex_text;
              vector<string> formatted_text = tdf.format_text(StringTable::get(TextKeys::SEX_INFO_DESC), Screen::get_lines_displayable_area(game.get_display()));

              for (const string& text_line : formatted_text)
              {
                TextDisplayPair text_line_for_ui = make_pair(Colour::COLOUR_WHITE, text_line);
                sex_text.push_back(text_line_for_ui);
              }

              TextDisplayScreen tds(display, titles[keyboard_selection], sex_text);
              tds.display();
            }
          }
        }
      }
    }
  }
}

void CharacterSelection::select_race(DisplayPtr display, const RaceMap& races, const CreatureSex sex, string& selected_race_id, string& creature_synopsis)
{
  Game& game = Game::instance();
  string default_race_id = game.get_settings_ref().get_setting(Setting::DEFAULT_RACE_ID);
  auto r_it = races.find(default_race_id);
  bool prompt_user_for_race_selection = true;
  Option opt;

  if (r_it != races.end())
  {
    Race* race = r_it->second.get();

    if (race && race->get_user_playable())
    {
      prompt_user_for_race_selection = false;
      selected_race_id = default_race_id;
    }
  }

  if (prompt_user_for_race_selection)
  {
    creature_synopsis = TextMessages::get_character_creation_synopsis(sex, nullptr, nullptr, "", nullptr);
    RaceSelectionScreen race_selection(display, creature_synopsis);
    string race_index = race_selection.display();

    if (opt.is_random_option(race_index.at(0)))
    {
      Race* random_race = CreatureUtils::get_random_user_playable_race();

      if (random_race != nullptr)
      {
        selected_race_id = random_race->get_race_id();
      }
    }
    else
    {
      int race_idx = Char::keyboard_selection_char_to_int(race_index.at(0));
      selected_race_id = Integer::to_string_key_at_given_position_in_rc_map(races, race_idx);
    }
  }
}