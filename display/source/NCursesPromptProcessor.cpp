#include "NCursesPromptProcessor.hpp"

using namespace std;

// JCD FIXME: Refactor.  Subclasses?  Split up into PromptReader/PromptWriter with applicable subclasses?
string NCursesPromptProcessor::get_prompt(WINDOW* window, PromptPtr prompt)
{
  string prompt_entry;

  if (prompt)
  {
    PromptType pt = prompt->get_type();

    // JCD FIX THIS LATER
    if (pt == PROMPT_TYPE_TEXT)
    {
      echo();
      char text[10000];
      wgetnstr(window, text, 10000);
      prompt_entry = text;
      noecho();
    }
    else
    {
      prompt_entry = wgetch(window);
    }
  }

  return prompt_entry;
}

// JCD: Still unwieldy.  Fix.
void NCursesPromptProcessor::show_prompt(WINDOW* window, PromptPtr prompt, int row, int col, int TERMINAL_MAX_ROWS, int TERMINAL_MAX_COLS)
{
  string empty_string;
  int prompt_row = row;
  int prompt_col = col;
  string prompt_text = prompt->get_text();
  PromptLocation location = prompt->get_location();

  if (location == PROMPT_LOCATION_LOWER_RIGHT)
  {
    int prompt_text_length = prompt_text.size();
    prompt_col = TERMINAL_MAX_COLS - prompt_text_length - 1;
    prompt_row = TERMINAL_MAX_ROWS - 1;
  }

  mvwprintw(window, prompt_row, prompt_col, prompt_text.c_str());
  wrefresh(window);
}
