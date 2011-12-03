#pragma once
#include <ncurses.h>
#include <menu.h>
#include <stack>
#include "Display.hpp"
#include "NCursesMenuWrapper.hpp"
#include "NCursesPromptProcessor.hpp"
#include "TextComponent.hpp"
#include "OptionsComponent.hpp"

class NCursesDisplay : public Display
{
  public:
    NCursesDisplay();
	  bool create();
	  void tear_down();

	  void draw(const Map& current_map);
	  std::string display_menu(const Menu& current_menu);

	  void clear_menu();

  protected:
    bool uses_colour() const;
    void refresh_terminal_size();
    void display_text_component(WINDOW* window, int* row, int* col, TextComponent* text_component);
    NCursesMenuWrapper display_and_return_options_component(WINDOW* window, int* row, int* col, OptionsComponent* options_component);
    std::string display_prompt(WINDOW* menu_window, PromptPtr prompt, int row = 0, int col = 0);

    // Creation/destruction methods
    WINDOW* create_menu(int height, int width, int start_row, int start_col);
    void destroy_menu(WINDOW *menu);

    int TERMINAL_MAX_ROWS;
    int TERMINAL_MAX_COLS;

    // The display is represented as a stack of windows in ncurses; the game window is the lowest, and any menus
    // or submenus are layered as new windows on top of that.  Each time a Menu is done, a window is popped off
    // the stack and the display is re-drawn.
    std::stack<WINDOW*> menus;

    // Used to process the prompt
    NCursesPromptProcessor prompt_processor;
    bool can_use_colour;
};
