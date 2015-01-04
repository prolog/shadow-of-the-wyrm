#include "HighScoreScreen.hpp"
#include "PromptTextKeys.hpp"
#include "ScoreTextKeys.hpp"

using namespace std;

HighScoreScreen::HighScoreScreen(DisplayPtr new_display, const vector<ScoreFileEntry>& new_sfe)
: Screen(new_display), sfe(new_sfe)
{
  line_increment = 1;
  initialize();
}

void HighScoreScreen::initialize()
{
  vector<ScreenComponentPtr> score_screen;

  title_text_sid = ScoreTextKeys::SCORE_HIGH_SCORES;
  int cnt = 0;
  int cur_pg = 0;
  int score_number = 1;

  // Add each entry.  If the entry is for the player, set the current page
  // appropriately, and display the entry in bold white text.
  for (const auto& entry : sfe)
  {
    // If the current score file entry is for the current character, make a note
    // of the page so that the right page can be displayed to the player.
    if (entry.get_is_current_char())
    {
      cur_page_idx = cur_pg;
    }

    Colour colour = entry.get_is_current_char() ? Colour::COLOUR_BOLD_WHITE : Colour::COLOUR_WHITE;
    string current_line = entry.str(score_number);

    TextComponentPtr text = std::make_shared<TextComponent>(current_line, colour);

    // When the text is displayed, it's on a new line after the previous entry,
    // so incr count by 2.
    cnt++;
    add_component(score_screen, text, cnt);

    TextComponentPtr separator = std::make_shared<TextComponent>("", Colour::COLOUR_WHITE);
    cnt++;
    add_component(score_screen, separator, cnt);

    if (cnt == 0)
    {
      cur_pg++;
    }   

    score_number++;
  }

  add_page(score_screen);

  // Set the prompt
  PromptPtr any_key_prompt = std::make_shared<Prompt>(PromptLocation::PROMPT_LOCATION_LOWER_RIGHT);
  any_key_prompt->set_accept_any_input(true);
  any_key_prompt->set_text_sid(PromptTextKeys::get_appropriate_prompt_sid(get_num_pages()));
  user_prompt = any_key_prompt;
}
