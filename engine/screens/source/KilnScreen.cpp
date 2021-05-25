#include "KilnScreen.hpp"
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

  // ...

  // Set the prompt
  PromptPtr any_key_prompt = std::make_unique<Prompt>(PromptLocation::PROMPT_LOCATION_LOWER_RIGHT);
  any_key_prompt->set_accept_any_input(true);
  any_key_prompt->set_text_sid(PromptTextKeys::PROMPT_SELECT_AN_OPTION);
  user_prompt = std::move(any_key_prompt);
}
