#pragma once
#include "curses.hpp"

#include "MenuWrapper.hpp"
#include "Prompt.hpp"
#include "PromptProcessor.hpp"

// Handles the output of the prompt text and the reading of the prompt from the keyboard based on the type of
// prompt provided.
class CursesPromptProcessor : public PromptProcessor
{
  public:
    virtual ~CursesPromptProcessor() = default;
    bool operator==(const CursesPromptProcessor& cpp) const;

    int get_prompt(WINDOW* window);
    std::string get_prompt(WINDOW* window, const MenuWrapper& menu_wrapper, Prompt* prompt);
    void show_prompt(WINDOW* window, Prompt* prompt, int row, int col, int TERMINAL_MAX_ROWS, int TERMINAL_MAX_COLS);
    std::string get_user_string(WINDOW* window, bool allow_nonalphanumeric = false, const std::string& default_for_esc_key = "");
};
