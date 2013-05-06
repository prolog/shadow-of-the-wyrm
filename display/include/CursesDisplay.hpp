#pragma once
#ifdef _MSC_VER
#include <curses.h>
#else
#include <ncurses.h>
#endif
#include <deque>
#include "Display.hpp"
#include "CursesMenuWrapper.hpp"
#include "CursesPromptProcessor.hpp"
#include "ISerializable.hpp"
#include "TextComponent.hpp"
#include "OptionsComponent.hpp"

class CursesDisplay : public Display
{
  public:
    CursesDisplay();
    bool operator==(const CursesDisplay& cd) const;

	  bool create();
	  void tear_down();

    unsigned int get_width() const;

    void clear_messages();
    void clear_display();

    void add_message(const std::string& message, const bool reset_prompt);
    void add_message(const std::string& message, const Colour colour, const bool reset_prompt);
    std::string add_message_with_prompt(const std::string& message, const Colour colour, const bool reset_prompt);

    void halt_messages();

	  void draw(const DisplayMap& current_map);
    void redraw();

    virtual void draw_update_map(const DisplayMap& update_map);
    virtual void draw_tile(const uint y, const uint x, const DisplayTile& tile);

    // Create an animation factory for the display type.
    AnimationFactoryPtr create_animation_factory() const;
    virtual void draw_animation(const Animation& animation);

    virtual void draw_coordinate(const DisplayTile& current_tile, const uint terminal_row, const uint terminal_col);

	  void display(const DisplayStatistics& player_stats);
	  
	  virtual void display_equipment(const DisplayEquipmentMap& equipment);	  
	  virtual int display_inventory(const DisplayInventoryMap& inventory);
	  
    MapDisplayArea get_map_display_area();

	  std::string display_menu(const Menu& current_menu);
    void display_header(const std::string& header_text, WINDOW* cur_window, const int display_line = 0);

	  void confirm(const std::string& confirmation_message);

	  void clear_menu();

    virtual Display* clone();

    WINDOW* get_current_menu();

    bool serialize(std::ostream& stream);
    bool deserialize(std::istream& stream);

  private:
    ClassIdentifier internal_class_identifier() const;

  protected:
    friend class SL_Display_CursesDisplayFixture; // test fixture

    bool uses_colour() const;

    // Setup colours the way ncurses requires.
    void initialize_colours();

    // These two methods are used to turn on/off colours for use
    // with mvprintw, etc.
    void enable_colour(const int colour, WINDOW* window);
    void disable_colour(const int colour, WINDOW* window);

    // Clear the message buffer.
    int clear_message_buffer();

    // Make the option look a little nicer.
    std::pair<char, std::string> get_formatted_option(const int option_num, const std::string& option_name, const std::string& option_desc, const bool show_desc) const;

    void refresh_terminal_size();
    void display_text_component(WINDOW* window, int* row, int* col, TextComponentPtr text_component, const uint line_increment);
    CursesMenuWrapper display_and_return_options_component(WINDOW* window, int* row, int* col, OptionsComponentPtr options_component);
    std::string display_prompt(WINDOW* menu_window, PromptPtr prompt, int row = 0, int col = 0);

    // Creation/destruction methods
    WINDOW* create_menu(int height, int width, int start_row, int start_col);
    void destroy_menu(WINDOW *menu);

    // Print the current display statistic at the specified row/column, unless we're in a different row than the initial one, and therefore
    // should line up the column with the next-available, previously-used column from the previous row.
    bool print_display_statistic_and_update_row_and_column(const unsigned int initial_row, unsigned int* current_row, unsigned int* current_col, const std::string& stat, const std::string& next_stat);

    // Update the row/column position for the synopsis details.  Return false if we can't do any more updates (have run off the screen).
    // Though, ideally that will never happen.
    bool update_synopsis_row_and_column(const unsigned int initial_row, unsigned int* row, unsigned int* column, const std::string& previous_printed_field, const std::string& next_field);

    uint TERMINAL_MAX_ROWS;
    uint TERMINAL_MAX_COLS;
    uint FIELD_SPACE;

    uint MSG_BUFFER_LAST_Y;
    uint MSG_BUFFER_LAST_X;

    // The display is represented as a stack of windows in ncurses; the game window is the lowest, and any menus
    // or submenus are layered as new windows on top of that.  Each time a Menu is done, a window is popped off
    // the stack and the display is re-drawn.
    std::deque<WINDOW*> menus;

    // Used to process the prompt
    CursesPromptProcessor prompt_processor;
    bool can_use_colour;
};
