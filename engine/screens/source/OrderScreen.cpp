#include "TextComponent.hpp"
#include "OptionsComponent.hpp"
#include "PromptTextKeys.hpp"
#include "OrderScreen.hpp"
#include "OrderTextKeys.hpp"
#include "PromptTextKeys.hpp"
#include "ScreenTitleTextKeys.hpp"
#include "StringTable.hpp"

using namespace std;

OrderScreen::OrderScreen(DisplayPtr new_display, const bool new_followers_exist_in_fov, const bool new_can_summon)
: Screen(new_display), followers_exist_in_fov(new_followers_exist_in_fov), can_summon(new_can_summon)
{
  initialize();
}

void OrderScreen::initialize()
{
  title_text_sid = ScreenTitleTextKeys::SCREEN_TITLE_GIVE_ORDERS;

  vector<ScreenComponentPtr> order_screen;
  OptionsComponentPtr options = std::make_shared<OptionsComponent>();

  vector<string> options_v = {};
  int cur_id = 0;

  if (followers_exist_in_fov)
  {
    options_v = {OrderTextKeys::ORDER_ATTACK, OrderTextKeys::ORDER_FOLLOW, OrderTextKeys::ORDER_FREEZE, OrderTextKeys::ORDER_AT_EASE};
  }

  if (can_summon)
  {
    // If there are no creatures in view, remove the options to attack/follow/freeze/etc.
    if (options_v.empty())
    {
      cur_id = 4;
    }

    options_v.push_back(OrderTextKeys::ORDER_SUMMON);
  }

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
  PromptPtr order_prompt = std::make_unique<Prompt>(PromptLocation::PROMPT_LOCATION_LOWER_RIGHT);
  order_prompt->set_accept_any_input(true);
  order_prompt->set_text_sid(PromptTextKeys::PROMPT_ORDER);
  user_prompt = std::move(order_prompt);
}
