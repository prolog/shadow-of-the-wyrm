#include <ctype.h>
#include "Conversion.hpp"
#include "Log.hpp"
#include "CursesConstants.hpp"
#include "CursesPromptProcessor.hpp"

using namespace std;

bool CursesPromptProcessor::operator==(const CursesPromptProcessor& cpp) const
{
  // Stateless, return true.
  return true;
}

// JCD FIXME: Refactor.  Subclasses?  Split up into PromptReader/PromptWriter with applicable subclasses?
string CursesPromptProcessor::get_prompt(WINDOW* window, const MenuWrapper& menu_wrapper, Prompt* prompt)
{
  string prompt_entry;

  if (prompt)
  {
    PromptType pt = prompt->get_type();

    // JCD FIX THIS LATER
    if (pt == PromptType::PROMPT_TYPE_TEXT)
    {
      prompt_entry = get_user_string(window);
    }
    else
    {
      prompt_entry = wgetch(window);

      // Reprompt for new input if the input must be in the menu's option range,
      // and if the given input does not meet that criterion.
      while (!prompt->get_accept_any_input() 
           && menu_wrapper.has_options() 
           // Is the option itself there?
           && !menu_wrapper.is_option_in_set(prompt_entry.at(0)))
      {
        prompt_entry = wgetch(window);
      }
    }
  }

  return prompt_entry;
}

// Get a prompt from the user
string CursesPromptProcessor::get_user_string(WINDOW* window, bool allow_nonalphanumeric, const std::string& default_for_esc_key)
{
  string prompt_text;
  char c = '?';
  int y = 0, x = 0;
        
  try
  {
    for (c = wgetch(window); (c != '\n') && (c != '\r') && (c != NC_ESCAPE_KEY); c = wgetch(window))
    {
      getyx(window, y, x);

      if (c == NC_BACKSPACE_KEY || c == NC_ALTERNATIVE_BACKSPACE_KEY)
      {
        if (prompt_text.length())
        {
          prompt_text.erase(prompt_text.end() - 1);
          mvwaddch(window, y, x - 1, ' ');
          wmove(window, y, x - 1);
          wrefresh(window);
        }
      }
      else if (c == NC_ESCAPE_KEY)
      {
        prompt_text = default_for_esc_key;
      }
      else
      {
        if ((isalpha(c) || isdigit(c) || (c == ' ')) || allow_nonalphanumeric)
        {
          prompt_text.push_back(c);
          mvwaddch(window, y, x++, c);
          wrefresh(window);
        }
      }
    }
  }
  catch (...)
  {
    // Do nothing, and use an empty string for the prompt text.
  }
  
  if (c == NC_ESCAPE_KEY)
  {
    prompt_text = default_for_esc_key;
  }

  string result = String::clean(prompt_text);  
  return result;
}

// Gets the item index of the selected menu item.
int CursesPromptProcessor::get_prompt(WINDOW* window/*, MENU* options_menu*/)
{
  int c = wgetch(window);

  /*
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
      case KEY_LEFT:
        menu_driver(options_menu, REQ_LEFT_ITEM);
        break;
      case KEY_RIGHT:
        menu_driver(options_menu, REQ_RIGHT_ITEM);
        break;
      case NC_BACKSPACE_KEY:
        menu_driver(options_menu, REQ_CLEAR_PATTERN);
        menu_driver(options_menu, REQ_FIRST_ITEM);
        break;
      case KEY_HOME:
        menu_driver(options_menu, REQ_FIRST_ITEM);
        break;
      case KEY_END:
        menu_driver(options_menu, REQ_LAST_ITEM);
        break;
      default:
        if (isalpha(c))
        {
          menu_driver(options_menu, c);
        }

        break;
    }

    c = wgetch(window);
  }
  
  int item_idx = item_index(current_item(options_menu));
  return item_idx;
  */

  return c; // JCD FIXME
}

void CursesPromptProcessor::show_prompt(WINDOW* window, Prompt* prompt, int row, int col, int TERMINAL_MAX_ROWS, int TERMINAL_MAX_COLS)
{
  if (prompt != nullptr)
  {
    Coordinate c = get_prompt_coords(prompt->get_location(), prompt->get_text(), row, col, TERMINAL_MAX_ROWS, TERMINAL_MAX_COLS);

    mvwprintw(window, c.first, c.second, prompt->get_text().c_str());
    wrefresh(window);
  }
}
