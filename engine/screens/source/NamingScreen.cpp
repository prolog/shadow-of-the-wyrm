#include <sstream>
#include <boost/algorithm/string/replace.hpp>
#include "NamingScreen.hpp"
#include "PromptTextKeys.hpp"
#include "StringTable.hpp"

using namespace std;

NamingScreen::NamingScreen(DisplayPtr new_display, const string& new_class, const string& synop, const string& warning)
: Screen(new_display), creature_class(new_class), creature_synopsis(synop), warning_message(warning)
{
  if (!creature_class.empty())
  {
    creature_class[0] = static_cast<char>(std::tolower(creature_class[0]));
  }

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

  if (!creature_synopsis.empty())
  {
    synop << "[" << creature_synopsis << "]";
  }

  TextComponentPtr blank_space = std::make_shared<TextComponent>(empty_str);

  naming_screen.push_back(make_shared<TextComponent>(synop.str()));

  if (!optional_message.empty())
  {
    naming_screen.push_back(make_shared<TextComponent>(optional_message));
    naming_screen.push_back(make_shared<TextComponent>(empty_str));
  }

  user_prompt = std::make_unique<TextPrompt>();

  string prompt_text = StringTable::get(PromptTextKeys::PROMPT_ENTER_YOUR_NAME);
  boost::replace_first(prompt_text, "%s", creature_class);
  user_prompt->set_text_sid(prompt_text);

  add_page(naming_screen);
}
