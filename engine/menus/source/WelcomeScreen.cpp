#include "global_prototypes.hpp"
#include "StringConstants.hpp"
#include "StringTable.hpp"
#include <boost/make_shared.hpp>
#include "WelcomeScreen.hpp"

using namespace std;
using boost::make_shared;

WelcomeScreen::WelcomeScreen(DisplayPtr new_display) : Menu(new_display)
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

  user_prompt = make_shared<AnyKeyPrompt>();
}
