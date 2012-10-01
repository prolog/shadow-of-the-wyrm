#include <boost/make_shared.hpp>
#include "global_prototypes.hpp"
#include "StringConstants.hpp"
#include "StringTable.hpp"
#include "WelcomeScreen.hpp"

using namespace std;

WelcomeScreen::WelcomeScreen(DisplayPtr new_display) : Menu(new_display)
{
  initialize();
}

// The Welcome screen - contains game version info and copyright
// information, and an prompt to continue
void WelcomeScreen::initialize()
{
  TextComponentPtr game_version_synopsis = boost::make_shared<TextComponent>(get_game_version_synopsis());
  TextComponentPtr copyright_info = boost::make_shared<TextComponent>(StringTable::get(TextKeys::COPYRIGHT_NOTICE));
  TextComponentPtr wanderer_excerpt = boost::make_shared<TextComponent>(get_title_poem());

  components.push_back(game_version_synopsis);
  components.push_back(copyright_info);
  components.push_back(wanderer_excerpt);

  user_prompt = boost::make_shared<AnyKeyPrompt>();
}
