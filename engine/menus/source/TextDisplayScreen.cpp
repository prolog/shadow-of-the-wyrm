#include <boost/foreach.hpp>
#include <boost/make_shared.hpp>
#include "global_prototypes.hpp"
#include "PromptTextKeys.hpp"
#include "StringTable.hpp"
#include "TextDisplayScreen.hpp"

using namespace std;

TextDisplayScreen::TextDisplayScreen(DisplayPtr new_display, const std::string& new_title_text_sid, const vector<TextDisplayPair>& new_text) : Menu(new_display), text(new_text)
{
  // Set the line increment to 1, so that single-spacing between lines is
  // enforced.  Otherwise, things will look goofy.
  line_increment = 1;

  initialize(new_title_text_sid);
}

void TextDisplayScreen::initialize(const string& title_sid)
{
  // Set the title text.
  title_text_sid = title_sid;

  // Set the text components.
  BOOST_FOREACH(TextDisplayPair line_pair, text)
  {
    TextComponentPtr current_line = boost::make_shared<TextComponent>(line_pair.second, line_pair.first);
    components.push_back(current_line);
  }

  // Set the prompt
  PromptPtr any_key_prompt = boost::make_shared<Prompt>(PROMPT_LOCATION_LOWER_RIGHT);
  any_key_prompt->set_text_sid(PromptTextKeys::PROMPT_ANY_KEY);
  user_prompt = any_key_prompt;
}
