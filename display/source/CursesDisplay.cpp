#include <iostream>
#include <sstream>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include "Colours.hpp"
#include "Conversion.hpp"
#include "Log.hpp"
#include "Menu.hpp"
#include "CursesConstants.hpp"
#include "CursesDisplay.hpp"
#include "OptionsComponent.hpp"
#include "Serialize.hpp"
#include "StringTable.hpp"

using namespace std;
using namespace boost;

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

bool CursesDisplay::operator==(const CursesDisplay& cd)
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
  Log::instance()->debug("Destroying current menu");
	delwin(menu);
	menu = NULL;
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
  init_pair(1, COLOR_BLACK,   COLOR_BLACK);
  init_pair(2, COLOR_RED,     COLOR_BLACK);
  init_pair(3, COLOR_GREEN,   COLOR_BLACK);
  init_pair(4, COLOR_YELLOW,  COLOR_BLACK);
  init_pair(5, COLOR_BLUE,    COLOR_BLACK);
  init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(7, COLOR_CYAN,    COLOR_BLACK);
  init_pair(8, COLOR_WHITE,   COLOR_BLACK);
}

// Turn on colour using attron.
//
// Note that the enable/disable colour need to match!  Don't pass different colours!
void CursesDisplay::enable_colour(const int selected_colour)
{
  if (uses_colour())
  {
    if (selected_colour > COLOUR_WHITE)
    {
      int actual_colour = selected_colour - COLOUR_BOLD_BLACK;
      attron(COLOR_PAIR(actual_colour+1));
      attron(A_BOLD);
      return;
    }

    attron(COLOR_PAIR(selected_colour+1));
  }
}

