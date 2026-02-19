#include "AgeSelectionScreen.hpp"
#include "ClassSelectionScreen.hpp"
#include "Conversion.hpp"
#include "DeitySelectionScreen.hpp"
#include "EyeSelectionScreen.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "HairSelectionScreen.hpp"
#include "OptionsComponent.hpp"
#include "RNG.hpp"
#include "CharacterSelection.hpp"
#include "CreatureUtils.hpp"
#include "RaceSelectionScreen.hpp"
#include "ReligionConstants.hpp"
#include "Setting.hpp"
#include "SexSelectionScreen.hpp"
#include "StartingLocationSelectionScreen.hpp"
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

void CharacterSelection::select_class(DisplayPtr display, const ClassMap& classes, const CreatureSex sex, Race* sel_race, string& selected_class_id, string& creature_synopsis)
{
  Game& game = Game::instance();
  string default_class_id = game.get_settings_ref().get_setting(Setting::DEFAULT_CLASS_ID);
  const auto c_it = classes.find(default_class_id);
  bool prompt_user_for_class_selection = true;
  Option opt;

  if (c_it != classes.end())
  {
    Class* cur_class = c_it->second.get();

    if (cur_class && cur_class->get_user_playable())
    {
      prompt_user_for_class_selection = false;
      selected_class_id = default_class_id;
    }
  }

  if (prompt_user_for_class_selection)
  {
    creature_synopsis = TextMessages::get_character_creation_synopsis(sex, sel_race, nullptr, "", nullptr);

    ClassSelectionScreen class_selection(display, creature_synopsis);
    string class_index = class_selection.display();

    if (opt.is_random_option(class_index.at(0)))
    {
      Class* cur_class = CreatureUtils::get_random_user_playable_class();

      if (cur_class != nullptr)
      {
        selected_class_id = cur_class->get_class_id();
      }
    }
    else
    {
      int class_idx = Char::keyboard_selection_char_to_int(class_index.at(0));
      selected_class_id = Integer::to_string_key_at_given_position_in_rc_map(classes, class_idx);
    }
  }
}

void CharacterSelection::select_hair(DisplayPtr display, const string& creature_synopsis, HairColour& hair_colour)
{
  Game& game = Game::instance();
  string default_hair = game.get_settings_ref().get_setting(Setting::DEFAULT_HAIR_COLOUR);
  Option opt;

  if (!default_hair.empty())
  {
    HairColour hc = static_cast<HairColour>(String::to_int(default_hair));

    if (hc == HairColour::HAIR_NA)
    {
      HairSelectionScreen hss(display, creature_synopsis);
      string val = hss.display();

      if (!opt.is_random_option(val.at(0)))
      {
        hair_colour = static_cast<HairColour>(Char::keyboard_selection_char_to_int(val.at(0)));
      }
    }
    else
    {
      hair_colour = hc;
    }
  }
}

void CharacterSelection::select_eyes(DisplayPtr display, const string& creature_synopsis, EyeColour& eye_colour)
{
  Game& game = Game::instance();
  string default_eye = game.get_settings_ref().get_setting(Setting::DEFAULT_EYE_COLOUR);
  Option opt;

  if (!default_eye.empty())
  {
    EyeColour ec = static_cast<EyeColour>(String::to_int(default_eye));

    if (ec == EyeColour::EYE_COLOUR_NA)
    {
      EyeSelectionScreen ess(display, creature_synopsis);
      string val = ess.display();

      if (!opt.is_random_option(val.at(0)))
      {
        eye_colour = static_cast<EyeColour>(Char::keyboard_selection_char_to_int(val.at(0)));
      }
    }
    else
    {
      eye_colour = ec;
    }
  }
}

void CharacterSelection::select_age(DisplayPtr display, Race* sel_race, const string& creature_synopsis, int& age)
{
  Game& game = Game::instance();
  string default_age = game.get_settings_ref().get_setting(Setting::DEFAULT_AGE);
  bool show_age_screen = false;

  if (sel_race != nullptr)
  {
    if (!default_age.empty())
    {
      age = String::to_int(default_age);

      if (age == -1)
      {
        show_age_screen = true;
      }
    }
  }

  if (show_age_screen)
  {
    AgeInfo age_info = sel_race->get_age_info();
    int min_select_age = age_info.get_starting_age().get_min();
    int max_select_age = age_info.get_maximum_age().get_min() - 1;
    bool valid_age = false;

    while (!valid_age)
    {
      AgeSelectionScreen ass(display, creature_synopsis, min_select_age, max_select_age);
      age = String::to_int(ass.display());
      valid_age = sel_race->is_valid_starting_age(age);
    }
  }
}

void CharacterSelection::select_deity(DisplayPtr display, Race* sel_race, string& creature_synopsis, string& selected_deity_id)
{
  Game& game = Game::instance();
  string default_deity_id = game.get_settings_ref().get_setting(Setting::DEFAULT_DEITY_ID);
  bool prompt_user_for_deity_selection = true;
  vector<string> deity_ids = sel_race->get_initial_deity_ids();
  Option opt;

  if (std::find(deity_ids.begin(), deity_ids.end(), default_deity_id) != deity_ids.end())
  {
    selected_deity_id = default_deity_id;
    prompt_user_for_deity_selection = false;
  }

  if (prompt_user_for_deity_selection)
  {
    DeitySelectionScreen deity_selection(display, sel_race, creature_synopsis);
    string deity_index = deity_selection.display();

    if (opt.is_random_option(deity_index.at(0)))
    {
      Deity* deity = CreatureUtils::get_random_deity_for_race(sel_race);

      if (deity != nullptr)
      {
        selected_deity_id = deity->get_id();
      }
    }
    else
    {
      int deity_idx = Char::keyboard_selection_char_to_int(deity_index.at(0));

      for (uint i = 0; i < deity_ids.size(); i++)
      {
        if (static_cast<int>(i) == deity_idx)
        {
          selected_deity_id = deity_ids.at(i);
          break;
        }
      }

      // If we selected something, but we didn't find the ID, assume it's
      // the Godless ID.
      if (selected_deity_id.empty())
      {
        selected_deity_id = ReligionConstants::DEITY_ID_GODLESS;
      }
    }
  }
}

void CharacterSelection::select_starting_location(DisplayPtr display, const CreatureSex sex, Race* sel_race, Class* sel_class, const string& selected_deity_id, string& creature_synopsis, StartingLocation& sl)
{
  Game& game = Game::instance();
  string default_starting_location_id = game.get_settings_ref().get_setting(Setting::DEFAULT_STARTING_LOCATION_ID);
  StartingLocationMap sm = game.get_starting_locations();
  auto sm_it = sm.find(default_starting_location_id);
  Option opt;

  if (sm_it != sm.end())
  {
    sl = sm_it->second;
  }
  else
  {
    creature_synopsis = TextMessages::get_character_creation_synopsis(sex, sel_race, sel_class, selected_deity_id, nullptr);
    StartingLocationSelectionScreen sl_selection(display, creature_synopsis, sm);
    string sl_sidx = sl_selection.display();

    if (opt.is_random_option(sl_sidx.at(0)))
    {
      sl = GameUtils::get_random_starting_location(sm);
    }
    else
    {
      int sl_idx = Char::keyboard_selection_char_to_int(sl_sidx.at(0));
      string selected_starting_location_id = Integer::to_string_key_at_given_position_in_map(sm, sl_idx);
      sl = sm.find(selected_starting_location_id)->second;
    }
  }
}
