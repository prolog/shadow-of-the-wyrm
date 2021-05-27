#include "KilnScreen.hpp"
#include "ActionTextKeys.hpp"
#include "Game.hpp"
#include "OptionsComponent.hpp"
#include "PromptTextKeys.hpp"
#include "ScreenTitleTextKeys.hpp"
#include "TextComponent.hpp"
#include "TextKeys.hpp"

using namespace std;

KilnScreen::KilnScreen(DisplayPtr new_display, const bool fire_bomb, const bool shadow_bomb)
: Screen(new_display), allow_fire_bombs(fire_bomb), allow_shadow_bombs(shadow_bomb)
{
  initialize();
}

void KilnScreen::initialize()
{
  title_text_sid = ScreenTitleTextKeys::SCREEN_TITLE_KILN;
  vector<ScreenComponentPtr> kiln_screen;

  TextComponentPtr select_item = std::make_shared<TextComponent>(StringTable::get(ActionTextKeys::ACTION_KILN_CREATE_ITEM));
  kiln_screen.push_back(select_item);

  OptionsComponentPtr options = std::make_shared<OptionsComponent>();
  options->set_show_option_descriptions(false);

  vector<tuple<string, int, bool>> item_display_details = { {ItemIdKeys::ITEM_ID_CLAY_POT, 0, true}, {ItemIdKeys::ITEM_ID_CLAY_SHOT, 1, true} };
  item_display_details.push_back({ItemIdKeys::ITEM_ID_FIRE_BOMB, 2, allow_fire_bombs});
  item_display_details.push_back({ItemIdKeys::ITEM_ID_SHADOW_BOMB, 3, allow_shadow_bombs });

  const ItemMap& items = Game::instance().get_items_ref();

  for (const auto& i_detail : item_display_details)
  {
    auto i_it = items.find(std::get<0>(i_detail));

    if (i_it != items.end())
    {
      Option current_option;
      current_option.set_id(std::get<1>(i_detail));
      current_option.set_description(StringTable::get(i_it->second->get_description_sid()));
      current_option.set_enabled(std::get<2>(i_detail));

      options->add_option(current_option);
    }
  }

  kiln_screen.push_back(options);
  add_page(kiln_screen);

  // Set the prompt
  PromptPtr any_key_prompt = std::make_unique<Prompt>(PromptLocation::PROMPT_LOCATION_LOWER_RIGHT);
  any_key_prompt->set_accept_any_input(true);
  any_key_prompt->set_text_sid(PromptTextKeys::PROMPT_KILN);
  user_prompt = std::move(any_key_prompt);
}
