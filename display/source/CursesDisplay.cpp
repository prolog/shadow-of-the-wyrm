#include <cctype>
#include <iostream>
#include <sstream>
#include <vector>
#include <boost/tokenizer.hpp>
#include "Animation.hpp"
#include "Colours.hpp"
#include "Conversion.hpp"
#include "CursesAnimationFactory.hpp"
#include "CursesProperties.hpp"
#include "DisplaySettings.hpp"
#include "EquipmentTextKeys.hpp"
#include "Log.hpp"
#include "MapUtils.hpp"
#include "Screen.hpp"
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

// Assumption: screens is empty (prototype object), and so this is safe.
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
message_buffer_screen(nullptr),
can_use_colour(false),
mono_colour(Colour::COLOUR_UNDEFINED),
cursor_mode(1) /* normal visibility */
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
  result = result && (screens.size() == cd.screens.size());

  if (result)
  {
    for (uint i = 0; i < screens.size(); i++)
    {
      WINDOW* screen = screens.at(i);
      WINDOW* cd_screen = cd.screens.at(i);

      result = result && screen && cd_screen && (memcmp(screen, cd_screen, sizeof(screen)) == 0);
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

// Create a screen and return it.
WINDOW* CursesDisplay::create_screen(int height, int width, int start_row, int start_col)
{
  WINDOW* screen;

	screen = newwin(height, width, start_row, start_col);
	keypad(screen, TRUE);

  // Because screens don't display the player (or have any other meaningful reason to have
  // the cursor present), turn off the cursor.
  curs_set(0);
	wrefresh(screen);

	return screen;
}

// Delete the given window.
void CursesDisplay::destroy_screen(WINDOW *screen)
{
  Log::instance().debug("CursesDisplay::destroy_screen - destroying current screen.");
	delwin(screen);
	screen = nullptr;
}

// Get whether the terminal can support colour.  False by
// default, until SL actually tries to detect the terminal's
// colour capabilities.  This can be turned off in the ini
// settings, also.
bool CursesDisplay::uses_colour() const
{
  string colour_prop = get_property(DisplaySettings::DISPLAY_SETTING_COLOUR);
  bool colour = String::to_bool(colour_prop);

  return colour;
}

// If the cursor mode has been set in the properties, use that.
// Otherwise, use the default.
int CursesDisplay::get_cursor_mode(const CursorSettings cs) const
{
  int mode = cursor_mode;

  if (cs == CursorSettings::CURSOR_SETTINGS_SHOW_CURSOR)
  {
    mode = 1; /* show cursor */
  }
  else
  {
    auto p_it = display_properties.find(CursesProperties::CURSES_PROPERTIES_CURSOR_MODE);

    if (p_it != display_properties.end())
    {
      mode = String::to_int(p_it->second);
    }
  }

  return mode;
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
    set_colour(selected_colour, window);
  }
  else
  {
    // Do we need to set the "monochrome" display to a particular colour?
    // Dark red, like my thirteen-year-old-self's old QBASIC games?
    // Bright green, like an old Apple ][?
    if (mono_colour == Colour::COLOUR_UNDEFINED)
    {
      // Set up the monochrome colour on initial use from the properties
      // set by the game.
      auto m_it = display_properties.find(DisplaySettings::DISPLAY_SETTING_MONOCHROME_COLOUR);

      if (m_it != display_properties.end())
      {
        int mono_i = String::to_int(m_it->second);
        mono_colour = static_cast<Colour>(mono_i);
      }
    }

    set_colour(static_cast<int>(mono_colour), window);
  }
}

// Set the display colour without actually checking for monochrome.
void CursesDisplay::set_colour(const int selected_colour, WINDOW* window)
{
  if ((selected_colour % CURSES_NUM_TOTAL_COLOURS) > static_cast<int>(Colour::COLOUR_WHITE))
  {
    int actual_colour = selected_colour - static_cast<int>(Colour::COLOUR_BOLD_BLACK);
    wattron(window, COLOR_PAIR(actual_colour + 1));
    wattron(window, A_BOLD);
    return;
  }

  wattron(window, COLOR_PAIR(selected_colour + 1));
}

// Turn off colour using attroff.
void CursesDisplay::disable_colour(const int selected_colour, WINDOW* window)
{
  if (uses_colour())
  {
    if ((selected_colour % CURSES_NUM_TOTAL_COLOURS) > static_cast<int>(Colour::COLOUR_WHITE))
    {
      int actual_colour = selected_colour - static_cast<int>(Colour::COLOUR_BOLD_BLACK);
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
  WINDOW* screen = get_message_buffer_screen();
  
  wmove(screen, 0, 0);
  wclrtoeol(screen);

  wmove(screen, 1, 0);
  return_val = wclrtoeol(screen);
  
  // Reset the internal state
  MSG_BUFFER_LAST_Y = 0;
  MSG_BUFFER_LAST_X = 0;
  
  // Reset cursor to original position
  wmove(screen, MSG_BUFFER_LAST_Y, MSG_BUFFER_LAST_X);

  return return_val;
}

WINDOW* CursesDisplay::get_message_buffer_screen()
{
  WINDOW* screen = stdscr;

  if (message_buffer_screen != nullptr)
  {
    screen = message_buffer_screen;
  }

  return screen;
}

// Halt processing and force user input to continue.
void CursesDisplay::halt_messages()
{
  WINDOW* screen = get_message_buffer_screen();

  wmove(screen, MSG_BUFFER_LAST_Y, MSG_BUFFER_LAST_X);
  wrefresh(screen);
  wgetch(screen);  
}

// Refresh the display's size.
//
//
// JCD FIXME: This doesn't seem to work.
//
// Fix this up once SOTW is compiling on Linux/FreeBSD and I can
// resize terminals.
//
void CursesDisplay::refresh_terminal_size()
{
  getmaxyx(stdscr, TERMINAL_MAX_ROWS, TERMINAL_MAX_COLS);
}

// Set up the Curses-based display.
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
    printw("Shadow of the Wyrm requires a terminal of 80x24 or larger.\n");
    creation_success = false;
  }

  refresh();

  return creation_success;
}

// Do anything necessary to tear down the Curses-based display.
void CursesDisplay::tear_down()
{
  refresh();
  endwin();
}

// Clear the display (in practice, stdscr).
void CursesDisplay::clear_display()
{
  clear();
}

void CursesDisplay::add_alert(const string& message)
{
  message_buffer_screen = get_current_screen();

  int prev_curs_state = curs_set(1);
  clear_message_buffer();
  add_message(message, Colour::COLOUR_BOLD_RED, false);
  wrefresh(message_buffer_screen);
  wgetch(message_buffer_screen);
  clear_message_buffer();
  curs_set(prev_curs_state);

  message_buffer_screen = nullptr;
}

// Clear the message buffer, and then add a message to display to
// the user.  If it's very long, "..." it.
void CursesDisplay::add_message(const string& message, const bool reset_cursor)
{
  add_message(message, Colour::COLOUR_WHITE, reset_cursor);
}

void CursesDisplay::add_message(const string& to_add_message, const Colour colour, const bool reset_cursor)
{
  string message = to_add_message;
  WINDOW* screen = get_message_buffer_screen();

  // Replace any single instances of "%", as these will cause a crash when
  // the corresponding parameters are not present in printw.
  boost::replace_all(message, "%", "%%");

  int orig_curs_y, orig_curs_x;
  getyx(screen, orig_curs_y, orig_curs_x);

  uint cur_y, cur_x;

  if (reset_cursor)
  {
    clear_message_buffer();
    wmove(screen, 0, 0);
  }
  else
  {
    wmove(screen, MSG_BUFFER_LAST_Y, MSG_BUFFER_LAST_X);
  }

  boost::char_separator<char> separator(" ", " ", boost::keep_empty_tokens); // Keep the tokens!
  boost::tokenizer<boost::char_separator<char>> tokens(message, separator);

  enable_colour(static_cast<int>(colour), screen);

  for (boost::tokenizer<boost::char_separator<char>>::iterator t_iter = tokens.begin(); t_iter != tokens.end(); t_iter++)
  {
    getyx(screen, MSG_BUFFER_LAST_Y, MSG_BUFFER_LAST_X);
    
    string current_token = *t_iter;
    getyx(screen, cur_y, cur_x);

    if (cur_y == 0)
    {
      if ((cur_x + current_token.length()) > (TERMINAL_MAX_COLS-1))
      {
        // Move to the second line of the buffer
        wmove(screen, 1, 0);
        getyx(screen, cur_y, cur_x);
      }
    }
    else
    {
      if ((cur_x + current_token.length()) > (TERMINAL_MAX_COLS) - 4)
      {
        wmove(screen, 1, TERMINAL_MAX_COLS-4);

        disable_colour(static_cast<int>(colour), screen);
        wprintw(screen, "...");
        wgetch(screen);
        enable_colour(static_cast<int>(colour), screen);

        clear_message_buffer();
        getyx(screen, cur_y, cur_x);
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

    wprintw(screen, current_token.c_str());        
  }

  // Ensure that the last coordinates from the message buffer are up to date.
  getyx(screen, MSG_BUFFER_LAST_Y, MSG_BUFFER_LAST_X);

  // Reset the cursor.
  if (reset_cursor)
  {
    wmove(screen, orig_curs_y, orig_curs_x);
  }
  
  disable_colour(static_cast<int>(colour), screen);
  
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

// Draw the specified Display in the term.  This'll be a simplified
// map that contains only the information needed by the display -
// no specific creature, etc., data.
void CursesDisplay::draw(const DisplayMap& current_map, const CursorSettings cs)
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
  curs_set(get_cursor_mode(cs));
  move(cursor_coord.first+CursesConstants::MAP_START_ROW, cursor_coord.second+CursesConstants::MAP_START_COL);
  wredrawln(stdscr, CursesConstants::MAP_START_ROW, map_rows);
  refresh();
}

// Refreshes the contents of the current window.
void CursesDisplay::redraw()
{
  if (screens.empty())
  {
    refresh();
  }
  else
  {
    wrefresh(screens.back());
  }
}

void CursesDisplay::draw_update_map(const DisplayMap& update_map, const CursorSettings cs)
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
  curs_set(get_cursor_mode(cs));
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

// Get the size of the map display in "tiles"
MapDisplayArea CursesDisplay::get_map_display_area()
{
  MapDisplayArea map_display_area;

  map_display_area.set_width(TERMINAL_MAX_COLS);
  map_display_area.set_height(TERMINAL_MAX_ROWS - 5); // JCD FIXME: Remove magic num later

  return map_display_area;
}

// Draw the specified screen, full-screen.
string CursesDisplay::display_screen(const Screen& current_screen)
{
  string result;
  refresh_terminal_size();

  MenuWrapper wrapper;
  WINDOW* screen_window = create_screen(TERMINAL_MAX_ROWS, TERMINAL_MAX_COLS, 0, 0);

  screens.push_back(screen_window);

  int current_row = 0;
  int current_col = 0;

  // Display the header if the text is defined.  Some screens (like the quest list,
  // etc) will have this defined, while others (such as the new character-type
  // screens) will not.
  string header_text = StringTable::get(current_screen.get_title_text_sid());
  uint num_pages = current_screen.get_num_pages();

  if (num_pages > 1)
  {
    ostringstream ss;

    ss << header_text << " (" << current_screen.get_current_page_number() << "/" << num_pages << ")";
    header_text = ss.str();
  }

  if (!header_text.empty())
  {
    display_header(header_text, screen_window, current_row);

    // Always allow for some space between the title and the components of the
    // screen, regardless of what the screen has set for line spacing.
    current_row += 2;
  }

  vector<ScreenComponentPtr> components = current_screen.get_current_page();
  uint line_incr = current_screen.get_line_increment();

  uint csize = components.size();
  for(uint i = 0; i < csize; i++)
  {
    ScreenComponentPtr component = components.at(i);
    ComponentAlignment ca = component->get_spacing_after();

    // Check to see if we should override the screen's line increment value.
    if (ca.get_override_default())
    {
      line_incr = ca.get_value();
    }

    if (component)
    {
      TextComponentPtr tc = dynamic_pointer_cast<TextComponent>(component);

      if (tc != nullptr)
      {
        display_text_component(screen_window, &current_row, &current_col, tc, line_incr);
      }
      else
      {
        OptionsComponentPtr oc = dynamic_pointer_cast<OptionsComponent>(component);

        if (oc != nullptr)
        {
          // Process the options...
          display_options_component(screen_window, &current_row, &current_col, oc);

          // Add them so that the prompt processor knows about the options in this set.
          wrapper.add_options(oc);
        }
      }

      // After each line, check to see if we need to throw up a prompt because
      // of hitting the end of the screen, but only if there's still stuff to
      // display.
      if (current_row == (TERMINAL_MAX_ROWS - 1) && (i != csize-1))
      {
        PromptPtr prompt = current_screen.get_prompt();
        prompt_processor.show_prompt(screen_window, prompt, current_row, current_col, TERMINAL_MAX_ROWS, TERMINAL_MAX_COLS);

        result = prompt_processor.get_prompt(screen_window, wrapper, prompt);

        wrefresh(screen_window);

        // We've shown the prompt, the user has intervened, and so
        // now we need to clear the window, reset the current row
        // back to 0 and keep displaying stuff from the screen.
        wclear(screen_window);
        current_row = 0;
      }
    }
  }

  // Done!  Add an appropriate prompt.
  PromptPtr prompt = current_screen.get_prompt();
  prompt_processor.show_prompt(screen_window, prompt, current_row, current_col, TERMINAL_MAX_ROWS, TERMINAL_MAX_COLS);

  result = prompt_processor.get_prompt(screen_window, wrapper, prompt);

  wrefresh(screen_window);

  return result;
}

// Show confirmation text - use the message buffer.
void CursesDisplay::confirm(const string& confirmation_message)
{
  add_message(confirmation_message, Colour::COLOUR_WHITE, false);
}

void CursesDisplay::display_text_component(WINDOW* window, int* row, int* col, TextComponentPtr tc, const uint line_incr)
{
  int cur_col = *col;

  if (tc != nullptr)
  {
    vector<pair<string, Colour>> current_text = tc->get_text();

    for (auto& text_line : current_text)
    {  
      string cur_text = text_line.first;
      boost::replace_all(cur_text, "%", "%%");

      enable_colour(static_cast<int>(text_line.second), window);
      mvwprintw(window, *row, cur_col, cur_text.c_str());
      disable_colour(static_cast<int>(text_line.second), window);

      cur_col += cur_text.size();
    }

    *row += line_incr;
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

        if (!option_desc.empty())
        {
          option_text->add_text(" - ");
          option_text->add_text(option_desc);
        }
      }

      enable_colour(static_cast<int>(option_colour), window);

      ostringstream display_option;
      display_option << "  [" << current_option.get_id_char() << "] ";

      int ocol = *col;

      string display_option_s = display_option.str();
      boost::replace_all(display_option_s, "%", "%%");

      mvwprintw(window, *row, ocol, display_option_s.c_str());
      
      getyx(window, *row, ocol);

      TextComponentPtr text = current_option.get_description();

      // JCD FIXME make 1 a constant later -
      // there should always be a single line break between options.
      display_text_component(window, row, &ocol, text, 1);
      disable_colour(static_cast<int>(option_colour), window);

      options_added++;
      temp_row++;
    }
  }

  // No need to update *row
  // It will have been taken care of when displaying the TextComponent.
}

void CursesDisplay::clear_screen()
{
  if (!screens.empty())
  {
    WINDOW* current_screen_window = screens.back();
    wclear(current_screen_window);
    wrefresh(current_screen_window);
    destroy_screen(current_screen_window);

    screens.pop_back();
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

  pair<string, Colour> alignment = player_stats.get_alignment();

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
  if (can_print) can_print = print_display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, defence, alignment.first);
  if (can_print) can_print = print_display_statistic_and_update_row_and_column(initial_row, &current_row, &current_col, alignment.first, speed, alignment.second);
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

        string sail = status_ailment.first;
        boost::replace_all(sail, "%", "%%");

        enable_colour(static_cast<int>(colour), stdscr);
        mvprintw(current_row, current_col, sail.c_str());
        disable_colour(static_cast<int>(colour), stdscr);
      }
    }
  }
}

