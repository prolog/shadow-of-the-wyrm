#include <boost/algorithm/string.hpp>
#include "global_prototypes.hpp"
#include "PromptTextKeys.hpp"
#include "StringTable.hpp"
#include "TextDisplayScreen.hpp"

using namespace std;
using namespace boost::algorithm;

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

  vector<MenuComponentPtr> text_menu;
  int cnt = 0;

  // Set the text components.
  for (const TextDisplayPair& line_pair : text)
  {
    Colour colour = line_pair.first;
    string text = line_pair.second;

    trim_left(text);
    trim_right(text);

    TextComponentPtr current_line = std::make_shared<TextComponent>(text, colour);

    text_menu.push_back(current_line);
    cnt++;

    if (cnt == LINES_DISPLAYABLE_AREA)
    {
      cnt = 0;

      add_page(text_menu);
      text_menu.clear();
    }
  }

  add_page(text_menu);

  // Set the prompt
  PromptPtr any_key_prompt = std::make_shared<Prompt>(PROMPT_LOCATION_LOWER_RIGHT);
  any_key_prompt->set_accept_any_input(true);
  any_key_prompt->set_text_sid(PromptTextKeys::get_appropriate_prompt_sid(get_num_pages()));
  user_prompt = any_key_prompt;
}
