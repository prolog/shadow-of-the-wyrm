#include <ctype.h>
#include "Conversion.hpp"
#include "Log.hpp"
#include "SDLKeyboardController.hpp"
#include "SDLPromptProcessor.hpp"

using namespace std;

bool SDLPromptProcessor::operator==(const SDLPromptProcessor& cpp) const
{
  return true;
}

string SDLPromptProcessor::get_prompt(SDL_Window* window, const MenuWrapper& menu_wrapper, PromptPtr prompt)
{
  string prompt_entry;

  if (prompt)
  {
    PromptType pt = prompt->get_type();

    if (pt == PromptType::PROMPT_TYPE_TEXT)
    {
      prompt_entry = get_user_string(window);
    }
    else
    {
      SDLKeyboardController kc;
      prompt_entry = kc.get_char_as_int();

      // Reprompt for new input if the input must be in the menu's option range,
      // and if the given input does not meet that criterion.
      while (!prompt->get_accept_any_input()
        && menu_wrapper.has_options()
        // Is the option itself there?
        && !menu_wrapper.is_option_in_set(prompt_entry.at(0)))
      {
        prompt_entry = kc.get_char_as_int();
      }
    }
  }

  return prompt_entry;
}

// Get a prompt from the user
string SDLPromptProcessor::get_user_string(SDL_Window* window, bool allow_nonalphanumeric)
{
  string user_string;

  // JCD FIXME
  SDLKeyboardController kc;
  user_string = kc.get_line();

  return user_string;
}

// Gets the item index of the selected menu item.
int SDLPromptProcessor::get_prompt(SDL_Window* window)
{
  int prompt_val;

  SDLKeyboardController kc;
  prompt_val = kc.get_char_as_int();

  return prompt_val;
}

void SDLPromptProcessor::show_prompt(SDLTextRendererPtr renderer, PromptPtr prompt, int row, int col, int TERMINAL_MAX_ROWS, int TERMINAL_MAX_COLS)
{
  if (renderer != nullptr && prompt != nullptr)
  {
    string prompt_text = prompt->get_text();

    Coordinate c = get_prompt_coords(prompt->get_location(), prompt_text, row, col, TERMINAL_MAX_ROWS, TERMINAL_MAX_COLS);
    // JCD FIXME renderer->render_text(c.first, c.second, prompt_text);
  }
}
