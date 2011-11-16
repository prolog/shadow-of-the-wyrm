#include <iostream>
#include <sstream>
#include <menu.h>
#include <boost/foreach.hpp>
#include "NCursesDisplay.hpp"
#include "Menu.hpp"

using namespace std;
using namespace boost;

// Create a menu and return it.
WINDOW* NCursesDisplay::create_menu(int height, int width, int start_row, int start_col)
{
  WINDOW* menu;

	menu = newwin(height, width, start_row, start_col);
	keypad(menu, TRUE);

	wrefresh(menu);

	return menu;
}

// Delete the given window.
void NCursesDisplay::destroy_menu(WINDOW *menu)
{
	delwin(menu);
}

/*
 **************************************************************

	Set up the NCurses-based display.

 **************************************************************/
bool NCursesDisplay::create()
{
  bool creation_success = true;

  initscr();
  keypad(stdscr, TRUE);
  noecho(); // Don't echo the user input.
  curs_set(0); // Cursor invisible.

  getmaxyx(stdscr, TERMINAL_MAX_ROWS, TERMINAL_MAX_COLS);

  if ((TERMINAL_MAX_ROWS < 24) || (TERMINAL_MAX_COLS < 80))
  {
    printw("Savage Lands requires a terminal of 80x24 or larger.\n");
    creation_success = false;
  }

  refresh();

  return creation_success;
}

/*
 ***************************************************************

 	Do anything necessary to tear down the NCurses-based display.

 ***************************************************************/
void NCursesDisplay::tear_down()
{
  endwin();
}

/*!
 *****************************************************************

 	Draw the specified map in the term.

 *****************************************************************/
void NCursesDisplay::draw(const Map& current_map)
{
}

/*!
 *****************************************************************

  Draw the specified menu, full-screen.

 *****************************************************************/
string NCursesDisplay::display_menu(const Menu& current_menu)
{
  // JCD FIXME: Refactor the shit out of this.
  // This is just a test to ensure the menu library is ok:
  MENU* test_menu_refactor_this_later;
  int row_start = 0;
  int col_start = 0;

  WINDOW* menu_window = create_menu(TERMINAL_MAX_ROWS, TERMINAL_MAX_COLS, row_start, col_start);
  menus.push(menu_window);

  int current_row = row_start;
  int current_col = col_start;

  vector<TextComponent> text = current_menu.get_text();
  BOOST_FOREACH( TextComponent text_component, text)
  {
    string current_text = text_component.get_text();
    mvwprintw(menu_window, current_row, current_col, current_text.c_str());
    current_row += 2;
  }

  wrefresh(menu_window);

  PromptPtr prompt = current_menu.get_prompt();
  prompt_processor.show_prompt(menu_window, prompt, current_row, current_col, TERMINAL_MAX_ROWS, TERMINAL_MAX_COLS);
  return prompt_processor.get_prompt(menu_window, prompt);
}

void NCursesDisplay::clear_menu()
{
  if (!menus.empty())
  {
    WINDOW* current_menu_window = menus.top();
    destroy_menu(current_menu_window);

    menus.pop();
  }
}
