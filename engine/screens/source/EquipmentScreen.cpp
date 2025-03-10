#include "Conversion.hpp"
#include "EquipmentScreen.hpp"
#include "EquipmentTextKeys.hpp"
#include "EquipmentTranslator.hpp"
#include "Game.hpp"
#include "OptionsComponent.hpp"
#include "PromptTextKeys.hpp"
#include "TextComponent.hpp"
#include "TextKeys.hpp"

using namespace std;

EquipmentScreen::EquipmentScreen(DisplayPtr new_display, CreaturePtr new_creature)
: Screen(new_display), creature(new_creature)
{
  initialize();
}

// Initialize the equipment screen, showing the user the list of eq
// slots and displaying further information in the inventory prompt.
void EquipmentScreen::initialize()
{
  vector<ScreenComponentPtr> eq_screen;

  // Set the title information
  title_text_sid = TextKeys::EQUIPMENT;

  // Create the various options and text
  int current_id = 0;
  DisplayEquipmentMap dem = EquipmentTranslator::create_display_equipment(creature);

  uint longest = 0;
  for (DisplayEquipmentMap::const_iterator e_it = dem.begin(); e_it != dem.end(); e_it++)
  {
    EquipmentWornLocation worn_location = e_it->first;
    string worn_location_name = EquipmentTextKeys::get_equipment_text_from_given_worn_location(worn_location);
    if (worn_location_name.size() > longest) longest = worn_location_name.size() + 1;
  }

  for (DisplayEquipmentMap::const_iterator e_it = dem.begin(); e_it != dem.end(); e_it++)
  {
    ostringstream ss;

    EquipmentWornLocation worn_location = e_it->first;
    DisplayItem display_item = e_it->second;
    Colour item_colour = display_item.get_colour();

    string worn_location_name = EquipmentTextKeys::get_equipment_text_from_given_worn_location(worn_location);
    string item_description = display_item.get_description();

    ss << String::add_trailing_spaces(worn_location_name, longest) << ": ";

    vector<pair<string, Colour>> flags = display_item.get_flags();

    OptionsComponentPtr options = std::make_shared<OptionsComponent>();
    Option current_option;
    TextComponentPtr option_text_component = current_option.get_description();
    option_text_component->add_text(ss.str());
    option_text_component->add_text(item_description, item_colour);

    for (const TextColour& flag_pair : flags)
    {
      ostringstream flag_ss;
      flag_ss << " ";

      Colour colour = flag_pair.second;
      flag_ss << flag_pair.first;

      option_text_component->add_text(flag_ss.str(), colour);
    }

    current_option.set_id(current_id);

    options->add_option(current_option);
    options->add_option_description("");

    current_id++;

    eq_screen.push_back(options);

    string res_abrv = StringTable::get(EquipmentTextKeys::EQUIPMENT_RESISTS_FLAGS);
    string item_addl_desc;
    string di_addl_desc = display_item.get_additional_description();
    String::reset_and_pad(item_addl_desc, 6 /* 6 = extra padding for '[a] : ' */);

    // Only show the resistances abbreviation if the item's got anything...
    if (!di_addl_desc.empty())
    {
      ostringstream ss_di_addl;
      ss_di_addl << String::add_trailing_spaces(res_abrv, longest) << ": " << di_addl_desc;
      di_addl_desc = ss_di_addl.str();
    }

    item_addl_desc += di_addl_desc;
    TextComponentPtr eq_text = std::make_shared<TextComponent>(item_addl_desc, Colour::COLOUR_BOLD_YELLOW);
    eq_screen.push_back(eq_text);
  }

  // Enable the equipment screen
  add_page(eq_screen);

  // Set the prompt
  PromptPtr eq_prompt = std::make_unique<Prompt>(PromptLocation::PROMPT_LOCATION_LOWER_RIGHT);

  // Accept any input - the equipment manager will take care of sorting out
  // what's a valid command and what is not.
  eq_prompt->set_accept_any_input(true);
  eq_prompt->set_text_sid(PromptTextKeys::PROMPT_EQUIPMENT);
  user_prompt = std::move(eq_prompt);
  line_increment = 1;
}
