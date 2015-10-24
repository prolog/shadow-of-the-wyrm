#include <boost/algorithm/string.hpp>
#include "global_prototypes.hpp"
#include "PromptTextKeys.hpp"
#include "StringTable.hpp"
#include "TextDisplayScreen.hpp"
#include "TextFormatSpecifiers.hpp"

using namespace std;
using namespace boost::algorithm;

TextDisplayScreen::TextDisplayScreen(DisplayPtr new_display, const std::string& new_title_text_sid, const vector<TextDisplayPair>& new_text, const bool preserve_formatting)
: Screen(new_display), text(new_text)
{
  // Set the line increment to 1, so that single-spacing between lines is
  // enforced.  Otherwise, things will look goofy.
  line_increment = 1;

  initialize(new_title_text_sid, preserve_formatting);
}

void TextDisplayScreen::initialize(const string& title_sid, const bool preserve_formatting)
{
  // Set the title text.
  title_text_sid = title_sid;

  vector<ScreenComponentPtr> text_screen;
  int cnt = 0;

  // Set the text components.
  for (const TextDisplayPair& line_pair : text)
  {
    Colour colour = line_pair.first;
    string text = line_pair.second;

    if (preserve_formatting == false)
    {
      trim_left(text);
      trim_right(text);
    }

    TextComponentPtr current_line = std::make_shared<TextComponent>(text, colour);
    add_component(text_screen, current_line, cnt);

    cnt++;
  }

  add_page(text_screen);

  // Set the prompt
  PromptPtr any_key_prompt = std::make_shared<Prompt>(PromptLocation::PROMPT_LOCATION_LOWER_RIGHT);
  any_key_prompt->set_accept_any_input(true);
  any_key_prompt->set_text_sid(PromptTextKeys::get_appropriate_prompt_sid(get_num_pages()));
  user_prompt = any_key_prompt;
}
