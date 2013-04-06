#include <boost/make_shared.hpp>
#include "CreatureFeatures.hpp"
#include "TextComponent.hpp"
#include "OptionsComponent.hpp"
#include "SexSelectionScreen.hpp"
#include "StringTable.hpp"
#include "TextKeys.hpp"

using namespace std;

SexSelectionScreen::SexSelectionScreen(DisplayPtr new_display)
: Menu(new_display)
{
  initialize();
}

void SexSelectionScreen::initialize()
{
  TextComponentPtr sex_selection_text = boost::make_shared<TextComponent>(StringTable::get(TextKeys::SELECT_SEX));

  OptionsComponentPtr options = boost::make_shared<OptionsComponent>();
  string male = StringTable::get(TextKeys::SEX_MALE);
  string female = StringTable::get(TextKeys::SEX_FEMALE);

  Option option_male;
  option_male.set_id(CREATURE_SEX_MALE);
  option_male.set_description(male);

  Option option_female;
  option_female.set_id(CREATURE_SEX_FEMALE);
  option_female.set_description(female);

  options->add_option(option_male);
  options->add_option_description("");
  options->add_option(option_female);
  options->add_option_description("");

  components.push_back(sex_selection_text);
  components.push_back(options);
}
