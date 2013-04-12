#include <boost/make_shared.hpp>
#include "SpellSelectionScreen.hpp"
#include "Game.hpp"
#include "MenuTitleTextKeys.hpp"
#include "OptionsComponent.hpp"
#include "SpellcastingTextKeys.hpp"
#include "TextComponent.hpp"
#include "TextKeys.hpp"

using namespace std;

SpellSelectionScreen::SpellSelectionScreen(DisplayPtr new_display, CreaturePtr player /* should only be shown for player! */)
: Menu(new_display), creature(player)
{
  initialize();
}

// Show the spell selection screen.
void SpellSelectionScreen::initialize()
{
  // Set the menu title.
  title_text_sid = MenuTitleKeys::MENU_TITLE_MAGIC_SPELLS;

  // Go through the player's spells, and add them as options.

  // Add the info prompt at the bottom of the screen.
  // Set the prompt
  PromptPtr spellcasting_prompt = boost::make_shared<Prompt>(PROMPT_LOCATION_LOWER_RIGHT);
  spellcasting_prompt->set_text_sid(SpellcastingTextKeys::SPELLCASTING_SCREEN_PROMPT);
  user_prompt = spellcasting_prompt;
}