bool CursesDisplay::print_display_statistic_and_update_row_and_column(const unsigned int initial_row, unsigned int* current_row, unsigned int* current_col, const string& current_stat, const string& next_stat, Colour print_colour)
{
  bool can_print = true;
  string stat = current_stat;
  boost::replace_all(stat, "%", "%%");

  enable_colour(static_cast<int>(print_colour), stdscr);
  mvprintw(*current_row, *current_col, stat.c_str());
  can_print = update_synopsis_row_and_column(initial_row, current_row, current_col, current_stat, next_stat);
  disable_colour(static_cast<int>(print_colour), stdscr);

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
  int white = static_cast<int>(Colour::COLOUR_WHITE);
  enable_colour(white, window);

  string header = header_text;
  boost::replace_all(header, "%", "%%");

  size_t header_text_size = header.size();

  unsigned int header_start = (TERMINAL_MAX_COLS/2) - (header_text_size/2);
  unsigned int header_end = (TERMINAL_MAX_COLS/2) - (header_text_size/2) + header_text_size;

  for (unsigned int i = 0; i < header_start-1; i++)
  {
    mvwprintw(window, display_line, i, "-");
  }
  
  mvwprintw(window, display_line, header_start, header.c_str());
  
  for (unsigned int i = header_end+1; i < TERMINAL_MAX_COLS; i++)
  {
    mvwprintw(window, display_line, i, "-");
  }

  disable_colour(white, window);
}

