#pragma once
#include <ncurses/ncurses.h>
#include <ncurses/menu.h>
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

    void clear_messages();
    void clear_display();

    void add_message(const std::string& message);
    void add_message(const std::string& message, bool reset_prompt);

	  void draw(const DisplayMap& current_map);

	  void display(const DisplayStatistics& player_stats);
	  
	  // JCD FIXME: Add stuff to the function arguments and return value later.
	  virtual void display_equipment();
	  
	  virtual void display_inventory();
	  
    MapDisplayArea get_map_display_area();

	  std::string display_menu(const Menu& current_menu);

	  void confirm(const std::string& confirmation_message);

	  void clear_menu();

  protected:
    bool uses_colour() const;

    // Setup colours the way ncurses requires.
    void initialize_colours();

    // These two methods are used to turn on/off colours for use
    // with mvprintw, etc.
    void enable_colour(const int colour);
    void disable_colour(const int colour);

    // Clear the message buffer.
    int clear_message_buffer();

    void refresh_terminal_size();
    void display_text_component(WINDOW* window, int* row, int* col, TextComponent* text_component);
    NCursesMenuWrapper display_and_return_options_component(WINDOW* window, int* row, int* col, OptionsComponent* options_component);
    std::string display_prompt(WINDOW* menu_window, PromptPtr prompt, int row = 0, int col = 0);

    // Creation/destruction methods
    WINDOW* create_menu(int height, int width, int start_row, int start_col);
    void destroy_menu(WINDOW *menu);

    // Print the current display statistic at the specified row/column, unless we're in a different row than the initial one, and therefore
    // should line up the column with the next-available, previously-used column from the previous row.
    bool print_display_statistic_and_update_row_and_column(const int initial_row, int* current_row, int* current_col, const std::string& stat, const std::string& next_stat);

    // Update the row/column position for the synopsis details.  Return false if we can't do any more updates (have run off the screen).
    // Though, ideally that will never happen.
    bool update_synopsis_row_and_column(const int initial_row, int* row, int* column, const std::string& previous_printed_field, const std::string& next_field);

    int TERMINAL_MAX_ROWS;
    int TERMINAL_MAX_COLS;
    int FIELD_SPACE;

    int MAP_START_ROW;
    int MAP_START_COL;

    // The display is represented as a stack of windows in ncurses; the game window is the lowest, and any menus
    // or submenus are layered as new windows on top of that.  Each time a Menu is done, a window is popped off
    // the stack and the display is re-drawn.
    std::stack<WINDOW*> menus;

    // Used to process the prompt
    NCursesPromptProcessor prompt_processor;
    bool can_use_colour;
};
