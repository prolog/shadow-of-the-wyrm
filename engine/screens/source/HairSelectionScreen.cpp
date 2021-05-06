#include "ColourTextKeys.hpp"
#include "CreatureFeatures.hpp"
#include "TextComponent.hpp"
#include "OptionsComponent.hpp"
#include "PromptTextKeys.hpp"
#include "HairSelectionScreen.hpp"
#include "StringTable.hpp"
#include "TextKeys.hpp"

using namespace std;

HairSelectionScreen::HairSelectionScreen(DisplayPtr new_display)
: Screen(new_display)
{
  initialize();
}

void HairSelectionScreen::initialize()
{
  TextComponentPtr hair_selection_text = std::make_shared<TextComponent>(StringTable::get(TextKeys::SELECT_HAIR_COLOUR));

  vector<ScreenComponentPtr> hair_screen;
  vector<HairColour> hair_colours = { HairColour::HAIR_COLOUR_BLACK, HairColour::HAIR_COLOUR_BROWN, HairColour::HAIR_COLOUR_BLONDE, HairColour::HAIR_COLOUR_RED, HairColour::HAIR_COLOUR_GREY, HairColour::HAIR_COLOUR_WHITE };

  OptionsComponentPtr options = std::make_shared<OptionsComponent>();

  for (const HairColour hc : hair_colours)
  {
    Option option_hc;
    option_hc.set_id(static_cast<int>(hc));
    option_hc.set_description(StringTable::get(ColourTextKeys::get_colour_sid_from_hair_colour(hc)));

    options->add_option(option_hc);
    options->add_option_description("");
  }

  // Random selection (use '*')
  Option random_option;
  random_option.set_id(random_option.get_id_for_random());
  random_option.set_description(StringTable::get(TextKeys::RANDOM_SELECTION));

  options->add_option(random_option);
  options->add_option_description("");

  add_page(hair_screen);

  // Set the prompt
  PromptPtr select_prompt = std::make_unique<Prompt>(PromptLocation::PROMPT_LOCATION_LOWER_RIGHT);
  select_prompt->set_text_sid(PromptTextKeys::PROMPT_SELECT_AN_OPTION);
  user_prompt = std::move(select_prompt);
}
