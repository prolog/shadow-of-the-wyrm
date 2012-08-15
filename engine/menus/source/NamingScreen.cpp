#include <boost/make_shared.hpp>
#include "NamingScreen.hpp"
#include "StringConstants.hpp"

using boost::make_shared;

NamingScreen::NamingScreen(DisplayPtr new_display) : Menu(new_display)
{
  initialize();
}

void NamingScreen::initialize()
{
  std::string empty_str = "";
  TextComponent* empty = new TextComponent(empty_str);
  TextComponent* more_emptiness = new TextComponent(empty_str);

  components.push_back(empty);
  components.push_back(more_emptiness);

  user_prompt = make_shared<TextPrompt>();
  user_prompt->set_text_sid(PromptTextKeys::PROMPT_ENTER_YOUR_NAME);
}
