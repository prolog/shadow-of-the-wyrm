#include "TextComponent.hpp"
#include "OptionsComponent.hpp"
#include "PromptTextKeys.hpp"
#include "WornLocationSelectionScreen.hpp"
#include "StringTable.hpp"
#include "TextKeys.hpp"
#include "EquipmentTextKeys.hpp"

using namespace std;

WornLocationSelectionScreen::WornLocationSelectionScreen(DisplayPtr new_display, const vector<EquipmentWornLocation>& new_worn_locs, const string& new_prompt_text_sid)
: Screen(new_display), worn_locs(new_worn_locs), prompt_text_sid(new_prompt_text_sid)
{
  initialize();
}

vector<EquipmentWornLocation> WornLocationSelectionScreen::get_worn_locs()
{
  return worn_locs;
}

void WornLocationSelectionScreen::initialize()
{
  vector<ScreenComponentPtr> slot_screen;

  title_text_sid = TextKeys::SELECT_EQUIPMENT_WORN_LOCATION;

  for (EquipmentWornLocation worn_location : worn_locs)
  {
    string worn_location_name = EquipmentTextKeys::get_equipment_text_from_given_worn_location(worn_location);

    OptionsComponentPtr options = std::make_shared<OptionsComponent>();
    Option current_option;
    TextComponentPtr option_text_component = current_option.get_description();
    option_text_component->add_text(worn_location_name);

    current_option.set_id(worn_location);

    options->add_option(current_option);
    options->add_option_description("");

    slot_screen.push_back(options);
  }

  add_page(slot_screen);

  // Set the prompt
  PromptPtr slot_prompt = std::make_shared<Prompt>(PROMPT_LOCATION_LOWER_RIGHT);

  // Accept any input - the equipment manager will take care of sorting out
  // what's a valid command and what is not.
  slot_prompt->set_accept_any_input(true);
  slot_prompt->set_text_sid(prompt_text_sid);
  user_prompt = slot_prompt;
}
