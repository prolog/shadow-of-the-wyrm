#include "CreatureFeatures.hpp"
#include "TextComponent.hpp"
#include "OptionsComponent.hpp"
#include "PromptTextKeys.hpp"
#include "SexSelectionScreen.hpp"
#include "StringTable.hpp"
#include "TextKeys.hpp"

using namespace std;

SexSelectionScreen::SexSelectionScreen(DisplayPtr new_display)
: Screen(new_display)
{
  initialize();
}

void SexSelectionScreen::initialize()
{
  TextComponentPtr sex_selection_text = std::make_shared<TextComponent>(StringTable::get(TextKeys::SELECT_SEX));

  vector<ScreenComponentPtr> sex_screen;

  OptionsComponentPtr options = std::make_shared<OptionsComponent>();
  string male = StringTable::get(TextKeys::SEX_MALE);
  string female = StringTable::get(TextKeys::SEX_FEMALE);

  Option option_male;
  option_male.set_id(static_cast<int>(CreatureSex::CREATURE_SEX_MALE));
  option_male.set_description(male);

  Option option_female;
  option_female.set_id(static_cast<int>(CreatureSex::CREATURE_SEX_FEMALE));
  option_female.set_description(female);

  options->add_option(option_male);
  options->add_option_description("");
  options->add_option(option_female);
  options->add_option_description("");

  sex_screen.push_back(sex_selection_text);
  sex_screen.push_back(options);

  add_page(sex_screen);

  // Set the prompt
  PromptPtr any_key_prompt = std::make_shared<Prompt>(PromptLocation::PROMPT_LOCATION_LOWER_RIGHT);
  any_key_prompt->set_text_sid(PromptTextKeys::PROMPT_SELECT_AN_OPTION);
  user_prompt = any_key_prompt;
}
