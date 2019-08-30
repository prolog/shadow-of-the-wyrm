#pragma once
#ifdef _MSC_VER
#include "SDL.h"
#else
#include "SDL2/SDL.h"
#endif
#include "Prompt.hpp"
#include "MenuWrapper.hpp"

// Handles prompts on a given sdl window.
class SDLPromptProcessor
{
  public:
    bool operator==(const SDLPromptProcessor& cpp) const;

    int get_prompt(SDL_Window* window);
    std::string get_prompt(SDL_Window* window, const MenuWrapper& menu_wrapper, PromptPtr prompt);
    void show_prompt(SDL_Window* window, PromptPtr prompt, int row, int col, int TERMINAL_MAX_ROWS, int TERMINAL_MAX_COLS);
    std::string get_user_string(SDL_Window* window, bool allow_nonalphanumeric = false);
};
