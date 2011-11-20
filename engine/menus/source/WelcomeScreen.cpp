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
  TextComponent* game_version_synopsis = new TextComponent(get_game_version_synopsis());
  TextComponent* copyright_info = new TextComponent(StringTable::get(TextKeys::COPYRIGHT_NOTICE));
  TextComponent* wanderer_excerpt = new TextComponent(get_title_poem());

  components.push_back(game_version_synopsis);
  components.push_back(copyright_info);
  components.push_back(wanderer_excerpt);

  user_prompt = PromptPtr(new AnyKeyPrompt());
}
