#include "NCursesConstants.hpp"
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

// Gets the item index of the selected menu item.
int NCursesPromptProcessor::get_prompt(WINDOW* window, MENU* options_menu)
{
  int c = wgetch(window);
  while (c != NC_ENTER_KEY)
  {
    switch(c)
    {
      case KEY_DOWN:
        menu_driver(options_menu, REQ_DOWN_ITEM);
        break;
      case KEY_UP:
        menu_driver(options_menu, REQ_UP_ITEM);
        break;
      default:
        break;
    }

    c = wgetch(window);
  }

  return item_index(current_item(options_menu));
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
