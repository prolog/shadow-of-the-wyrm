#include "NamingScreen.hpp"
#include "StringConstants.hpp"

NamingScreen::NamingScreen(DisplayPtr display) : Menu(display)
{
  initialize();
}

void NamingScreen::initialize()
{
  TextComponent empty("");
  TextComponent more_emptiness("");

  text.push_back(empty);
  text.push_back(more_emptiness);

  user_prompt = PromptPtr(new TextPrompt());
  user_prompt->set_text_sid(PromptTextKeys::PROMPT_ENTER_YOUR_NAME);
}
