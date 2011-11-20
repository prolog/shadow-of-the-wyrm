#include "NamingScreen.hpp"
#include "StringConstants.hpp"

NamingScreen::NamingScreen(DisplayPtr display) : Menu(display)
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

  user_prompt = PromptPtr(new TextPrompt());
  user_prompt->set_text_sid(PromptTextKeys::PROMPT_ENTER_YOUR_NAME);
}
