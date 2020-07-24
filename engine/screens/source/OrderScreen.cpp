#include "TextComponent.hpp"
#include "OptionsComponent.hpp"
#include "PromptTextKeys.hpp"
#include "OrderScreen.hpp"
#include "OrderTextKeys.hpp"
#include "ScreenTitleTextKeys.hpp"
#include "StringTable.hpp"
#include "TextKeys.hpp"

using namespace std;

OrderScreen::OrderScreen(DisplayPtr new_display)
: Screen(new_display)
{
  initialize();
}

void OrderScreen::initialize()
{
  title_text_sid = ScreenTitleTextKeys::SCREEN_TITLE_GIVE_ORDERS;

  vector<ScreenComponentPtr> order_screen;
  OptionsComponentPtr options = std::make_shared<OptionsComponent>();

  vector<string> options_v = { OrderTextKeys::ORDER_ATTACK, OrderTextKeys::ORDER_FOLLOW, OrderTextKeys::ORDER_GUARD, OrderTextKeys::ORDER_FREEZE };
  int cur_id = 0;

  for (const auto& option_s : options_v)
  {
    Option current_option;
    current_option.set_id(cur_id++);
    current_option.set_description(StringTable::get(option_s));

    options->add_option(current_option);
    options->add_option_description("");
  }

  order_screen.push_back(options);
  add_page(order_screen);

  // Set the prompt
  PromptPtr any_key_prompt = std::make_unique<Prompt>(PromptLocation::PROMPT_LOCATION_LOWER_RIGHT);
  any_key_prompt->set_text_sid(PromptTextKeys::PROMPT_SELECT_AN_OPTION);
  user_prompt = std::move(any_key_prompt);
}
