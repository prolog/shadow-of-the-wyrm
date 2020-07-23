#include "TextComponent.hpp"
#include "OptionsComponent.hpp"
#include "PromptTextKeys.hpp"
#include "OrderScreen.hpp"
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

  // Set the prompt
  PromptPtr any_key_prompt = std::make_unique<Prompt>(PromptLocation::PROMPT_LOCATION_LOWER_RIGHT);
  any_key_prompt->set_text_sid(PromptTextKeys::PROMPT_SELECT_AN_OPTION);
  user_prompt = std::move(any_key_prompt);
}
