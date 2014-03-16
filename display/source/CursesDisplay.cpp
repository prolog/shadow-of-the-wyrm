#include <cctype>
#include <iostream>
#include <sstream>
#include <vector>
#include <boost/tokenizer.hpp>
#include "Animation.hpp"
#include "Colours.hpp"
#include "Conversion.hpp"
#include "CursesAnimationFactory.hpp"
#include "EquipmentTextKeys.hpp"
#include "Log.hpp"
#include "MapUtils.hpp"
#include "Menu.hpp"
#include "CursesConstants.hpp"
#include "CursesDisplay.hpp"
#include "MapDisplayArea.hpp"
#include "OptionsComponent.hpp"
#include "Serialize.hpp"
#include "StringTable.hpp"
#include "TextKeys.hpp"

using namespace std;

const int CURSES_NUM_BASE_COLOURS = 8;
const int CURSES_NUM_TOTAL_COLOURS = 16;

// Assumption: menus is empty (prototype object), and so this is safe.
Display* CursesDisplay::clone()
{
  return new CursesDisplay(*this);
}

CursesDisplay::CursesDisplay()
: TERMINAL_MAX_ROWS(0), 
TERMINAL_MAX_COLS(0), 
FIELD_SPACE(2), 
MSG_BUFFER_LAST_Y(0), 
MSG_BUFFER_LAST_X(0), 
can_use_colour(false)
{
}

bool CursesDisplay::operator==(const CursesDisplay& cd) const
{
  bool result = true;

  result = result && (TERMINAL_MAX_ROWS == cd.TERMINAL_MAX_ROWS);
  result = result && (TERMINAL_MAX_COLS == cd.TERMINAL_MAX_COLS);
  result = result && (FIELD_SPACE == cd.FIELD_SPACE);
  result = result && (MSG_BUFFER_LAST_Y == cd.MSG_BUFFER_LAST_Y);
  result = result && (MSG_BUFFER_LAST_X == cd.MSG_BUFFER_LAST_X);
  result = result && (menus.size() == cd.menus.size());

  if (result)
  {
    for (uint i = 0; i < menus.size(); i++)
    {
      WINDOW* menu = menus.at(i);
      WINDOW* cd_menu = cd.menus.at(i);

      result = result && menu && cd_menu && (memcmp(menu, cd_menu, sizeof(menu)) == 0);
    }
  }

  result = result && (prompt_processor == cd.prompt_processor);
  result = result && (can_use_colour == cd.can_use_colour);

  return result;
}

// Get the current display width
unsigned int CursesDisplay::get_width() const
{
  return TERMINAL_MAX_COLS;
}

// Create a menu and return it.
WINDOW* CursesDisplay::create_menu(int height, int width, int start_row, int start_col)
{
  WINDOW* menu;

	menu = newwin(height, width, start_row, start_col);
	keypad(menu, TRUE);

  // Because menus don't display the player (or have any other meaningful reason to have
  // the cursor present), turn off the cursor.
  curs_set(0);
	wrefresh(menu);

	return menu;
}

// Delete the given window.
void CursesDisplay::destroy_menu(WINDOW *menu)
{
  Log::instance().debug("Destroying current menu");
	delwin(menu);
	menu = nullptr;
}

// Get whether the terminal can support colour.  False by
// default, until SL actually tries to detect the terminal's
// colour capabilities.  This can be turned off in the ini
// settings, also.
bool CursesDisplay::uses_colour() const
{
  return can_use_colour;
}

// Initialize the base ncurses colours.
void CursesDisplay::initialize_colours()
{
  vector<short int> colours{COLOR_BLACK, COLOR_RED, COLOR_GREEN, COLOR_YELLOW, COLOR_BLUE, COLOR_MAGENTA, COLOR_CYAN, COLOR_WHITE};

  short int pair_counter = 1;
  for (auto bg_colour : colours)
  {
    for (auto fg_colour : colours)
    {
      init_pair(pair_counter, fg_colour, bg_colour);
      pair_counter++;
    }

    pair_counter += CURSES_NUM_BASE_COLOURS;
  }
}

