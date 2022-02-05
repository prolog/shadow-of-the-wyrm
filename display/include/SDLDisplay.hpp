// General definition of an abstract Display so that multiple displays
// can be specified (curses-based, graphical tiles, etc).
#pragma once
#ifdef ENABLE_SDL

#include "sdl.hpp"

#include <deque>
#include <unordered_map>
#include <vector>
#include "Display.hpp"
#include "SDLCursorLocation.hpp"
#include "SDLDisplayParameters.hpp"
#include "SDLPromptProcessor.hpp"
#include "Settings.hpp"

enum class SDLWindowMode
{
  SDL_WINDOW_MODE_WINDOWED = 0,
  SDL_WINDOW_MODE_DESKTOP_FULLSCREEN = 1,
  SDL_WINDOW_MODE_FULLSCREEN = 2
};

class SDLDisplay : public Display
{
	public:
    SDLDisplay();
    virtual ~SDLDisplay();
    
	  virtual bool create() override;
	  virtual void tear_down() override;

    virtual bool display_splash(const bool enabled) override;

    virtual std::string toggle_fullscreen() override;

    virtual std::string get_name() const override;

    // Get the screen's current width
    virtual unsigned int get_width() const;

    // Get the screen's current height
    virtual unsigned int get_height() const override;

    virtual void clear_messages() override;
    
    // Clears the message buffer, map, and info display.
    virtual void clear_display() override;

    virtual void clear_to_bottom(const int row) override;

    // Adds a message in the current window, clearing any existing messages and
    // requiring user input.
    virtual void add_alert(const std::string& message, const bool prompt_for_input) override;

    // Add a message to display to the user
    virtual void add_message(const std::string& message, const Colour colour, const bool clear_prior_to_adding_message) override;
    virtual std::string add_message_with_prompt(const std::string& message, const Colour colour, const bool clear_prior, const std::string& default_for_esc_key) override;

    // Halt the messages - require some form of input from the user to continue
    virtual void halt_messages() override;

    virtual void refresh_display_parameters() override;
    virtual void redraw() override;

    virtual void draw_coordinate(const DisplayTile& current_tile, const uint terminal_row, const uint terminal_col) override;

    // Used by the engine to query the display size, so the DisplayMap can be created accordingly.
    virtual MapDisplayArea get_map_display_area() override;

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

    void display_text(int row, int col, const std::string& s) override;

    SDL_Colour get_colour(const Colour curses_colour, const bool fg_colour = true) const;
    SDL_Color get_colour(const int curses_colour, const bool fg_colour = true) const;
    void enable_colour(const Colour colour) override;
    void disable_colour(const Colour colour) override;
    virtual void set_colour(const int colour, const int r, const int g, const int b) override;

    virtual std::string display_screen(const Screen& current_screen) override;

    void set_spritesheets(const std::map<std::string, std::pair<std::string, std::unordered_map<std::string, Coordinate>>>& spritesheet_details) override;
    SDL_Texture* get_spritesheet(const std::string& spritesheet_idx);

    // Palettes
    void set_palette_id(const std::string& new_palette_id) override;
    virtual void set_palette(const std::string& new_palette_id) override;
    virtual std::string get_palette_id() const override;
    virtual std::pair<bool, std::pair<std::string, std::string>> switch_colour_palette(const std::string& current_palette_id) override;

    Coordinate get_spritesheet_coordinate(const SpritesheetLocation& ssl) const;

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

    virtual Display* clone() override;

  protected:
    void set_window_dimensions(const Settings& settings);

    // Functions to help set up the SDL display
    bool read_dimensions_from_settings();
    bool read_font_into_texture();
    bool read_colours_from_settings();
    bool create_window_and_renderer();
    void initialize_colours();
    void initialize_colours(const std::vector<SDL_Colour>& colourset);

    bool check_available_screen_dimensions();

    // Game-related functions
    void display_text_component(SDL_Window* window, int* row, int* col, TextComponentPtr text_component, const uint line_increment);

    void display_options_component(SDL_Window* window, int* row, int* col, OptionsComponentPtr options_component);
    std::pair<int, int> get_glyph_location_from_spritesheet(const char c);
    
    bool load_spritesheet_from_file(const std::string& path, SDL_Renderer* renderer);
    SDL_Texture* load_texture(const std::string& path, SDL_Renderer* renderer);
    void free_spritesheets();
    void free_screens();

    virtual void redraw_cursor(const DisplayMap& current_map, const CursorSettings& cs, const uint map_rows) override;

    std::pair<int, int> get_calculated_or_requested_window_size(const Settings& settings);
    std::pair<int, int> get_calculated_or_requested_window_location(const Settings& settings);

    std::unordered_map<int, SDL_Color> colours;

    SDL_Window* window = NULL;
    
    // The screens and cursors have a 1:1 relationship.  The screen cursor
    // at index i in its deque corresponds to the screen at index i in
    // the screens deque.
    std::deque<SDL_Texture*> screens;
    SDL_Texture* message_buffer_screen;

    std::deque<SDLCursorLocation> screen_cursors;

    SDL_Window* splash_window = NULL;
    SDL_Renderer* splash_renderer = NULL;
    SDL_Renderer* renderer = NULL;

    SDLDisplayParameters sdld;
    SDLPromptProcessor prompt_processor;

    // The texture with the empty string key is the font spritesheet.
    // All other textures should have a string key with length > 0.
    std::unordered_map<std::string, SDL_Texture*> spritesheets;
    std::unordered_map<std::string, std::unordered_map<std::string, Coordinate>> spritesheet_references;
    std::map<std::string, std::pair<std::string, std::vector<SDL_Colour>>> palettes;
    std::string cur_palette_id;

    static const int SCREEN_ROWS;
    static const int SCREEN_COLS;
    static const int NUM_SDL_BASE_COLOURS;
    static const std::string TEXT_ID;
    static const std::string PALETTES_SETTING;
    static const std::string DEFAULT_PALETTE_SETTING;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

#endif