WINDOW* CursesDisplay::get_current_screen()
{
  WINDOW* screen = stdscr;

  if (!screens.empty())
  {
    screen = screens.back();
  }

  return screen;
}

bool CursesDisplay::serialize(ostream& stream) const
{
  Display::serialize(stream);

  Serialize::write_uint(stream, TERMINAL_MAX_ROWS);
  Serialize::write_uint(stream, TERMINAL_MAX_COLS);
  Serialize::write_uint(stream, FIELD_SPACE);
  Serialize::write_uint(stream, MSG_BUFFER_LAST_Y);
  Serialize::write_uint(stream, MSG_BUFFER_LAST_X);
  
  // Screens are not serialized.  Saving can only be done on the main screen,
  // which will be reconstructed based on the game's map/etc data.

  // CursesPromptProcessor is stateless; don't write it.

  Serialize::write_bool(stream, can_use_colour);

  // cursor_mode is a constant set in the constructor - ignore it.

  return true;
}

bool CursesDisplay::deserialize(istream& stream)
{
  Display::deserialize(stream);

  Serialize::read_uint(stream, TERMINAL_MAX_ROWS);
  Serialize::read_uint(stream, TERMINAL_MAX_COLS);
  Serialize::read_uint(stream, FIELD_SPACE);
  Serialize::read_uint(stream, MSG_BUFFER_LAST_Y);
  Serialize::read_uint(stream, MSG_BUFFER_LAST_X);

  // Screens are not serialized.  Saving can only be done on the main screen,
  // which will be reconstructed based on the game's map/etc data.

  // CursesPromptProcessor is stateless; don't load it.

  Serialize::read_bool(stream, can_use_colour);

  // cursor_mode is a constant set in the constructor - ignore it.

  return true;
}

ClassIdentifier CursesDisplay::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_CURSES_DISPLAY;
}

#ifdef UNIT_TESTS
#include "unit_tests/CursesDisplay_test.cpp"
#endif