// Turn on colour using attron.
//
// Note that the enable/disable colour need to match!  Don't pass different colours!
void CursesDisplay::enable_colour(const int selected_colour, WINDOW* window)
{
  if (uses_colour())
  {
    if ((selected_colour % CURSES_NUM_TOTAL_COLOURS) > COLOUR_WHITE)
    {
      int actual_colour = selected_colour - COLOUR_BOLD_BLACK;
      wattron(window, COLOR_PAIR(actual_colour+1));
      wattron(window, A_BOLD);
      return;
    }

    wattron(window, COLOR_PAIR(selected_colour+1));
  }
}

// Turn off colour using attroff.
void CursesDisplay::disable_colour(const int selected_colour, WINDOW* window)
{
  if (uses_colour())
  {
    if ((selected_colour % CURSES_NUM_TOTAL_COLOURS) > COLOUR_WHITE)
    {
      int actual_colour = selected_colour - COLOUR_BOLD_BLACK;
      wattroff(window, COLOR_PAIR(actual_colour+1));
      wattroff(window, A_BOLD);
      return;
    }

    wattroff(window, COLOR_PAIR(selected_colour+1));
  }
}

// The Display function - hooks up to clear_message_buffer
void CursesDisplay::clear_messages()
{
  clear_message_buffer();
}

// Clear the message buffer and reset the cursor.  The message buffer is always lines 0 and 1.
int CursesDisplay::clear_message_buffer()
{  
  int return_val;
  
  move(0, 0);
  clrtoeol();

  move(1, 0);
  return_val = clrtoeol();
  
  // Reset the internal state
  MSG_BUFFER_LAST_Y = 0;
  MSG_BUFFER_LAST_X = 0;
  
  // Reset cursor to original position
  move(MSG_BUFFER_LAST_Y, MSG_BUFFER_LAST_X);
//  refresh();

  return return_val;
}

// Halt processing and force user input to continue.
void CursesDisplay::halt_messages()
{
  move(MSG_BUFFER_LAST_Y, MSG_BUFFER_LAST_X);
  refresh();
  getch();  
}

/*
 **************************************************************

  Refresh the display's size.

 **************************************************************/
//
// JCD FIXME: This doesn't seem to work.
//
// Fix this up once SL is compiling on Linux/FreeBSD and I can
// resize terminals.
//
void CursesDisplay::refresh_terminal_size()
{
  getmaxyx(stdscr, TERMINAL_MAX_ROWS, TERMINAL_MAX_COLS);
}

/*
 **************************************************************

	Set up the Curses-based display.

 **************************************************************/
