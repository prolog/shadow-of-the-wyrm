#pragma once
#ifdef _MSC_VER
#include <curses.h>
#else
#include <ncurses.h>
#endif
#include "Prompt.hpp"
#include "NCursesMenuWrapper.hpp"

// Handles the output of the prompt text and the reading of the prompt from the keyboard based on the type of
// prompt provided.
class NCursesPromptProcessor
{
  public:
    int get_prompt(WINDOW* window/*, MENU* menu*/);
    std::string get_prompt(WINDOW* window, const NCursesMenuWrapper& menu_wrapper, PromptPtr prompt);
    void show_prompt(WINDOW* window, PromptPtr prompt, int row, int col, int TERMINAL_MAX_ROWS, int TERMINAL_MAX_COLS);
    std::string get_user_string(WINDOW* window);
};
