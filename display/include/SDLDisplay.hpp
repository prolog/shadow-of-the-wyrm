// General definition of an abstract Display so that multiple displays
// can be specified (curses-based, graphical tiles, etc).
#pragma once

#ifdef _MSC_VER
#include "SDL.h"
#else
#include "SDL2/SDL.h"
#endif

#include <deque>
#include "Display.hpp"
#include "SDLCursorLocation.hpp"
#include "SDLDisplayParameters.hpp"
#include "SDLPromptProcessor.hpp"

class SDLDisplay : public Display
{
	public:
    SDLDisplay();
    virtual ~SDLDisplay();
    
	  virtual bool create() override;
	  virtual void tear_down() override;

    // Get the screen's current width
    virtual unsigned int get_width() const;

    // Get the screen's current height
    virtual unsigned int get_height() const override;

    virtual void clear_messages() override;
    
    // Clears the message buffer, map, and info display.
    virtual void clear_display() override;

    // Adds a message in the current window, clearing any existing messages and
    // requiring user input.
    virtual void add_alert(const std::string& message, const bool prompt_for_input) override;

    // Add a message to display to the user
    virtual void add_message(const std::string& message, const bool reset_cursor) override;
    virtual void add_message(const std::string& message, const Colour colour, const bool clear_prior_to_adding_message) override;
    virtual std::string add_message_with_prompt(const std::string& message, const Colour colour, const bool clear_prior) override;

    // Halt the messages - require some form of input from the user to continue
    virtual void halt_messages() override;

    // Draws the map
	  virtual void draw(const DisplayMap& current_map, const CursorSettings cs) override;
    virtual void redraw() override;

    // Draws on a portion of the map area.
    virtual void draw_update_map(const DisplayMap& update_map, const CursorSettings cs) override;

    // Update a single tile.
    // Engine coordinates are used - the display will calculate the correct coordinates for the display
    // to ignore the message display area.
    virtual void draw_tile(const uint y, const uint x, const DisplayTile& display_tile) override;

    // Create an animation factory for the display type.
    virtual AnimationFactoryPtr create_animation_factory() const override;

    // Draws an animation.
    virtual void draw_animation(const Animation& animation) override;
	  
	  // Displays the player info
	  virtual void display(const DisplayStatistics& player_stats) override;

    // Used by the engine to query the display size, so the DisplayMap can be created accordingly.
    virtual MapDisplayArea get_map_display_area() override;

	  // Show confirmation text on the display.
	  virtual void confirm(const std::string& confirmation_message) override;

    virtual void set_title(const std::string& title) override;
    virtual void show() override;
    virtual void hide() override;
	  virtual void clear_screen() override;
    virtual void refresh_and_clear_window() override;
    virtual std::string get_prompt_value(const Screen& screen, const MenuWrapper& wrapper, const int row, const int col) override;
    virtual void display_header(const std::string& header_str, const int row) override;
    virtual void setup_new_screen() override;
    virtual void refresh_current_window() override;
    virtual void display_text_component(int* row, int* col, TextComponentPtr text, const uint line_incr) override;
    virtual void display_options_component(int* row, int* col, OptionsComponentPtr oc) override;
    virtual int get_max_rows() const override;
    virtual int get_max_cols() const override;

    // These functions are "dumb" and don't reset the row/col at all.  This
    // allows for finer control.
    void display_text(int row, int col, const std::string& s);
    void display_text(int row, int col, const char c);

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

    virtual Display* clone() override;

  protected:
    // Functions to help set up the SDL display
    bool read_dimensions_from_settings();
    bool read_font_into_texture();
    bool create_window_and_renderer();

    // Game-related functions
    void display_text_component(SDL_Window* window, int* row, int* col, TextComponentPtr text_component, const uint line_increment);

    void display_options_component(SDL_Window* window, int* row, int* col, OptionsComponentPtr options_component);
    std::pair<int, int> get_glyph_location_from_spritesheet(const char c);
    
    bool load_spritesheet_from_file(const std::string& path, SDL_Renderer* renderer);
    void free_font_spritesheet();

    SDL_Window* window = NULL;
    
    // The screens and cursors have a 1:1 relationship.  The screen cursor
    // at index i in its deque corresponds to the screen at index i in
    // the screens deque.
    std::deque<SDL_Texture*> screens;
    std::deque<SDLCursorLocation> screen_cursors;

    SDL_Renderer* renderer = NULL;

    SDLDisplayParameters sdld;
    SDLPromptProcessor prompt_processor;
    SDL_Texture* font_spritesheet;

    static const int SCREEN_ROWS;
    static const int SCREEN_COLS;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};


using SDLDisplayPtr = std::shared_ptr<SDLDisplay>;
