#include <boost/make_shared.hpp>
#include "NamingScreen.hpp"
#include "PromptTextKeys.hpp"

using namespace std;

NamingScreen::NamingScreen(DisplayPtr new_display, const string& warning) 
: Menu(new_display), warning_message(warning)
{
  initialize();
}

void NamingScreen::initialize()
{
  string optional_message;
  string empty_str;

  if (!warning_message.empty())
  {
    optional_message = warning_message;
  }

  TextComponentPtr optional_warning_message = boost::make_shared<TextComponent>(optional_message);
  TextComponentPtr blank_space = boost::make_shared<TextComponent>(empty_str);

  components.push_back(optional_warning_message);
  components.push_back(blank_space);

  user_prompt = boost::make_shared<TextPrompt>();
  user_prompt->set_text_sid(PromptTextKeys::PROMPT_ENTER_YOUR_NAME);
}
