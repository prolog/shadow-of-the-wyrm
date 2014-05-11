#include "InventoryScreen.hpp"
#include "InventoryTranslator.hpp"
#include "OptionsComponent.hpp"
#include "Prompt.hpp"
#include "TextComponent.hpp"
#include "TextKeys.hpp"

using namespace std;

InventoryScreen::InventoryScreen(DisplayPtr new_display, CreaturePtr new_creature, const DisplayInventoryMap& new_dim)
: Menu(new_display), creature(new_creature), dim(new_dim)
{
  initialize();
}

void InventoryScreen::initialize()
{
  Inventory& inv = creature->get_inventory();
  vector<MenuComponentPtr> inv_menu;
  int current_id = 0;
  int cnt = 0;

  title_text_sid = TextKeys::INVENTORY;

  for (const auto& i_it : dim)
  {
    DisplayItemType display_item_type = i_it.first;
    vector<DisplayItem> display_items = i_it.second;

    // Display the category info
    string category_symbol = display_item_type.get_symbol();
    Colour category_colour = display_item_type.get_colour();
    string category_desc = display_item_type.get_description();
    string category_synopsis = category_desc + " - " + category_symbol;

    TextComponentPtr text = std::make_shared<TextComponent>(category_desc);
    text->add_text(" - ", COLOUR_WHITE);
    text->add_text(category_symbol, category_colour);

    add_component(inv_menu, text, cnt);
    cnt++;

    if (!display_items.empty())
    {
      for (DisplayItem item : display_items)
      {
        Option current_option;

        TextComponentPtr option_text_component = current_option.get_description();

        string item_description = item.get_description();
        Colour item_colour = item.get_colour();

        option_text_component->add_text(item_description, item_colour);

        DisplayItemFlagsVec flags = item.get_flags();
        for (const TextColour& tc : flags)
        {
          string flag_text = tc.first;
          Colour flag_col = tc.second;

          // Include sufficient spacing between each of the flags.
          option_text_component->add_text(" ", flag_col);
          option_text_component->add_text(flag_text, flag_col);
        }

        OptionsComponentPtr options = std::make_shared<OptionsComponent>();

        current_option.set_id(current_id);
        current_option.set_external_id(item.get_id());

        options->add_option(current_option);
        options->add_option_description("");

        cnt++;
        current_id++;

        add_component(inv_menu, options, cnt);
      }

      TextComponentPtr empty = std::make_shared<TextComponent>("");
      cnt++;
      add_component(inv_menu, empty, cnt);
    }
  }

  // Add the most recent page.
  add_page(inv_menu);

  // Set the prompt
  PromptPtr inv_prompt = std::make_shared<Prompt>(PROMPT_LOCATION_LOWER_RIGHT);

  // Accept any input to the inventory manager will take care of sorting out
  // what's a valid command and what is not.
  inv_prompt->set_accept_any_input(true);
  inv_prompt->set_text_sid(TextKeys::INVENTORY_PROMPT);
  user_prompt = inv_prompt;
  line_increment = 1;
}

