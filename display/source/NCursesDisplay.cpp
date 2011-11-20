#include <iostream>
#include <sstream>
#include <boost/foreach.hpp>
#include "Conversion.hpp"
#include "NCursesDisplay.hpp"
#include "Menu.hpp"
#include "OptionsComponent.hpp"

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

  Refresh the display's size.

 **************************************************************/
//
// JCD FIXME: This doesn't seem to work.
//
void NCursesDisplay::refresh_terminal_size()
{
  getmaxyx(stdscr, TERMINAL_MAX_ROWS, TERMINAL_MAX_COLS);
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
  nl();
  noecho(); // Don't echo the user input.
  curs_set(0); // Cursor invisible.  Doesn't seem to work in Cygwin.

  refresh_terminal_size();

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
  refresh_terminal_size();
}

/*!
 *****************************************************************

  Draw the specified menu, full-screen.

 *****************************************************************/
string NCursesDisplay::display_menu(const Menu& current_menu)
{
  refresh_terminal_size();

  // JCD FIXME: Refactor the shit out of this.
  int row_start = 0;
  int col_start = 0;

  NCursesMenuWrapper wrapper;
  WINDOW* menu_window = create_menu(TERMINAL_MAX_ROWS, TERMINAL_MAX_COLS, row_start, col_start);

  menus.push(menu_window);

  int current_row = row_start;
  int current_col = col_start;

  // JCD FIXME: It goes without saying that this shit needs a refactorin'.
  vector<MenuComponent*> components = current_menu.get_components();
  BOOST_FOREACH( MenuComponent* component, components)
  {
    TextComponent* tc = dynamic_cast<TextComponent*>(component);

    if (tc != NULL)
    {
      display_text_component(menu_window, &current_row, &current_col, tc);
    }
    else
    {
      OptionsComponent* oc = dynamic_cast<OptionsComponent*>(component);

      if (oc != NULL)
      {
        // Process the options...
        wrapper = display_and_return_options_component(menu_window, &current_row, &current_col, oc);
      }
    }
  }

  // Menu driver for any options window goes here...

  wrefresh(menu_window);

  PromptPtr prompt = current_menu.get_prompt();
  prompt_processor.show_prompt(menu_window, prompt, current_row, current_col, TERMINAL_MAX_ROWS, TERMINAL_MAX_COLS);
  wrapper.release_pointer_structures();

  MENU* menu = wrapper.get_menu();

  if (menu)
  {
    int index = prompt_processor.get_prompt(menu_window, menu);
    return Integer::to_string(index);
  }
  else
  {
    return prompt_processor.get_prompt(menu_window, prompt);
  }
}

void NCursesDisplay::display_text_component(WINDOW* window, int* row, int* col, TextComponent* tc)
{
  string current_text = tc->get_text();
  mvwprintw(window, *row, *col, current_text.c_str());
  *row += 2;
}

NCursesMenuWrapper NCursesDisplay::display_and_return_options_component(WINDOW* window, int* row, int* col, OptionsComponent* oc)
{
  MENU* options_menu;
  ITEM** option_items;

  vector<Option> options = oc->get_options();
  vector<string> option_descriptions = oc->get_option_descriptions();
  int num_options = options.size();

  if (!options.empty())
  {
    option_items = (ITEM**) calloc(num_options, sizeof(ITEM*));

    for (int i = 0; i < num_options; i++)
    {
      Option current_option = options.at(i);
      string option_name = current_option.get_description();
      string option_desc = option_descriptions.at(i);
      option_items[i] = new_item(option_name.c_str(), option_desc.c_str());
    }

    option_items[num_options] = (ITEM *) NULL;

    options_menu = new_menu(option_items);
    set_menu_win(options_menu, window);
    set_menu_sub(options_menu, derwin(window, TERMINAL_MAX_ROWS - *row, TERMINAL_MAX_COLS, *row, *col));
    set_menu_mark(options_menu, " --> ");
    set_menu_format(options_menu, TERMINAL_MAX_ROWS - *row, 1); // By default, 1 column.  Change later.
    post_menu(options_menu);
    wrefresh(window);
  }

  NCursesMenuWrapper wrapper;
  wrapper.set_menu(options_menu);
  wrapper.set_items(option_items);
  wrapper.set_num_items(num_options);

  return wrapper;
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