// Turn off colour using attroff.
void CursesDisplay::disable_colour(const int selected_colour)
{
  if (uses_colour())
  {
    if (selected_colour > COLOUR_WHITE)
    {
      int actual_colour = selected_colour - COLOUR_BOLD_BLACK;
      attroff(COLOR_PAIR(actual_colour+1));
      attroff(A_BOLD);
      return;
    }

    attroff(COLOR_PAIR(selected_colour+1));
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

  char_separator<char> separator(" ", " ", boost::keep_empty_tokens); // Keep the tokens!
  tokenizer<char_separator<char> > tokens(message, separator);

  enable_colour(colour);

  for (tokenizer<char_separator<char> >::iterator t_iter = tokens.begin(); t_iter != tokens.end(); t_iter++)
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
      }
    }
    else
    {
      if ((cur_x + current_token.length()) > (TERMINAL_MAX_COLS) - 4)
      {
        move(1, TERMINAL_MAX_COLS-4);

        // Add "..."
        disable_colour(colour);
        printw("...");
        getch();
        enable_colour(colour);

        clear_message_buffer();
      }
    }
    
    // If the user presses enter
    if (cur_y > CursesConstants::MESSAGE_BUFFER_END_ROW)
    {
      cur_y--;
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
  
  disable_colour(colour);
  
  //refresh();
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

      display_tile = current_map.at(map_coords);

      int colour = display_tile.get_colour();

      enable_colour(colour);

      // Maps are always drawn on ncurses' stdscr.
      mvprintw(terminal_row, terminal_col, "%c", display_tile.get_symbol());

      disable_colour(colour);
    }
  }

  Coordinate cursor_coord = current_map.get_cursor_coordinate();

  // Since we're drawing the map (with, presumably, the player) we need the cursor present to show the
  // position of the player's character.
  curs_set(1);
  move(cursor_coord.first+CursesConstants::MAP_START_ROW, cursor_coord.second+CursesConstants::MAP_START_COL);
  wredrawln(stdscr, CursesConstants::MAP_START_ROW, map_rows);
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

  CursesMenuWrapper wrapper;
  WINDOW* menu_window = create_menu(TERMINAL_MAX_ROWS, TERMINAL_MAX_COLS, 0, 0);

  menus.push_back(menu_window);

  int current_row = 0;
  int current_col = 0;

  vector<MenuComponentPtr> components = current_menu.get_components();
  BOOST_FOREACH( MenuComponentPtr component, components)
  {
    TextComponentPtr tc = dynamic_pointer_cast<TextComponent>(component);

    if (tc != NULL)
    {
      display_text_component(menu_window, &current_row, &current_col, tc);
    }
    else
    {
      OptionsComponentPtr oc = dynamic_pointer_cast<OptionsComponent>(component);

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

  result = prompt_processor.get_prompt(menu_window, wrapper, prompt);
  
  return result;
}

// Show confirmation text - use the message buffer.
void CursesDisplay::confirm(const string& confirmation_message)
{
  add_message(confirmation_message, COLOUR_WHITE, false);
}

void CursesDisplay::display_text_component(WINDOW* window, int* row, int* col, TextComponentPtr tc)
{
  string current_text = tc->get_text();
  mvwprintw(window, *row, *col, current_text.c_str());
  *row += 2;
}

// Get a somewhat nice (it's ASCII...) option.
pair<char, string> CursesDisplay::get_formatted_option(const int incr, const string& option_name, const string& option_desc) const
{
  pair<char, string> result;

  char ascii_letter = 'a';
  ascii_letter += incr;

  result.first = ascii_letter;

  string formatted_option = "[" + Char::to_string(ascii_letter) + "] " + option_name;

  if (!option_desc.empty())
  {
    formatted_option += " - " + option_desc;
  }

  result.second = formatted_option;

  return result;
}

CursesMenuWrapper CursesDisplay::display_and_return_options_component(WINDOW* window, int* row, int* col, OptionsComponentPtr oc)
{
  CursesMenuWrapper wrapper;

  vector<Option> options = oc->get_options();
  vector<string> option_descriptions = oc->get_option_descriptions();
 
  int num_options = options.size();

  if (!options.empty())
  {
    int temp_row = *row;

    for (int i = 0; i < num_options; i++)
    {
      Option current_option = options.at(i);
      string option_name = current_option.get_description();
      string option_desc = option_descriptions.at(i);

      pair<char, string> option_details = get_formatted_option(current_option.get_id(), option_name, option_desc);
      wrapper.add_option(option_details.first);

      mvwprintw(window, temp_row, (*col)+2, option_details.second.c_str());

      temp_row++;
    }

    wrefresh(window);
  }

  wrapper.set_num_items(num_options);

  return wrapper;
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

  string strength     = player_stats.get_strength();
  string dexterity    = player_stats.get_dexterity();
  string agility      = player_stats.get_agility();
  string health       = player_stats.get_health();
  string intelligence = player_stats.get_intelligence();
  string willpower    = player_stats.get_willpower();
  string charisma     = player_stats.get_charisma();

  string valour       = player_stats.get_valour();
  string spirit       = player_stats.get_spirit();
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
  if (can_print) can_print = print_display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, synopsis, strength);
  if (can_print) can_print = print_display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, strength, dexterity);
  if (can_print) can_print = print_display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, dexterity, agility);
  if (can_print) can_print = print_display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, agility, health);
  if (can_print) can_print = print_display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, health, intelligence);
  if (can_print) can_print = print_display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, intelligence, willpower);
  if (can_print) can_print = print_display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, willpower, charisma);
  if (can_print) can_print = print_display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, charisma, level);
  if (can_print) can_print = print_display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, level, defence);
  if (can_print) can_print = print_display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, defence, valour);
  if (can_print) can_print = print_display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, valour, spirit);
  if (can_print) can_print = print_display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, spirit, speed);
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

        enable_colour(colour);
        print_display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, status_ailment.first, next_ailment.first); 
        disable_colour(colour);
      }
    }
    else
    {
      if (can_print)
      {
        Colour colour = status_ailment.second;

        enable_colour(colour);
        mvprintw(current_row, current_col, status_ailment.first.c_str());
        disable_colour(colour);
      }
    }
  }
}

