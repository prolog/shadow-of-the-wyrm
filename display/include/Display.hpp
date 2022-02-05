// General definition of an abstract Display so that multiple displays
// can be specified (curses-based, graphical tiles, etc).
#pragma once
#include <string>
#include "Animation.hpp"
#include "AnimationFactory.hpp"
#include "DisplayConstants.hpp"
#include "DisplayItem.hpp"
#include "DisplayMap.hpp"
#include "DisplayStatistics.hpp"
#include "ISerializable.hpp"
#include "MenuWrapper.hpp"
#include "Prompt.hpp"

class Screen;
class MapDisplayArea;
class Animation;
class Map;

class Display : public ISerializable
{
	public:
    Display();
    virtual ~Display() {};
    bool operator==(const Display& d) const;

	  virtual bool create() = 0;
	  virtual void tear_down() = 0;

    virtual bool display_splash(const bool enabled) = 0;

    virtual std::string get_name() const = 0;

    virtual void set_force_ascii(const bool new_force_ascii);
    virtual bool get_force_ascii() const;

    // Returns a SID to display in the message manager
    virtual std::string toggle_fullscreen() = 0;

    // Get the screen's current width
    virtual unsigned int get_width() const = 0;

    // Get the screen's current height
    virtual unsigned int get_height() const = 0;

    virtual void clear_messages() = 0;
    
    // Clears the message buffer, map, and info display.
    virtual void clear_display() = 0;

    // Clears from a given row to the bottom of the screen.
    virtual void clear_to_bottom(const int row) = 0;

    // Adds a message in the current window, clearing any existing messages and
    // requiring user input.
    virtual void add_alert(const std::string& message, const bool prompt_for_input) = 0;

    // Add a message to display to the user
    virtual void add_message(const std::string& message, const bool reset_cursor) ;
    virtual void add_message(const std::string& message, const Colour colour, const bool clear_prior_to_adding_message) = 0;
    virtual std::string add_message_with_prompt(const std::string& message, const Colour colour, const bool clear_prior, const std::string& default_for_esc_key) = 0;

    virtual bool uses_colour() const;

    // Halt the messages - require some form of input from the user to continue
    virtual void halt_messages() = 0;

    // Draws the map
    virtual void refresh_display_parameters() = 0;
    virtual void draw(const DisplayMap& current_map, const CursorSettings cs);
    virtual void redraw() = 0;

    // Draws on a portion of the map area.
    virtual void draw_update_map(const DisplayMap& update_map, const CursorSettings cs);

    // Update a single tile.
    // Engine coordinates are used - the display will calculate the correct coordinates for the display
    // to ignore the message display area.
    virtual void draw_tile(const uint y, const uint x, const DisplayTile& display_tile);

    // Create an animation factory for the display type.
    virtual AnimationFactoryPtr create_animation_factory() const;

    // Draws an animation.
    virtual void draw_animation(const Animation& animation, std::shared_ptr<Map> player_fov_map);
	  
	  // Displays the player info
	  virtual void display(const DisplayStatistics& player_stats);

    // Draw a particular map coordinate
    virtual void draw_coordinate(const DisplayTile& current_tile, const uint terminal_row, const uint terminal_col) = 0;

    // Used by the engine to query the display size, so the DisplayMap can be created accordingly.
    virtual MapDisplayArea get_map_display_area() = 0;

	  // Return result is the response to whatever prompt is displayed
	  virtual std::string display_screen(const Screen& current_screen);

	  // Show confirmation text on the display.
	  virtual void confirm(const std::string& confirmation_message);

    virtual void set_title(const std::string& title) = 0;
    virtual void show() = 0;
    virtual void hide() = 0;
	  virtual void clear_screen() = 0;
    virtual void refresh_and_clear_window() = 0;
    virtual std::string get_prompt_value(const Screen& screen, const MenuWrapper& wrapper, const int row, const int col) = 0;
    virtual void display_header(const std::string& header_str, const int row) = 0;
    virtual void setup_new_screen() = 0;
    virtual void refresh_current_window() = 0;
    virtual void display_text_component(int* row, int* col, TextComponentPtr text, const uint line_incr) = 0;
    virtual void display_options_component(int* row, int* col, OptionsComponentPtr oc) = 0;
    
    virtual int get_max_rows() const = 0;
    virtual int get_max_cols() const = 0;
    virtual int get_field_space() const;

    // Print the current display statistic at the specified row/column, unless we're in a different row than the initial one, and therefore
    // should line up the column with the next-available, previously-used column from the previous row.
    bool display_statistic_and_update_row_and_column(const unsigned int initial_row, unsigned int* current_row, unsigned int* current_col, const std::string& stat, const std::string& next_stat, Colour print_colour = Colour::COLOUR_WHITE);

    // Update the row/column position for the synopsis details.  Return false if we can't do any more updates (have run off the screen).
    // Though, ideally that will never happen.
    bool update_synopsis_row_and_column(const unsigned int initial_row, unsigned int* row, unsigned int* column, const std::string& previous_printed_field, const std::string& next_field);

    virtual void display_text(int row, int col, const std::string& s) = 0;
    virtual void enable_colour(const Colour colour) = 0;
    virtual void disable_colour(const Colour colour) = 0;
    virtual void set_colour(const int colour, const int r, const int g, const int b) = 0;

    virtual void set_spritesheets(const std::map<std::string, std::pair<std::string, std::unordered_map<std::string, Coordinate>>>& spritesheet_details) = 0;

    // Palettes
    virtual void set_palette_id(const std::string& new_palette_id) = 0;
    virtual void set_palette(const std::string& new_palette_id) = 0;
    virtual std::string get_palette_id() const = 0;
    virtual std::pair<bool, std::pair<std::string, std::string>> switch_colour_palette(const std::string& current_palette_id) = 0;

    // Property methods.
    virtual void set_properties(const std::map<std::string, std::string>& new_properties);
    virtual void set_property(const std::string& property, const std::string& value);
    virtual bool remove_property(const std::string& property);
    virtual std::string get_property(const std::string& property) const;

    // ISerializable methods
    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

    virtual Display* clone() = 0;

  protected:
    virtual void init_mono_if_necessary();
    virtual void draw_tile_init();
    virtual void redraw_cursor(const DisplayMap& current_map, const CursorSettings& cs, const uint map_rows) = 0;
    int get_cursor_mode(const CursorSettings cs) const;

    bool force_ascii;
    Colour mono_colour;
    std::map<std::string, std::string> display_properties;
    const int cursor_mode;
    uint msg_buffer_last_y;
    uint msg_buffer_last_x;

  private:
    virtual ClassIdentifier internal_class_identifier() const override = 0;
};

using DisplayPtr = std::shared_ptr<Display>;
