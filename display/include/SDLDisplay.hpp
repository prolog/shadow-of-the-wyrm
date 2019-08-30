// General definition of an abstract Display so that multiple displays
// can be specified (curses-based, graphical tiles, etc).
#pragma once
#include "Display.hpp"

#ifdef _MSC_VER
#include "SDL.h"
#else
#include "SDL2/SDL.h"
#endif


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

	  // Return result is the response to whatever prompt is displayed
	  virtual std::string display_screen(const Screen& current_screen) override;
	  
	  // Show confirmation text on the display.
	  virtual void confirm(const std::string& confirmation_message) override;

	  virtual void clear_screen() override;

    virtual Display* clone() override;

  protected:
    void read_dimensions_from_settings();
    void read_font_into_texture();
    bool create_window_and_renderer();

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    int tile_width;
    int tile_height;
    int screen_width;
    int screen_height;
    
    static const int SCREEN_ROWS;
    static const int SCREEN_COLS;
  private:
    virtual ClassIdentifier internal_class_identifier() const override ;
};