bool CursesDisplay::create()
{
  bool creation_success = true;

  initscr();
  keypad(stdscr, TRUE);
  nl();
  noecho(); // Don't echo the user input.
  raw(); // pass control characters to the program.
  curs_set(0); // Cursor invisible.  Doesn't seem to work in Cygwin.  Just like colour redefinition.  Fucking Cygwin.

  if (has_colors() == TRUE)
  {
    can_use_colour = true;
    start_color();
    initialize_colours();
  }

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

 	Do anything necessary to tear down the Curses-based display.

 ***************************************************************/
void CursesDisplay::tear_down()
{
  clear_display();
  refresh();
  endwin();
}

/*
 *****************************************************************

  Clear the display (in practice, stdscr).

 *****************************************************************/
void CursesDisplay::clear_display()
{
  clear();
}

/*
 *****************************************************************

  Clear the message buffer, and then add a message to display to
  the user.  If it's very long, "..." it.

 *****************************************************************/
void CursesDisplay::add_message(const string& message, const bool reset_cursor)
{
  add_message(message, COLOUR_WHITE, reset_cursor);
}

void CursesDisplay::add_message(const string& message, const Colour colour, const bool reset_cursor)
{
  int orig_curs_y, orig_curs_x;
  getyx(stdscr, orig_curs_y, orig_curs_x);

  uint cur_y, cur_x;

  if (reset_cursor)
  {
    clear_message_buffer();
    move(0, 0);
  }
  else
  {
    move(MSG_BUFFER_LAST_Y, MSG_BUFFER_LAST_X);
  }

  boost::char_separator<char> separator(" ", " ", boost::keep_empty_tokens); // Keep the tokens!
  boost::tokenizer<boost::char_separator<char>> tokens(message, separator);

  enable_colour(colour, stdscr);

  for (boost::tokenizer<boost::char_separator<char>>::iterator t_iter = tokens.begin(); t_iter != tokens.end(); t_iter++)
  {
    getyx(stdscr, MSG_BUFFER_LAST_Y, MSG_BUFFER_LAST_X);
    
    string current_token = *t_iter;
    getyx(stdscr, cur_y, cur_x);

    if (cur_y == 0)
    {
      if ((cur_x + current_token.length()) > (TERMINAL_MAX_COLS-1))
      {
        // Move to the second line of the buffer
        move(1, 0);
        getyx(stdscr, cur_y, cur_x);
      }
    }
    else
    {
      if ((cur_x + current_token.length()) > (TERMINAL_MAX_COLS) - 4)
      {
        move(1, TERMINAL_MAX_COLS-4);

        disable_colour(colour, stdscr);
        printw("...");
        getch();
        enable_colour(colour, stdscr);

        clear_message_buffer();
        getyx(stdscr, cur_y, cur_x);
      }
    }
    
    // If the user presses enter
    if (cur_y > CursesConstants::MESSAGE_BUFFER_END_ROW)
    {
      cur_y--;
    }

    if (cur_x == 0)
    {
      if (String::is_whitespace(current_token))
      {
        // If we're at the start of a new line in the buffer, and the string 
        // is entirely whitespace, skip it.
        continue;
      }
    }

    printw(current_token.c_str());        
  }

  // Ensure that the last coordinates from the message buffer are up to date.
  getyx(stdscr, MSG_BUFFER_LAST_Y, MSG_BUFFER_LAST_X);

  // Reset the cursor.
  if (reset_cursor)
  {
    move(orig_curs_y, orig_curs_x);
  }
  
  disable_colour(colour, stdscr);
  
  //refresh();
}

string CursesDisplay::add_message_with_prompt(const string& message, const Colour colour, const bool reset_prompt)
{
  string prompt_result;

  // Add the message and then get the prompt value.
  // The assumption is that this should only ever (ever!  EVAR!) get called
  // from stdscr, since that's where the message manager is actually
  // displayed!
  add_message(message, colour, reset_prompt);
  prompt_result = prompt_processor.get_user_string(stdscr, true /* allow arbitrary non-alphanumeric characters */);

  return prompt_result;
}

/*
 *****************************************************************

 	Draw the specified Display in the term.  This'll be a simplified
  map that contains only the information needed by the display -
  no specific creature, etc., data.

 *****************************************************************/
void CursesDisplay::draw(const DisplayMap& current_map)
{
  refresh_terminal_size();

  DisplayTile display_tile;
  Coordinate map_coords;

  Dimensions d = current_map.size();
  unsigned int map_rows = d.get_y();
  unsigned int map_cols = d.get_x();

  for (unsigned int terminal_row = CursesConstants::MAP_START_ROW; terminal_row < map_rows + CursesConstants::MAP_START_ROW; terminal_row++)
  {
    for (unsigned int terminal_col = CursesConstants::MAP_START_COL; terminal_col < map_cols + CursesConstants::MAP_START_COL; terminal_col++)
    {
      map_coords.first = terminal_row - CursesConstants::MAP_START_ROW;
      map_coords.second = terminal_col - CursesConstants::MAP_START_COL;

      DisplayTile tile = current_map.at(map_coords);
      draw_coordinate(tile, terminal_row, terminal_col);
    }
  }

  Coordinate cursor_coord = current_map.get_cursor_coordinate();

  // Since we're drawing the map (with, presumably, the player) we need the cursor present to show the
  // position of the player's character.
  curs_set(1);
  move(cursor_coord.first+CursesConstants::MAP_START_ROW, cursor_coord.second+CursesConstants::MAP_START_COL);
  wredrawln(stdscr, CursesConstants::MAP_START_ROW, map_rows);
}

// Refreshes the contents of the current window.
void CursesDisplay::redraw()
{
  if (menus.empty())
  {
    refresh();
  }
  else
  {
    wrefresh(menus.back());
  }
}

void CursesDisplay::draw_update_map(const DisplayMap& update_map)
{
  DisplayTile display_tile;
  Coordinate map_coords;

  DisplayMapType tiles = update_map.get_tiles();

  uint terminal_row, terminal_col;

  for (DisplayMapType::value_type& tile : tiles)
  {
    Coordinate map_coords = MapUtils::convert_map_key_to_coordinate(tile.first);
    DisplayTile dtile = tile.second;

    terminal_row = CursesConstants::MAP_START_ROW + map_coords.first;
    terminal_col = CursesConstants::MAP_START_COL + map_coords.second;

    draw_coordinate(dtile, terminal_row, terminal_col);
  }

  Coordinate cursor_coord = update_map.get_cursor_coordinate();

  // Since we're drawing the map (with, presumably, the player) we need the cursor present to show the
  // position of the player's character.
  curs_set(1);
  move(cursor_coord.first+CursesConstants::MAP_START_ROW, cursor_coord.second+CursesConstants::MAP_START_COL);
  wredrawln(stdscr, CursesConstants::MAP_START_ROW, update_map.size().get_y());
}

// draw_tile is called externally from a Display to draw a particular engine
// coordinate.  The display takes the given y and x, adds the appropriate offsets,
// and then calls its own internal function to draw the given DisplayTile at the
// correct location on-screen.
void CursesDisplay::draw_tile(const uint y, const uint x, const DisplayTile& tile)
{
  // Turn off the cursor temporarily - higher level redraw functions will enable it
  // and place it correctly.
  curs_set(0);

  uint terminal_row = CursesConstants::MAP_START_ROW + y;
  uint terminal_col = CursesConstants::MAP_START_COL + x;

  draw_coordinate(tile, terminal_row, terminal_col);

  refresh();
}

AnimationFactoryPtr CursesDisplay::create_animation_factory() const
{
  AnimationFactoryPtr curses_animation_factory = std::make_shared<CursesAnimationFactory>();
  return curses_animation_factory;
}

void CursesDisplay::draw_animation(const Animation& animation)
{
  vector<AnimationInstructionPtr> animation_instructions = animation.get_animation_instructions();

  for(AnimationInstructionPtr& instruct : animation_instructions)
  {
    if (instruct)
    {
      instruct->execute(this);
    }
  }
}

void CursesDisplay::draw_coordinate(const DisplayTile& display_tile, const unsigned int terminal_row, const unsigned int terminal_col)
{
  int colour = display_tile.get_colour();

  // Maps are always drawn on ncurses' stdscr.
  enable_colour(colour, stdscr);
  mvprintw(terminal_row, terminal_col, "%c", display_tile.get_symbol());
  disable_colour(colour, stdscr);
}

/*!
 *****************************************************************

  Get the size of the map display in "tiles"

 *****************************************************************/
MapDisplayArea CursesDisplay::get_map_display_area()
{
  MapDisplayArea map_display_area;

  map_display_area.set_width(TERMINAL_MAX_COLS);
  map_display_area.set_height(TERMINAL_MAX_ROWS - 5); // FIXME: Remove magic num later

  return map_display_area;
}

/*!
 *****************************************************************

  Draw the specified menu, full-screen.

 *****************************************************************/
string CursesDisplay::display_menu(const Menu& current_menu)
{
  string result;
  refresh_terminal_size();

  MenuWrapper wrapper;
  WINDOW* menu_window = create_menu(TERMINAL_MAX_ROWS, TERMINAL_MAX_COLS, 0, 0);

  menus.push_back(menu_window);

  int current_row = 0;
  int current_col = 0;

  // Display the header if the text is defined.  Some menus (like the quest list,
  // etc) will have this defined, while others (such as the new character-type
  // menus) will not.
  string header_text = StringTable::get(current_menu.get_title_text_sid());
  uint num_pages = current_menu.get_num_pages();

  if (num_pages > 1)
  {
    ostringstream ss;

    ss << header_text << " (" << current_menu.get_current_page_number() << "/" << num_pages << ")";
    header_text = ss.str();
  }

  if (!header_text.empty())
  {
    display_header(header_text, menu_window, current_row);

    // Always allow for some space between the title and the components of the
    // menu, regardless of what the menu has set for line spacing.
    current_row += 2;
  }

  vector<MenuComponentPtr> components = current_menu.get_current_page();
  uint line_incr = current_menu.get_line_increment();

  uint csize = components.size();
  for(uint i = 0; i < csize; i++)
  {
    MenuComponentPtr component = components.at(i);

    if (component)
    {
      TextComponentPtr tc = dynamic_pointer_cast<TextComponent>(component);

      if (tc != NULL)
      {
        display_text_component(menu_window, &current_row, &current_col, tc, line_incr);
      }
      else
      {
        OptionsComponentPtr oc = dynamic_pointer_cast<OptionsComponent>(component);

        if (oc != NULL)
        {
          // Process the options...
          display_options_component(menu_window, &current_row, &current_col, oc);

          // Add them so that the prompt processor knows about the options in this set.
          wrapper.add_options(oc);
        }
      }

      // After each line, check to see if we need to throw up a prompt because
      // of hitting the end of the screen, but only if there's still stuff to
      // display.
      if (current_row == (TERMINAL_MAX_ROWS - 1) && (i != csize-1))
      {
        PromptPtr prompt = current_menu.get_prompt();
        prompt_processor.show_prompt(menu_window, prompt, current_row, current_col, TERMINAL_MAX_ROWS, TERMINAL_MAX_COLS);

        result = prompt_processor.get_prompt(menu_window, wrapper, prompt);

        wrefresh(menu_window);

        // We've shown the prompt, the user has intervened, and so
        // now we need to clear the window, reset the current row
        // back to 0 and keep displaying stuff from the menu.
        wclear(menu_window);
        current_row = 0;
      }
    }
  }

  // Done!  Add an appropriate prompt.
  PromptPtr prompt = current_menu.get_prompt();
  prompt_processor.show_prompt(menu_window, prompt, current_row, current_col, TERMINAL_MAX_ROWS, TERMINAL_MAX_COLS);

  result = prompt_processor.get_prompt(menu_window, wrapper, prompt);

  wrefresh(menu_window);

  return result;
}

// Show confirmation text - use the message buffer.
void CursesDisplay::confirm(const string& confirmation_message)
{
  add_message(confirmation_message, COLOUR_WHITE, false);
}

void CursesDisplay::display_text_component(WINDOW* window, int* row, int* col, TextComponentPtr tc, const uint line_incr)
{
  int cur_col = *col;

  if (tc != nullptr)
  {
    vector<pair<string, Colour>> current_text = tc->get_text();

    for (const auto& text_line : current_text)
    {
      enable_colour(text_line.second, window);
      mvwprintw(window, *row, cur_col, text_line.first.c_str());
      disable_colour(text_line.second, window);

      cur_col += text_line.first.size();
    }

    *row += line_incr;
  }
}

// Get a somewhat nice (it's ASCII...) option.
void CursesDisplay::format_option(const int incr, TextComponentPtr option_text, const string& option_desc, const bool show_desc) const
{
  char ascii_letter = 'a';
  ascii_letter += incr;

  if (option_text != nullptr)
  {
    vector<pair<string, Colour>> text = option_text->get_text();

    if (!text.empty())
    {
      string formatted_option = "[" + Char::to_string(ascii_letter) + "] " + text.at(0).first;

      if (show_desc && !option_desc.empty())
      {
        formatted_option += " - " + option_desc;
      }

      text[0].first = formatted_option;

      option_text->set_text(text);
    }
  }
}

void CursesDisplay::display_options_component(WINDOW* window, int* row, int* col, OptionsComponentPtr oc)
{
  vector<Option> options = oc->get_options();
  vector<string> option_descriptions = oc->get_option_descriptions();
  bool show_desc = oc->get_show_option_descriptions();

  size_t num_options = options.size();
  size_t num_option_desc = option_descriptions.size();

  int options_added = 0;

  if (!options.empty())
  {
    int temp_row = *row;

    for (unsigned int i = 0; i < num_options; i++)
    {
      Option current_option = options.at(i);
      Colour option_colour = current_option.get_colour();
      TextComponentPtr option_text = current_option.get_description();
      string option_desc;
      
      // Only get the description if we should show one and if one has been set.
      if (show_desc && (i < num_option_desc))
      {
        option_desc = option_descriptions.at(i);
      }

      format_option(current_option.get_id(), option_text, option_desc, show_desc);

      enable_colour(option_colour, window);
      TextComponentPtr text = current_option.get_description();
      display_text_component(window, row, col, text, 1);
      disable_colour(option_colour, window);

      options_added++;
      temp_row++;
    }
  }

  *row += options_added;
}

void CursesDisplay::clear_menu()
{
  if (!menus.empty())
  {
    WINDOW* current_menu_window = menus.back();
    wclear(current_menu_window);
    wrefresh(current_menu_window);
    destroy_menu(current_menu_window);

    menus.pop_back();
  }
}

// Display the player data
void CursesDisplay::display(const DisplayStatistics& player_stats)
{
  string name         = player_stats.get_name();
  string synopsis     = player_stats.get_synopsis();

  pair<string, Colour> strength     = player_stats.get_strength();
  pair<string, Colour> dexterity    = player_stats.get_dexterity();
  pair<string, Colour> agility      = player_stats.get_agility();
  pair<string, Colour> health       = player_stats.get_health();
  pair<string, Colour> intelligence = player_stats.get_intelligence();
  pair<string, Colour> willpower    = player_stats.get_willpower();
  pair<string, Colour> charisma     = player_stats.get_charisma();

  string speed        = player_stats.get_speed();

  string level        = player_stats.get_level();
  string defence      = player_stats.get_defence();

  string hit_points   = player_stats.get_hit_points();
  string arc_points   = player_stats.get_arcana_points();

  string map_depth    = player_stats.get_map_depth();

  vector<pair<string, Colour>> status_ailments = player_stats.get_status_ailments();

  unsigned int PLAYER_SYNOPSIS_START_ROW = TERMINAL_MAX_ROWS - 3;
  unsigned int current_row = PLAYER_SYNOPSIS_START_ROW;
  unsigned int initial_row = current_row;
  unsigned int current_col = 0;
  bool can_print = true;
  
  // First, clear the synopsis.
  move(PLAYER_SYNOPSIS_START_ROW, 0);
  clrtobot();
  
  // Next, set the synopsis values
  if (can_print) can_print = print_display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, name, synopsis);
  if (can_print) can_print = print_display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, synopsis, strength.first);
  if (can_print) can_print = print_display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, strength.first, dexterity.first, strength.second);
  if (can_print) can_print = print_display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, dexterity.first, agility.first, dexterity.second);
  if (can_print) can_print = print_display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, agility.first, health.first, agility.second);
  if (can_print) can_print = print_display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, health.first, intelligence.first, health.second);
  if (can_print) can_print = print_display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, intelligence.first, willpower.first, intelligence.second);
  if (can_print) can_print = print_display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, willpower.first, charisma.first, willpower.second);
  if (can_print) can_print = print_display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, charisma.first, level, charisma.second);
  if (can_print) can_print = print_display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, level, defence);
  if (can_print) can_print = print_display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, defence, speed);
  if (can_print) can_print = print_display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, speed, hit_points);
  if (can_print) can_print = print_display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, hit_points, arc_points);
  if (can_print) can_print = print_display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, arc_points, map_depth);
  mvprintw(current_row, current_col, map_depth.c_str());

  // Last row: status ailments
  current_row = TERMINAL_MAX_ROWS-1;
  current_col = 0;

  for (uint x = 0; x < status_ailments.size(); x++)
  {
    pair<string, Colour> status_ailment = status_ailments.at(x);
    bool has_more = (x != (status_ailments.size() - 1));

    if (has_more)
    {
      pair<string, Colour> next_ailment = status_ailments.at(x+1);

      if (can_print)
      {
        Colour colour = status_ailment.second;

        print_display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, status_ailment.first, next_ailment.first, colour); 
      }
    }
    else
    {
      if (can_print)
      {
        Colour colour = status_ailment.second;

        enable_colour(colour, stdscr);
        mvprintw(current_row, current_col, status_ailment.first.c_str());
        disable_colour(colour, stdscr);
      }
    }
  }
}

