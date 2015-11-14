#include <sstream>
#include "NamingScreen.hpp"
#include "PromptTextKeys.hpp"

using namespace std;

NamingScreen::NamingScreen(DisplayPtr new_display, const string& synop, const string& warning) 
: Screen(new_display), creature_synopsis(synop), warning_message(warning)
{
  initialize();
}

void NamingScreen::initialize()
{
  string optional_message;
  string empty_str;
  ostringstream synop;

  vector<ScreenComponentPtr> naming_screen;

  if (!warning_message.empty())
  {
    optional_message = warning_message;
  }

  synop << "[" << creature_synopsis << "]";

  TextComponentPtr blank_space = std::make_shared<TextComponent>(empty_str);

  naming_screen.push_back(make_shared<TextComponent>(synop.str()));

  if (!optional_message.empty())
  {
    naming_screen.push_back(make_shared<TextComponent>(optional_message));
    naming_screen.push_back(make_shared<TextComponent>(empty_str));
  }

  user_prompt = std::make_shared<TextPrompt>();
  user_prompt->set_text_sid(PromptTextKeys::PROMPT_ENTER_YOUR_NAME);

  add_page(naming_screen);
}
