#include <boost/make_shared.hpp>
#include "NamingScreen.hpp"
#include "StringConstants.hpp"


NamingScreen::NamingScreen(DisplayPtr new_display) : Menu(new_display)
{
  initialize();
}

void NamingScreen::initialize()
{
  std::string empty_str = "";
  TextComponentPtr empty = boost::make_shared<TextComponent>(empty_str);
  TextComponentPtr more_emptiness = boost::make_shared<TextComponent>(empty_str);

  components.push_back(empty);
  components.push_back(more_emptiness);

  user_prompt = boost::make_shared<TextPrompt>();
  user_prompt->set_text_sid(PromptTextKeys::PROMPT_ENTER_YOUR_NAME);
}
