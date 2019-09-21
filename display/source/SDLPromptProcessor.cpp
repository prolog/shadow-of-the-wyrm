#include <ctype.h>
#include "Conversion.hpp"
#include "CursesConstants.hpp"
#include "Log.hpp"
#include "SDLKeyboardController.hpp"
#include "SDLPromptProcessor.hpp"

using namespace std;

bool SDLPromptProcessor::operator==(const SDLPromptProcessor& cpp) const
{
  return true;
}

string SDLPromptProcessor::get_prompt(const SDLDisplayParameters& display_params, SDLCursorLocation& cursor_location, SDLRenderPtr render, SDL_Renderer* sdl_renderer, SDL_Texture* spritesheet, SDL_Texture* screen, const MenuWrapper& menu_wrapper, PromptPtr prompt)
{
  string prompt_entry;

  if (prompt)
  {
    PromptType pt = prompt->get_type();

    if (pt == PromptType::PROMPT_TYPE_TEXT)
    {
      prompt_entry = get_user_string(display_params, cursor_location, render, sdl_renderer, spritesheet, screen);
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
string SDLPromptProcessor::get_user_string(const SDLDisplayParameters& display_params, SDLCursorLocation& cursor_location, SDLRenderPtr render, SDL_Renderer* sdl_renderer, SDL_Texture* spritesheet, SDL_Texture* screen, bool allow_nonalphanumeric)
{
  string prompt_text;
  SDLKeyboardController kc;

  try
  {
    bool update = false;
    Coordinate original_yx = cursor_location.get_yx();

    for (char c = kc.get_char_as_int(); (c != '\n') && (c != '\r'); c = kc.get_char_as_int())
    {
      update = false;
      Coordinate yx = cursor_location.get_yx();

      if (c == NC_BACKSPACE_KEY || c == NC_ALTERNATIVE_BACKSPACE_KEY)
      {
        if (prompt_text.length() && (yx.first >= original_yx.first && yx.second >= original_yx.second))
        {
          cursor_location.decr();
          yx = cursor_location.get_yx();
          prompt_text.erase(prompt_text.end() - 1);
          render->render_text(cursor_location, sdl_renderer, spritesheet, screen, yx.first, yx.second, ' ', display_params.get_fg_colour(), display_params.get_bg_colour());
          cursor_location.decr();

          update = true;
        }
      }
      else
      {
        if ((isalpha(c) || isdigit(c) || (c == ' ')) || allow_nonalphanumeric)
        {
          prompt_text.push_back(c);
          render->render_text(cursor_location, sdl_renderer, spritesheet, screen, yx.first, yx.second, c, display_params.get_fg_colour(), display_params.get_bg_colour());
          update = true;
        }
      }

      if (update)
      {
        SDL_SetRenderTarget(sdl_renderer, NULL);
        SDL_RenderCopy(sdl_renderer, screen, NULL, NULL);
        SDL_RenderPresent(sdl_renderer);
        SDL_SetRenderTarget(sdl_renderer, screen);

        update = false;
      }
    }
  }
  catch (...)
  {
    // Do nothing, and use an empty string for the prompt text.
  }

  string result = String::clean(prompt_text);
  return result;
}

// Gets the item index of the selected menu item.
int SDLPromptProcessor::get_prompt(SDL_Window* window)
{
  int prompt_val;

  SDLKeyboardController kc;
  prompt_val = kc.get_char_as_int();

  return prompt_val;
}

void SDLPromptProcessor::show_prompt(const SDLDisplayParameters& display_params, SDLCursorLocation& cursor_location, SDLRenderPtr render, SDL_Renderer* sdl_renderer, SDL_Texture* spritesheet, SDL_Texture* screen, PromptPtr prompt, int row, int col, int TERMINAL_MAX_ROWS, int TERMINAL_MAX_COLS)
{
  if (render != nullptr && sdl_renderer != nullptr && spritesheet != nullptr && screen != nullptr && prompt != nullptr)
  {
    string prompt_text = prompt->get_text();

    Coordinate c = get_prompt_coords(prompt->get_location(), prompt_text, row, col, TERMINAL_MAX_ROWS, TERMINAL_MAX_COLS);
    render->render_text(cursor_location, sdl_renderer, spritesheet, screen, c.first, c.second, prompt_text, display_params.get_fg_colour(), display_params.get_bg_colour());
  }
}