bool CursesDisplay::print_display_statistic_and_update_row_and_column(const unsigned int initial_row, unsigned int* current_row, unsigned int* current_col, const string& current_stat, const string& next_stat, Colour print_colour)
{
  bool can_print = true;

  enable_colour(print_colour, stdscr);
  mvprintw(*current_row, *current_col, current_stat.c_str());
  can_print = update_synopsis_row_and_column(initial_row, current_row, current_col, current_stat, next_stat);
  disable_colour(print_colour, stdscr);

  return can_print;
}

// Update the row/col for the player synopsis.  Return false if we've run out of space
// and can't print anything else.
bool CursesDisplay::update_synopsis_row_and_column(const unsigned int initial_row, unsigned int* row, unsigned int* col, const string& previous_field, const string& next_field)
{
  bool can_update = true;
  unsigned int next_column_end = *col + previous_field.size() + FIELD_SPACE + next_field.size();

  *col = *col + previous_field.size() + FIELD_SPACE;

  if (next_column_end > TERMINAL_MAX_COLS - 1)
  {
    // We've gone over max cols.  Fine - but can we increment to the next row in the display?
    if (*row < TERMINAL_MAX_ROWS-2)
    {
      *col = 0;
      *row = *row + 1;
    }
    else
    {
      can_update = false;
    }
  }

  return can_update;
}

