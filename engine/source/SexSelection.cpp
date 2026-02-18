#include "Conversion.hpp"
#include "Game.hpp"
#include "OptionsComponent.hpp"
#include "RNG.hpp"
#include "SexSelection.hpp"
#include "SexSelectionScreen.hpp"
#include "StringTable.hpp"
#include "TextDisplayFormatter.hpp"
#include "TextDisplayScreen.hpp"
#include "TextKeys.hpp"

using namespace std;

void SexSelection::select_sex(DisplayPtr display, CreatureSex& sex)
{
  bool select_sex = true;
  Option opt;
  Game& game = Game::instance();

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