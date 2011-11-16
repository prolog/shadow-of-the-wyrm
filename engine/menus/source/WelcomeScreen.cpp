#include "global_prototypes.hpp"
#include "StringConstants.hpp"
#include "StringTable.hpp"
#include "WelcomeScreen.hpp"

using namespace std;

WelcomeScreen::WelcomeScreen(DisplayPtr display) : Menu(display)
{
  initialize();
}

// The Welcome screen - contains game version info and copyright
// information, and an prompt to continue
void WelcomeScreen::initialize()
{
  TextComponent game_version_synopsis(get_game_version_synopsis());
  TextComponent copyright_info(StringTable::get(TextKeys::COPYRIGHT_NOTICE));
  TextComponent wanderer_excerpt(get_title_poem());

  text.push_back(game_version_synopsis);
  text.push_back(copyright_info);
  text.push_back(wanderer_excerpt);

  user_prompt = PromptPtr(new AnyKeyPrompt());
}