void CursesDisplay::display_header(const string& header_text, WINDOW* window, const int display_line)
{
  size_t header_text_size = header_text.size();

  unsigned int header_start = (TERMINAL_MAX_COLS/2) - (header_text_size/2);
  unsigned int header_end = (TERMINAL_MAX_COLS/2) - (header_text_size/2) + header_text_size;

  for (unsigned int i = 0; i < header_start-1; i++)
  {
    mvwprintw(window, display_line, i, "-");
  }
  
  mvwprintw(window, display_line, header_start, header_text.c_str());
  
  for (unsigned int i = header_end+1; i < TERMINAL_MAX_COLS; i++)
  {
    mvwprintw(window, display_line, i, "-");
  }
}

// Display the Inventory
// JCD FIXME: Break this off into its own class later.
int CursesDisplay::display_inventory(const DisplayInventoryMap& inventory)
{
  int items_displayed = 0;
  string inventory_header = StringTable::get(TextKeys::INVENTORY);

  // Create the new window to display the items
  WINDOW* inv_window = create_menu(TERMINAL_MAX_ROWS, TERMINAL_MAX_COLS, 0, 0);
  menus.push_back(inv_window);
  
  // Centre the header on the first line
  int current_row = 0;
  const int current_row_start_value = 2;
  char slot_char = 'A';

  display_header(inventory_header, inv_window, current_row);
  
  current_row = current_row_start_value;

  for (DisplayInventoryMap::const_iterator i_it = inventory.begin(); i_it != inventory.end(); i_it++)
  {
    DisplayItemType display_item_type    = i_it->first;
    vector<DisplayItem> display_items    = i_it->second;
    
    // Display the category info
    string category_symbol   = display_item_type.get_symbol();
    Colour category_colour   = display_item_type.get_colour();
    string category_desc     = display_item_type.get_description();
    string category_synopsis = category_desc + " - " + category_symbol;

    if (!display_items.empty())
    {
      enable_colour (category_colour, inv_window);
      mvwprintw(inv_window, current_row, 0, category_synopsis.c_str());
      disable_colour(category_colour, inv_window);
      
      for(DisplayItem item : display_items)
      {
        current_row++;
        
        string item_description = Char::to_string(slot_char) + " - ";
        mvwprintw(inv_window, current_row, 3, item_description.c_str());        
        
        item_description   = item.get_description();
        Colour item_colour = item.get_colour();

        enable_colour(item_colour, inv_window);
        wprintw(inv_window, item_description.c_str());        
        disable_colour(item_colour, inv_window);

        DisplayItemFlagsVec flags = item.get_flags();
        for(const TextColour& tc : flags)
        {
          wprintw(inv_window, " ");

          enable_colour(tc.second, inv_window);
          wprintw(inv_window, tc.first.c_str());
          disable_colour(tc.second, inv_window);
        }

        items_displayed++;
        slot_char++;
      }
      
      current_row++;
      if (current_row == TERMINAL_MAX_ROWS-1) // Need room for the prompt at the bottom!
      {
        break;
      } 
    }
  }

  string prompt_text = StringTable::get(TextKeys::INVENTORY_PROMPT);
  int prompt_col = (TERMINAL_MAX_COLS - prompt_text.size() - 1);
  mvwprintw(inv_window, TERMINAL_MAX_ROWS-1, prompt_col, prompt_text.c_str());
  
  wrefresh(inv_window);
  
  return items_displayed;
}