bool CursesDisplay::print_display_statistic_and_update_row_and_column(const unsigned int initial_row, unsigned int* current_row, unsigned int* current_col, const string& current_stat, const string& next_stat)
{
  bool can_print = true;

  mvprintw(*current_row, *current_col, current_stat.c_str());

  can_print = update_synopsis_row_and_column(initial_row, current_row, current_col, current_stat, next_stat);

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

// Display the Equipment
// JCD FIXME: break this off into its own class later.
void CursesDisplay::display_equipment(const DisplayEquipmentMap& equipment)
{
  string equipment_header = StringTable::get(TextKeys::EQUIPMENT);

  // Create the new window to display the equipment
  WINDOW* eq_window = create_menu(TERMINAL_MAX_ROWS, TERMINAL_MAX_COLS, 0, 0);
  menus.push_back(eq_window);
  
  // Centre the header on the first line
  int current_row = 0;
  
  unsigned int header_start = (TERMINAL_MAX_COLS/2) - (equipment_header.size()/2);
  unsigned int header_end = (TERMINAL_MAX_COLS/2) - (equipment_header.size()/2) + equipment_header.size();
  for (unsigned int i = 0; i < header_start-1; i++) mvwprintw(eq_window, current_row, i, "-");
  mvwprintw(eq_window, current_row, header_start, equipment_header.c_str());
  for (unsigned int i = header_end+1; i < TERMINAL_MAX_COLS; i++) mvwprintw(eq_window, current_row, i, "-");

  uint longest = 0;
  for (DisplayEquipmentMap::const_iterator e_it = equipment.begin(); e_it != equipment.end(); e_it++)
  {
    EquipmentWornLocation worn_location = e_it->first;
    string worn_location_name = EquipmentTextKeys::get_equipment_text_from_given_worn_location(worn_location);
    if (worn_location_name.size() > longest) longest = worn_location_name.size() + 1;
  }

  char slot_char = 'A';
  
  // Ensure that the first row of the equipment is right below the "---"
  current_row--;
  
  // Display each individual slot
  for (DisplayEquipmentMap::const_iterator e_it = equipment.begin(); e_it != equipment.end(); e_it++)
  {
    // One row for item synopsis, one row for status effects
    current_row += 2;
    ostringstream ss;
    
    EquipmentWornLocation worn_location = e_it->first;
    DisplayItem display_item            = e_it->second;
    
    string worn_location_name = EquipmentTextKeys::get_equipment_text_from_given_worn_location(worn_location);
    string item_description   = display_item.get_description();
    ss << slot_char << " - " <<  String::add_trailing_spaces(worn_location_name, longest) << ": " << item_description;
    
    mvwprintw(eq_window, current_row, 0, ss.str().c_str());

    slot_char++;
  }
  
  string prompt_text = StringTable::get(TextKeys::EQUIPMENT_PROMPT);
  uint prompt_col = (TERMINAL_MAX_COLS - prompt_text.size() - 1);
  mvwprintw(eq_window, TERMINAL_MAX_ROWS-1, prompt_col, prompt_text.c_str());
  
  wrefresh(eq_window);
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
  
  unsigned int header_start = (TERMINAL_MAX_COLS/2) - (inventory_header.size()/2);
  unsigned int header_end = (TERMINAL_MAX_COLS/2) - (inventory_header.size()/2) + inventory_header.size();
  for (unsigned int i = 0; i < header_start-1; i++) mvwprintw(inv_window, current_row, i, "-");
  mvwprintw(inv_window, current_row, header_start, inventory_header.c_str());
  for (unsigned int i = header_end+1; i < TERMINAL_MAX_COLS; i++) mvwprintw(inv_window, current_row, i, "-");
  
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
      enable_colour (category_colour);
      mvwprintw(inv_window, current_row, 0, category_synopsis.c_str());
      disable_colour(category_colour);
      
      BOOST_FOREACH(DisplayItem item, display_items)
      {
        current_row++;
        
        string item_description = Char::to_string(slot_char) + " - " + item.get_description();
        mvwprintw(inv_window, current_row, 3, item_description.c_str());        

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
  uint prompt_col = (TERMINAL_MAX_COLS - prompt_text.size() - 1);
  mvwprintw(inv_window, TERMINAL_MAX_ROWS-1, prompt_col, prompt_text.c_str());
  
  wrefresh(inv_window);
  
  return items_displayed;
}

bool CursesDisplay::serialize(ostream& stream)
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
