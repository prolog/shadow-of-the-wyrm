#include "global_prototypes.hpp"
#include "PromptTextKeys.hpp"
#include "StringTable.hpp"
#include "TextDisplayScreen.hpp"
#include "TextFormatSpecifiers.hpp"

using namespace std;
using namespace boost::algorithm;

TextDisplayScreen::TextDisplayScreen(DisplayPtr new_display, const std::string& new_title_text_sid, const vector<TextDisplayPair>& new_text, const bool preserve_formatting, const deque<Symbol>& rsyms)
: Screen(new_display), text(new_text), replacement_symbols(rsyms)
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

  if (add_text(text_screen, text, replacement_symbols, preserve_formatting, cnt))
  {
    add_page(text_screen);
  }

  // Set the prompt
  PromptPtr any_key_prompt = std::make_shared<Prompt>(PromptLocation::PROMPT_LOCATION_LOWER_RIGHT);
  any_key_prompt->set_accept_any_input(true);
  any_key_prompt->set_text_sid(PromptTextKeys::get_appropriate_prompt_sid(get_num_pages()));
  user_prompt = any_key_prompt;
}