WINDOW* CursesDisplay::get_current_menu()
{
  WINDOW* menu = nullptr;

  if (!menus.empty())
  {
    menu = menus.back();
  }

  return menu;
}

bool CursesDisplay::serialize(ostream& stream) const
{
  Serialize::write_uint(stream, TERMINAL_MAX_ROWS);
  Serialize::write_uint(stream, TERMINAL_MAX_COLS);
  Serialize::write_uint(stream, FIELD_SPACE);
  Serialize::write_uint(stream, MSG_BUFFER_LAST_Y);
  Serialize::write_uint(stream, MSG_BUFFER_LAST_X);
  
  // Menus are not serialized.  Saving can only be done on the main screen,
  // which will be reconstructed based on the game's map/etc data.

  // CursesPromptProcessor is stateless; don't write it.

  Serialize::write_bool(stream, can_use_colour);

  return true;
}

bool CursesDisplay::deserialize(istream& stream)
{
  Serialize::read_uint(stream, TERMINAL_MAX_ROWS);
  Serialize::read_uint(stream, TERMINAL_MAX_COLS);
  Serialize::read_uint(stream, FIELD_SPACE);
  Serialize::read_uint(stream, MSG_BUFFER_LAST_Y);
  Serialize::read_uint(stream, MSG_BUFFER_LAST_X);

  // Menus are not serialized.  Saving can only be done on the main screen,
  // which will be reconstructed based on the game's map/etc data.

  // CursesPromptProcessor is stateless; don't load it.

  Serialize::read_bool(stream, can_use_colour);

  return true;
}

ClassIdentifier CursesDisplay::internal_class_identifier() const
{
  return CLASS_ID_CURSES_DISPLAY;
}

#ifdef UNIT_TESTS
#include "unit_tests/CursesDisplay_test.cpp"
#endif
