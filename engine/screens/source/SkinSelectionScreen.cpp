#include "TextComponent.hpp"
#include "OptionsComponent.hpp"
#include "PromptTextKeys.hpp"
#include "SkinSelectionScreen.hpp"
#include "StringTable.hpp"
#include "TextKeys.hpp"
#include "EquipmentTextKeys.hpp"

using namespace std;

SkinSelectionScreen::SkinSelectionScreen(DisplayPtr new_display)
: Screen(new_display)
{
  initialize();
}

void SkinSelectionScreen::initialize()
{
  vector<ScreenComponentPtr> skin_screen;

  title_text_sid = TextKeys::SELECT_EQUIPMENT_WORN_LOCATION;

  vector<EquipmentWornLocation> valid_skin_locations = {EQUIPMENT_WORN_HEAD, EQUIPMENT_WORN_BODY, EQUIPMENT_WORN_AROUND_BODY, EQUIPMENT_WORN_FEET};

  for (EquipmentWornLocation worn_location : valid_skin_locations)
  {
    string worn_location_name = EquipmentTextKeys::get_equipment_text_from_given_worn_location(worn_location);

    OptionsComponentPtr options = std::make_shared<OptionsComponent>();
    Option current_option;
    TextComponentPtr option_text_component = current_option.get_description();
    option_text_component->add_text(worn_location_name);

    current_option.set_id(worn_location);

    options->add_option(current_option);
    options->add_option_description("");

    skin_screen.push_back(options);
  }

  add_page(skin_screen);

  // Set the prompt
  PromptPtr skin_prompt = std::make_shared<Prompt>(PROMPT_LOCATION_LOWER_RIGHT);

  // Accept any input - the equipment manager will take care of sorting out
  // what's a valid command and what is not.
  skin_prompt->set_accept_any_input(true);
  skin_prompt->set_text_sid(TextKeys::SKIN_PROMPT);
  user_prompt = skin_prompt;
}
