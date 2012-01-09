#pragma once
#include <ncurses/ncurses.h>
#include <ncurses/menu.h>
#include "Prompt.hpp"

// Handles the output of the prompt text and the reading of the prompt from the keyboard based on the type of
// prompt provided.
class NCursesPromptProcessor
{
  public:
    int get_prompt(WINDOW* window, MENU* menu);
    std::string get_prompt(WINDOW* window, PromptPtr prompt);
    void show_prompt(WINDOW* window, PromptPtr prompt, int row, int col, int TERMINAL_MAX_ROWS, int TERMINAL_MAX_COLS);

  protected:
    std::string get_user_string(WINDOW* window);
};
