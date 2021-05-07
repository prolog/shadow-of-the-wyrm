#include "ColourTextKeys.hpp"
#include "CreatureFeatures.hpp"
#include "TextComponent.hpp"
#include "OptionsComponent.hpp"
#include "PromptTextKeys.hpp"
#include "EyeSelectionScreen.hpp"
#include "StringTable.hpp"
#include "TextKeys.hpp"

using namespace std;

EyeSelectionScreen::EyeSelectionScreen(DisplayPtr new_display, const string& synopsis)
: Screen(new_display), creature_synopsis(synopsis)
{
  initialize();
}

void EyeSelectionScreen::initialize()
{
  TextComponentPtr eye_selection_text = std::make_shared<TextComponent>(StringTable::get(TextKeys::SELECT_EYE_COLOUR));

  vector<ScreenComponentPtr> eye_screen;
  vector<EyeColour> eye_colours;
  
  for (int i = static_cast<int>(EyeColour::EYE_COLOUR_FIRST); i <= static_cast<int>(EyeColour::EYE_COLOUR_LAST); i++)
  {
    eye_colours.push_back(static_cast<EyeColour>(i));
  }

  OptionsComponentPtr options = std::make_shared<OptionsComponent>();

  for (const EyeColour ec : eye_colours)
  {
    Option option_ec;
    option_ec.set_id(static_cast<int>(ec));
    option_ec.set_description(StringTable::get(ColourTextKeys::get_colour_sid_from_eye_colour(ec)));

    options->add_option(option_ec);
    options->add_option_description("");
  }

  // Random selection (use '*')
  Option random_option;
  random_option.set_id(random_option.get_id_for_random());
  random_option.set_description(StringTable::get(TextKeys::RANDOM_SELECTION));

  options->add_option(random_option);
  options->add_option_description("");

  TextComponentPtr synopsis = std::make_shared<TextComponent>("[" + creature_synopsis + "]");
  eye_screen.push_back(synopsis);
  eye_screen.push_back(eye_selection_text);
  eye_screen.push_back(options);
  add_page(eye_screen);

  // Set the prompt
  PromptPtr select_prompt = std::make_unique<Prompt>(PromptLocation::PROMPT_LOCATION_LOWER_RIGHT);
  select_prompt->set_text_sid(PromptTextKeys::PROMPT_SELECT_AN_OPTION);
  user_prompt = std::move(select_prompt);
}
