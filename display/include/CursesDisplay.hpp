#pragma once
#ifdef _MSC_VER
#include <curses.h>
#else
#define NCURSES_OPAQUE 0
#include <ncurses.h>
#endif
#include <deque>
#include "Display.hpp"
#include "CursesPromptProcessor.hpp"
#include "ISerializable.hpp"
#include "MenuWrapper.hpp"
#include "TextComponent.hpp"
#include "OptionsComponent.hpp"

class CursesDisplay : public Display
{
  public:
    CursesDisplay();
    bool operator==(const CursesDisplay& cd) const;

	  bool create() override;
	  void tear_down() override;

    unsigned int get_width() const override;
    unsigned int get_height() const override;

    void clear_messages() override;
    void clear_display() override;
    void clear_to_bottom(const int row) override;

    // Adds a message in the current window, clearing any existing messages and
    // requiring user input.
    void add_alert(const std::string& message, const bool require_input) override;

    // Functions to add messages to the message buffer.
    void add_message(const std::string& message, const Colour colour, const bool reset_prompt) override;
    std::string add_message_with_prompt(const std::string& message, const Colour colour, const bool reset_prompt) override;

    void halt_messages() override;

    virtual void refresh_display_parameters() override;
    void redraw() override;

    // Create an animation factory for the display type.
    AnimationFactoryPtr create_animation_factory() const override;

    virtual void draw_coordinate(const DisplayTile& current_tile, const uint terminal_row, const uint terminal_col) override;
    MapDisplayArea get_map_display_area() override;

    void display_header(const std::string& header_text, WINDOW* cur_window, const int display_line = 0);

	  void confirm(const std::string& confirmation_message) override;

    void set_title(const std::string& title) override;
    void show() override;
    void hide() override;
	  void clear_screen() override;

    virtual Display* clone() override;

    WINDOW* get_current_screen();
    WINDOW* get_message_buffer_screen();

    // Creation/destruction methods.
    // Generally, don't use these.  Know what you're doing!
    WINDOW* create_screen(int height, int width, int start_row, int start_col);
    void destroy_screen(WINDOW *screen);

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

    static uint TERMINAL_MAX_ROWS;
    static uint TERMINAL_MAX_COLS;

  private:
    ClassIdentifier internal_class_identifier() const override;

  protected:
    friend class SW_Display_CursesDisplayFixture; // test fixture

    virtual void redraw_cursor(const DisplayMap& current_map, const CursorSettings& cs, const uint map_rows) override;
    virtual void draw_tile_init() override;

    int get_cursor_mode(const CursorSettings cs) const;

    // Setup colours the way ncurses requires.
    void initialize_colours();

    // These are used to turn on/off colours for use
    // with mvprintw, etc.
    //
    // Without a WINDOW* argument, stdscr is used.
    virtual void enable_colour(const Colour colour) override;
    virtual void disable_colour(const Colour colour) override;

    void enable_colour(const int colour, WINDOW* window);
    void disable_colour(const int colour, WINDOW* window);

    // Set colour sets the colour without checking to see if we're in
    // monochrome mode or not.
    void set_colour(const int colour, WINDOW* window);

    // Clear the message buffer.
    int clear_message_buffer();

    void refresh_terminal_size();
    void refresh_and_clear_window() override;
    virtual std::string get_prompt_value(const Screen& screen, const MenuWrapper& wrapper, const int row, const int col) override;
    virtual void display_header(const std::string& header, const int row) override;
    virtual void setup_new_screen() override;
    virtual void refresh_current_window() override;
    virtual void display_text_component(int* row, int* col, TextComponentPtr text, const uint line_incr) override;
    virtual void display_options_component(int* row, int* col, OptionsComponentPtr oc) override;
    virtual int get_max_rows() const override;
    virtual int get_max_cols() const override;

    void display_text_component(WINDOW* window, int* row, int* col, TextComponentPtr text_component, const uint line_increment);
    void display_options_component(WINDOW* window, int* row, int* col, OptionsComponentPtr options_component);

    // Display text safely on stdscr - does % replacement
    void display_text(int row, int col, const std::string& s) override;

    uint MSG_BUFFER_LAST_Y;
    uint MSG_BUFFER_LAST_X;

    // The display is represented as a stack of windows in ncurses; the game window is the lowest, and any screens
    // or subscreens are layered as new windows on top of that.  Each time a screen is done, a window is popped off
    // the stack and the display is re-drawn.
    std::deque<WINDOW*> screens;
    WINDOW* message_buffer_screen;

    // Used to process the prompt
    CursesPromptProcessor prompt_processor;
    bool can_use_colour;
    const int cursor_mode;
};
