#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include "Conversion.hpp"
#include "SDLKeyboardController.hpp"
#include "SDLDisplay.hpp"
#include "SDLRender.hpp"
#include "Game.hpp"
#include "Log.hpp"
#include "MapDisplayArea.hpp"
#include "Screen.hpp"
#include "Serialize.hpp"
#include "Setting.hpp"
#include "TextKeys.hpp"
#include "TextMessages.hpp"

#ifdef _MSC_VER
#include "SDL_image.h"
#else
#include "SDL2/SDL_image.h"
#endif

using namespace std;

const int SDLDisplay::SCREEN_ROWS = 25;
const int SDLDisplay::SCREEN_COLS = 80;
const int SDLDisplay::NUM_SDL_BASE_COLOURS = 16;
const string SDLDisplay::TEXT_ID = "";
const string SDLDisplay::PALETTES_SETTING = "colour_palettes";
const string SDLDisplay::DEFAULT_PALETTE_SETTING = "colour_palettes_default";

SDLDisplay::SDLDisplay()
{
  window = nullptr;
  renderer = nullptr;
  message_buffer_screen = nullptr;

  sdld.set_screen_rows(SCREEN_ROWS);
  sdld.set_screen_cols(SCREEN_COLS);

  initialize_colours();
}

SDLDisplay::~SDLDisplay()
{
}

bool SDLDisplay::create()
{
  bool init = true;

  init = read_colours_from_settings();
  init = read_dimensions_from_settings();

  if (init)
  {
    init = check_available_screen_dimensions();

    if (init)
    {
      init = create_window_and_renderer();

      if (init)
      {
        init = read_font_into_texture();

        if (!init)
        {
          std::cerr << "Could not read font into texture" << std::endl;
        }
      }
      else
      {
        std::cerr << "Could not read create window and renderer" << std::endl;
      }
    }
    else
    {
      std::cerr << "Screen is smaller than required " << sdld.get_screen_width() << "x" << sdld.get_screen_height() << " - increase resolution and restart, or change to display=curses in swyrm.ini" << std::endl;
    }
  }
  else
  {
    std::cerr << "Could not read dimensions from settings" << std::endl;
  }

  
  if (init)
  {
    enable_colour(Colour::COLOUR_WHITE);

    // Set up the main screen, analagous to stdscr in curses.
    setup_new_screen();
  }

  return init;
}

void SDLDisplay::tear_down()
{
  free_spritesheets();
  free_screens();

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

bool SDLDisplay::check_available_screen_dimensions()
{
  bool dim_ok = true;
  SDL_DisplayMode display_mode;
  SDL_GetCurrentDisplayMode(0, &display_mode);
  auto avail_width = display_mode.w;
  auto avail_height = display_mode.h;

  if (avail_width < sdld.get_screen_width() || avail_height < sdld.get_screen_height())
  {
    dim_ok = false;
  }

  return dim_ok;
}

void SDLDisplay::initialize_colours()
{
  colours = { /* black                */ {0, {0,0,0,255} }, 
              /* red                  */ {1, {180,0,0,255} },
              /* green                */ {2, {0,159,0,255} },
              /* yellow               */ {3, {159,159,0,255} },
              /* blue                 */ {4, {0,100,200,255} },
              /* magenta              */ {5, {159,0,159,255} },
              /* cyan                 */ {6, {0,159,159,255} },
              /* white                */ {7, {200,200,200,255} },
              /* bold black/dark gray */ {8, {67,99,99,255} },
              /* bold red             */ {9, {255,0,0,255} },
              /* bold green           */ {10, {0,255,0,255} },
              /* bold yellow          */ {11, {255,255,0,255} },
              /* bold blue            */ {12, {0,0,255,255} },
              /* bold magenta         */ {13, {255,0,255,255} },
              /* bold cyan            */ {14, {0,255,255,255} },
              /* bold white           */ {15, {255,255,255,255} }
  };
}

void SDLDisplay::initialize_colours(const vector<SDL_Colour>& colourset)
{
  if (colours.size() == NUM_SDL_BASE_COLOURS)
  {
    for (size_t i = 0; i < NUM_SDL_BASE_COLOURS; i++)
    {
      SDL_Colour cur_colour = colourset[i];
      colours[i] = cur_colour;
    }
  }
}

bool SDLDisplay::read_dimensions_from_settings()
{
  bool dim_val = false;

  string tile_size = get_property(Setting::DISPLAY_TILE_SIZE);
  vector<string> tile_spl;

  // The dimensions are in HxW format, eg, 8x8, 8x16, ...
  boost::split(tile_spl, tile_size, boost::is_any_of("x"));

  if (tile_spl.size() >= 2)
  {
    int glyph_width = String::to_int(tile_spl[0]);
    int glyph_height = String::to_int(tile_spl[1]);

    sdld.set_glyph_width(glyph_width);
    sdld.set_glyph_height(glyph_height);

    sdld.set_screen_width(sdld.get_screen_cols() * glyph_width);
    sdld.set_screen_height(sdld.get_screen_rows() * glyph_height);
  }

  string tile_glyphs_per_line = get_property(Setting::DISPLAY_TILE_GLYPHS_PER_LINE);
  int glyphs_per_line = String::to_int(tile_glyphs_per_line);
  sdld.set_glyphs_per_line(glyphs_per_line);

  string num_glyphs_s = get_property(Setting::DISPLAY_NUM_GLYPHS);
  int num_glyphs = String::to_int(num_glyphs_s);
  sdld.set_num_glyphs(num_glyphs);

  dim_val = (tile_spl.size() >= 2 && !tile_glyphs_per_line.empty() && glyphs_per_line > 0);
  return dim_val;
}

bool SDLDisplay::read_font_into_texture()
{
  bool font_result = true;
  string font_path = get_property(Setting::DISPLAY_FONT);

  if (!load_spritesheet_from_file(font_path, renderer))
  {
    ostringstream ss;
    ss << "Could not read font from path: " << font_path;
    Log::instance().error(ss.str());
    font_result = false;
  }

  return font_result;
}

bool SDLDisplay::read_colours_from_settings()
{
  vector<string> sdl_palettes = String::create_string_vector_from_csv_string(get_property(Setting::DISPLAY_SDL_PREFIX + PALETTES_SETTING));
  string default_palette = get_property(Setting::DISPLAY_SDL_PREFIX + DEFAULT_PALETTE_SETTING);

  // Read the colours
  for (const string& p : sdl_palettes)
  {
    string palette_name = get_property(Setting::DISPLAY_SDL_PREFIX + p + "_name");
    vector<SDL_Colour> palette_colours;

    for (uint i = 0; i <= static_cast<int>(Colour::COLOUR_MAX); i++)
    {
      string colour_setting = Setting::DISPLAY_SDL_PREFIX + p + "_colour_" + std::to_string(i);
      string colour_val = get_property(colour_setting);

      if (!colour_val.empty())
      {
        std::vector<std::string> rgba;
        boost::split(rgba, colour_val, boost::is_any_of(", "));

        if (rgba.size() == 4)
        {
          Uint8 r = String::to_int(rgba.at(0));
          Uint8 g = String::to_int(rgba.at(1));
          Uint8 b = String::to_int(rgba.at(2));
          Uint8 a = String::to_int(rgba.at(3));

          if (r >= 0 && r <= 255 &&
            g >= 0 && g <= 255 &&
            b >= 0 && b <= 255 &&
            a >= 0 && a <= 255)
          {
            palette_colours.push_back({ r,g,b,a });
          }
        }
      }

    }

    if (palette_colours.size() == NUM_SDL_BASE_COLOURS && palette_name.empty() == false)
    {
      palettes[p] = make_pair(palette_name, palette_colours);
    }
  }

  // Set the default
  auto p_it = palettes.find(default_palette);

  if (p_it != palettes.end())
  {
    pair<string, vector<SDL_Colour>> palette_details = p_it->second;

    for (uint i = 0; i < NUM_SDL_BASE_COLOURS; i++)
    {
      colours[i] = palette_details.second[i];
    }
  }

  cur_palette_id = default_palette;

  return true;
}

bool SDLDisplay::create_window_and_renderer()
{
  bool wr_created = true;
  ostringstream ss;

  string window_title = StringTable::get(TextKeys::SW_TITLE);
  window = SDL_CreateWindow(window_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, sdld.get_screen_width(), sdld.get_screen_height(), SDL_WINDOW_SHOWN);
  if (window == NULL)
  {
    ss << "Window could not be created! SDL Error: " << SDL_GetError();
    Log::instance().error(ss.str());

    wr_created = false;
  }
  else
  {
    //Create vsynced renderer for window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == NULL)
    {
      ss << "Renderer could not be created! SDL Error: %s\n" << SDL_GetError();
      Log::instance().error(ss.str());

      wr_created = false;
    }
  }

  return wr_created;
}

// width is in rows
unsigned int SDLDisplay::get_width() const
{
  return sdld.get_screen_cols();
}

// height is in rows
unsigned int SDLDisplay::get_height() const
{
  return sdld.get_screen_rows();
}

void SDLDisplay::clear_messages()
{
  if (!screens.empty() && !screen_cursors.empty())
  {
    int text_size = sdld.get_glyph_height();
    int clear_height = text_size * DisplayConstants::MESSAGE_BUFFER_ROWS;
    SDL_Rect dst_rect;
    dst_rect.y = 0;
    dst_rect.x = 0;
    dst_rect.h = clear_height;
    dst_rect.w = sdld.get_screen_width();

    SDLRender render(sdld);
    render.fill_area(renderer, screens.back(), &dst_rect, get_colour(Colour::COLOUR_BLACK));
    refresh_current_window();

    SDLCursorLocation& sdlc = screen_cursors.back();
    sdlc.set_y(0);
    sdlc.set_x(0);

    msg_buffer_last_y = 0;
    msg_buffer_last_x = 0;
  }
}

void SDLDisplay::clear_display()
{
  clear_to_bottom(0);
}

void SDLDisplay::clear_to_bottom(const int row)
{
  int glyph_height = sdld.get_glyph_height();
  int rows = sdld.get_screen_rows();
  int rows_to_blank = rows - row;

  if (rows_to_blank > 0 && !screens.empty() && !screen_cursors.empty())
  {
    SDLRender render(sdld);
    SDL_Rect dst_rect = {0, 0, 0, 0};

    dst_rect.y = row * glyph_height;
    dst_rect.x = 0;
    dst_rect.h = rows_to_blank * glyph_height;
    dst_rect.w = sdld.get_screen_width();

    render.fill_area(renderer, screens.back(), &dst_rect, get_colour(0));
  }
}

void SDLDisplay::add_alert(const string& message, const bool prompt_for_input)
{
  if (!screens.empty() && !screen_cursors.empty())
  {
    clear_messages();

    message_buffer_screen = screens.back();
    add_message(message, Colour::COLOUR_BOLD_RED, false);
    refresh_current_window();

    if (prompt_for_input)
    {
      prompt_processor.get_prompt(window);
      clear_messages();
    }

    message_buffer_screen = nullptr;
  }
}

void SDLDisplay::add_message(const string& to_add_message, const Colour colour, const bool clear_prior_to_adding_message)
{
  if (!screens.empty() && !screen_cursors.empty())
  {
    SDL_Texture* screen = screens.at(0);

    if (message_buffer_screen != nullptr)
    {
      screen = message_buffer_screen;
    }

    string message = to_add_message;

    SDLCursorLocation& sdlc = screen_cursors.back();

    uint cur_y = 0;
    uint cur_x = 0;

    if (clear_prior_to_adding_message)
    {
      clear_messages();
    }
    else
    {
      sdlc.set_y(msg_buffer_last_y);
      sdlc.set_x(msg_buffer_last_x);
    }

    boost::char_separator<char> separator(" ", " ", boost::keep_empty_tokens); // Keep the tokens!
    boost::tokenizer<boost::char_separator<char>> tokens(message, separator);

    enable_colour(colour);
    SDLRender render(sdld);

    for (boost::tokenizer<boost::char_separator<char>>::iterator t_iter = tokens.begin(); t_iter != tokens.end(); t_iter++)
    {
      msg_buffer_last_y = sdlc.get_y();
      msg_buffer_last_x = sdlc.get_x();

      cur_y = msg_buffer_last_y;
      cur_x = msg_buffer_last_x;

      string current_token = *t_iter;

      if (cur_y == 0)
      {
        if ((cur_x + current_token.length()) > (static_cast<uint>(get_max_cols()) - 1))
        {
          // Move to the second line of the buffer
          sdlc.set_yx(1, 0);
          cur_y = sdlc.get_y();
          cur_x = sdlc.get_x();
        }
      }
      else
      {
        if ((cur_x + current_token.length()) > (static_cast<uint>(get_max_cols()))-4)
        {
          sdlc.set_yx(1, get_max_cols() - 4);

          disable_colour(colour);
          render.render_text(sdlc, renderer, spritesheets[TEXT_ID], screen, cur_y, cur_x, "...", sdld.get_fg_colour(), sdld.get_bg_colour());
          refresh_current_window();

          prompt_processor.get_prompt(window);
          enable_colour(colour);

          clear_messages();

          cur_y = msg_buffer_last_y;
          cur_x = msg_buffer_last_x;
        }
      }

      // If the user presses enter
      if (cur_y > DisplayConstants::MESSAGE_BUFFER_END_ROW)
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

      render.render_text(sdlc, renderer, spritesheets[TEXT_ID], screen, cur_y, cur_x, current_token, sdld.get_fg_colour(), sdld.get_bg_colour());

      // After rendering text, update the message buffer position.
      msg_buffer_last_y = sdlc.get_y();
      msg_buffer_last_x = sdlc.get_x();
    }

    // Once we're done, make sure the message buffer coordinates are properly
    // updated, and clear messages if necessary.
    msg_buffer_last_y = sdlc.get_y();
    msg_buffer_last_x = sdlc.get_x();

    disable_colour(colour);
  }

  refresh_current_window();
}

string SDLDisplay::add_message_with_prompt(const string& message, const Colour colour, const bool clear_prior, const std::string& default_for_esc_key)
{
  string prompt_result;

  if (!screens.empty() && !screen_cursors.empty())
  {
    SDLRender render(sdld);

    add_message(message, colour, clear_prior);
    prompt_result = prompt_processor.get_user_string(sdld, screen_cursors.back(), render, renderer, spritesheets[TEXT_ID], screens.back(), true /* allow arbitrary non-alphanumeric characters */, default_for_esc_key);
  }
  
  return prompt_result;
}

void SDLDisplay::halt_messages()
{
  // Get a keypress from the user and throw it away to continue.
  prompt_processor.get_prompt(window);
}

void SDLDisplay::refresh_display_parameters()
{
  // Resizing is currently disallowed.
}

void SDLDisplay::redraw()
{
  refresh_current_window();
}

void SDLDisplay::draw_coordinate(const DisplayTile& current_tile, const uint terminal_row, const uint terminal_col)
{
  if (!screens.empty() && !screen_cursors.empty())
  {
    SDLRender render(sdld);

    Colour colour = static_cast<Colour>(current_tile.get_colour());
    Symbol s = current_tile.get_symbol();
    uchar char_symbol = s.get_symbol();
    bool rendered = false;

    if (colour != Colour::COLOUR_UNDEFINED)
    {
      enable_colour(colour);
    }

    if (!force_ascii && s.get_uses_spritesheet())
    {
      SpritesheetLocation ssl = s.get_spritesheet_location();
      SDL_Texture* spritesheet = get_spritesheet(s.get_spritesheet_location_ref().get_index());

      if (spritesheet != nullptr)
      {
        Coordinate c = get_spritesheet_coordinate(ssl);
        render.render_glyph(screen_cursors.back(), renderer, spritesheet, screens.back(), terminal_row, terminal_col, c.first, c.second, sdld.get_fg_colour(), sdld.get_bg_colour());
        rendered = true;
      }
    }

    // If there were issues looking up the glyph, fall back on text.
    if (rendered == false)
    {
      render.render_text(screen_cursors.back(), renderer, spritesheets[TEXT_ID], screens.back(), terminal_row, terminal_col, char_symbol, sdld.get_fg_colour(), sdld.get_bg_colour());
    }

    if (colour != Colour::COLOUR_UNDEFINED)
    {
      disable_colour(colour);
    }
  }
}

MapDisplayArea SDLDisplay::get_map_display_area()
{
  MapDisplayArea map_display_area;

  map_display_area.set_width(sdld.get_screen_cols());
  map_display_area.set_height(sdld.get_screen_rows() - DisplayConstants::ROWS_FOR_MESSAGE_BUFFER_AND_SYNOPSIS);

  return map_display_area;
}

void SDLDisplay::set_title(const string& title)
{
  SDL_SetWindowTitle(window, title.c_str());
}

void SDLDisplay::show()
{
  SDL_ShowWindow(window);
  SDL_RaiseWindow(window);
}

void SDLDisplay::hide()
{
  SDL_HideWindow(window);
}

void SDLDisplay::clear_screen()
{
  if (!screens.empty() && !screen_cursors.empty())
  {
    SDL_Texture* current_screen = screens.back();

    screens.pop_back();
    screen_cursors.pop_back();

    SDL_DestroyTexture(current_screen);

    Game::instance().set_requires_redraw(true);
  }
}

void SDLDisplay::refresh_and_clear_window()
{
  if (!screens.empty() && !screen_cursors.empty())
  {
    clear_screen();
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderClear(renderer);
    SDL_SetRenderTarget(renderer, screens.back());
    screen_cursors.back().reset();
  }
}

void SDLDisplay::setup_new_screen()
{
  SDL_Texture* screen = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, sdld.get_screen_width(), sdld.get_screen_height());
  screens.push_back(screen);

  SDLCursorLocation cursor_loc(get_max_rows(), get_max_cols());
  screen_cursors.push_back(cursor_loc);

  clear_display();
}

// To render the screen, detach the renderer from the current texture and 
// use the renderer to display it.  Then, reattach to the current screen
// (texture).
void SDLDisplay::refresh_current_window()
{
  if (!screens.empty() && !screen_cursors.empty())
  {
    SDL_Texture* cur_screen = screens.back();

    SDL_SetRenderTarget(renderer, NULL);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, cur_screen, NULL, NULL);
    SDL_RenderPresent(renderer);

    SDL_SetRenderTarget(renderer, cur_screen);
  }
}

int SDLDisplay::get_max_rows() const
{
  return SCREEN_ROWS;
}

int SDLDisplay::get_max_cols() const
{
  return SCREEN_COLS;
}

void SDLDisplay::display_text_component(int* row, int* col, TextComponentPtr text, const uint line_incr)
{
  display_text_component(window, row, col, text, line_incr);
}

void SDLDisplay::display_options_component(int* row, int* col, OptionsComponentPtr oc)
{
  display_options_component(window, row, col, oc);
}

string SDLDisplay::get_prompt_value(const Screen& screen, const MenuWrapper& menu_wrapper, const int row, const int col)
{
  string prompt_val;

  if (!screens.empty() && !screen_cursors.empty())
  {
    SDL_Texture* current_screen = screens.back();
    SDLCursorLocation& cursor_loc = screen_cursors.back();

    SDLRender text_renderer(sdld);
    Prompt* prompt = screen.get_prompt();
    prompt_processor.show_prompt(sdld, cursor_loc, text_renderer, renderer, spritesheets[TEXT_ID], current_screen, prompt, row, col, get_max_rows(), get_max_cols());
    refresh_current_window();

    prompt_val = prompt_processor.get_prompt(sdld, cursor_loc, text_renderer, renderer, spritesheets[TEXT_ID], current_screen, menu_wrapper, prompt);
  }

  return prompt_val;
}

void SDLDisplay::display_header(const string& header_text, const int row)
{
  if (!screens.empty() && !screen_cursors.empty())
  {
    SDLRender render(sdld);

    string full_header = TextMessages::get_full_header_text(header_text, sdld.get_screen_cols());
    render.render_text(screen_cursors.back(), renderer, spritesheets[TEXT_ID], screens.back(), row, 0, full_header, sdld.get_fg_colour(), sdld.get_bg_colour());
  }
}

void SDLDisplay::display_text_component(SDL_Window* window, int* row, int* col, TextComponentPtr tc, const uint line_incr)
{
  if (!screens.empty() && !screen_cursors.empty())
  {
    SDLRender text_renderer(sdld);
    SDL_Texture* texture = screens.back();
    SDL_Texture* text_spritesheet = spritesheets[TEXT_ID];

    if (tc != nullptr && row != nullptr && col != nullptr)
    {
      vector<pair<string, Colour>> current_text = tc->get_text();
      vector<Symbol> symbols = tc->get_symbols();

      for (auto& text_line : current_text)
      {
        string cur_text = text_line.first;
        Colour colour = text_line.second;

        // Loop through the given string.  For each character, render it,
        // and increment the column.
        size_t txt_size = cur_text.size();
        size_t sym_size = symbols.size();

        size_t cur_sym = 0;
        size_t cur_char = 0;

        while (cur_char < txt_size)
        {
          char c = cur_text[cur_char];

          if (c == '%' && cur_char < txt_size - 1 && cur_text[cur_char + 1] == 's' && cur_sym < sym_size)
          {
            Symbol s = symbols[cur_sym];
            DisplayTile dt(s);
            draw_coordinate(dt, *row, *col);
            *col += 1;
            cur_char += 2;
          }
          else
          {
            text_renderer.render_text(screen_cursors.back(), renderer, text_spritesheet, texture, *row, *col, c, get_colour(colour), sdld.get_bg_colour());
            *col += 1;
            cur_char++;
          }
        }
      }

      *col = 0;
      *row += line_incr;
    }
  }
}

void SDLDisplay::display_text(const int row, const int col, const string& s)
{
  if (!screens.empty() && !screen_cursors.empty())
  {
    SDLRender text_renderer(sdld);
    text_renderer.render_text(screen_cursors.back(), renderer, spritesheets[TEXT_ID], screens.back(), row, col, s, sdld.get_fg_colour(), sdld.get_bg_colour());
  }
}

void SDLDisplay::display_options_component(SDL_Window* window, int* row, int* col, OptionsComponentPtr oc)
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

      ostringstream display_option;
      display_option << "  [" << current_option.get_id_char() << "] ";
      string display_option_s = display_option.str();
      display_text(*row, *col, display_option_s);

      int ocol = *col + display_option_s.size();

      TextComponentPtr text = current_option.get_description();

      display_text_component(window, row, &ocol, text, DisplayConstants::OPTION_SPACING);

      options_added++;
      temp_row++;
    }
  }

  // No need to update *row
  // It will have been taken care of when displaying the TextComponent.
}

SDL_Color SDLDisplay::get_colour(const Colour curses_colour) const
{
  return get_colour(static_cast<int>(curses_colour));
}

SDL_Color SDLDisplay::get_colour(const int curses_colour) const
{
  SDL_Color c = { 0,0,0,255 };

  auto c_it = colours.find(curses_colour);

  if (c_it != colours.end())
  {
    c = c_it->second;
  }

  return c;
}

void SDLDisplay::enable_colour(const Colour colour)
{
  Colour c = colour;

  if (uses_colour() == false)
  {
    init_mono_if_necessary();
    c = mono_colour;
  }

  int colour_i = static_cast<int>(c);
  int colour_fg_curses = colour_i % NUM_SDL_BASE_COLOURS;
  int colour_bg_curses = colour_i / NUM_SDL_BASE_COLOURS;

  sdld.set_fg_colour(get_colour(colour_fg_curses));
  sdld.set_bg_colour(get_colour(colour_bg_curses));
}

void SDLDisplay::disable_colour(const Colour colour)
{
  if (uses_colour())
  {
    enable_colour(Colour::COLOUR_WHITE);
  }
}

void SDLDisplay::set_colour(const int colour, const int r, const int g, const int b)
{
  if (colour >= 0 && colour <= 127 &&
      r >= 0 && r <= 255 &&
      g >= 0 && g <= 255 &&
      b >= 0 && b <= 255)
  {
    Uint8 a = 255;
    colours[colour] = { static_cast<Uint8>(r), 
                        static_cast<Uint8>(g), 
                        static_cast<Uint8>(b), 
                        a };
  }
}

// When displaying a general screen, reset the colour to white.
string SDLDisplay::display_screen(const Screen& current_screen)
{
  enable_colour(Colour::COLOUR_WHITE);
  return Display::display_screen(current_screen);
}

void SDLDisplay::set_spritesheets(const map<string, pair<string, unordered_map<string, Coordinate>>>& spritesheet_ids_and_files)
{
  for (auto ss_it : spritesheet_ids_and_files)
  {
    string spritesheet_id = ss_it.first;
    string filename = ss_it.second.first;

    // If the spritesheet already exists (we might be reloading textures),
    // free it.
    auto ss_texture_it = spritesheets.find(spritesheet_id);
    if (ss_texture_it != spritesheets.end())
    {
      SDL_Texture* existing_texture = ss_texture_it->second;
      SDL_DestroyTexture(existing_texture);
    }

    SDL_Texture* spritesheet = load_texture(filename, renderer);
    spritesheets[spritesheet_id] = spritesheet;

    unordered_map<string, Coordinate> refs = ss_it.second.second;
    spritesheet_references[spritesheet_id] = refs;
  }
}

SDL_Texture* SDLDisplay::get_spritesheet(const string& spritesheet_idx)
{
  SDL_Texture* ss = nullptr;

  auto ss_it = spritesheets.find(spritesheet_idx);
  if (ss_it != spritesheets.end())
  {
    ss = ss_it->second;
  }

  return ss;
}

void SDLDisplay::set_palette_id(const string& new_palette_id)
{
  cur_palette_id = new_palette_id;
}

void SDLDisplay::set_palette(const string& new_palette_id)
{
  auto p_it = palettes.find(new_palette_id);

  if (p_it != palettes.end())
  {
    set_palette_id(new_palette_id);

    auto colourset = p_it->second.second;
    initialize_colours(colourset);

    // Reset the colours on the dimensions
    sdld.set_fg_colour(get_colour(static_cast<int>(Colour::COLOUR_BLACK)));
    sdld.set_bg_colour(get_colour(static_cast<int>(Colour::COLOUR_BLACK)));
  }
}

string SDLDisplay::get_palette_id() const
{
  return cur_palette_id;
}

pair<bool, pair<string, string>> SDLDisplay::switch_colour_palette(const std::string& palette_id)
{
  pair<bool, pair<string, string>> palette;
  palette.first = false;

  string pid = palette_id;
  if (pid.empty())
  {
    pid = this->cur_palette_id;
  }

  auto p_it = palettes.find(pid);
  auto p_it_new = palettes.end();

  if (p_it != palettes.end())
  {
    p_it_new = std::next(p_it);
  }

  if (p_it_new == palettes.end())
  {
    p_it_new = palettes.begin();
  }

  palette.first = true;
  palette.second.first = p_it_new->first;
  palette.second.second = p_it_new->second.first;

  cur_palette_id = p_it_new->first;
  initialize_colours(p_it_new->second.second);

  return palette;
}


Coordinate SDLDisplay::get_spritesheet_coordinate(const SpritesheetLocation& ssl) const
{
  Coordinate coords = ssl.get_coordinate();

  if (ssl.uses_reference_id())
  {
    auto sr_it = spritesheet_references.find(ssl.get_index());

    if (sr_it != spritesheet_references.end())
    {
      auto sr_map = sr_it->second;
      auto srm_it = sr_map.find(ssl.get_reference_id());

      if (srm_it != sr_map.end())
      {
        coords = srm_it->second;
      }
    }
  }

  return coords;
}

bool SDLDisplay::serialize(std::ostream& stream) const
{
  Display::serialize(stream);

  // Window, raw screen textures, the font spritesheet, the renderer,
  // palettes will all be set up outside of this function.  They're 
  // not serialized.  Ignore them.

  sdld.serialize(stream);
  Serialize::write_string(stream, cur_palette_id);

  Serialize::write_size_t(stream, palettes.size());
  for (const auto& p_details : palettes)
  {
    Serialize::write_string(stream, p_details.first);
    Serialize::write_string(stream, p_details.second.first);

    vector<SDL_Colour> palette_colours = p_details.second.second;
    Serialize::write_size_t(stream, palette_colours.size());

    for (const auto& pc : palette_colours)
    {
      Serialize::write_uint(stream, pc.r);
      Serialize::write_uint(stream, pc.g);
      Serialize::write_uint(stream, pc.b);
      Serialize::write_uint(stream, pc.a);
    }
  }

  return true;
}

bool SDLDisplay::deserialize(std::istream& stream)
{
  Display::deserialize(stream);

  // Window, raw screen textures, the font spritesheet, and renderer will 
  // all be set up outside of this function. They're not serialized.  
  // Ignore them.

  sdld.deserialize(stream);
  Serialize::read_string(stream, cur_palette_id);

  size_t num_palettes = 0;
  Serialize::read_size_t(stream, num_palettes);

  for (size_t i = 0; i < num_palettes; i++)
  {
    string palette_id;
    Serialize::read_string(stream, palette_id);

    string palette_name_sid;
    Serialize::read_string(stream, palette_name_sid);

    size_t palette_size = 0;
    Serialize::read_size_t(stream, palette_size);

    vector<SDL_Colour> colours;
    for (size_t j = 0; j < palette_size; j++)
    {
      uint r = 0;
      uint g = 0;
      uint b = 0;
      uint a = 0;

      Serialize::read_uint(stream, r);
      Serialize::read_uint(stream, g);
      Serialize::read_uint(stream, b);
      Serialize::read_uint(stream, a);

      SDL_Colour c = {static_cast<Uint8>(r), static_cast<Uint8>(g), static_cast<Uint8>(b), static_cast<Uint8>(a)};
      colours.push_back(c);
    }

    palettes.insert(make_pair(palette_id, make_pair(palette_name_sid, colours)));
  }

  // After reading palettes, update the palette based on the currently selected
  // ID.
  auto p_it = palettes.find(cur_palette_id);

  if (p_it != palettes.end())
  {
    auto palette = p_it->second.second;
    initialize_colours(palette);
  }

  return true;
}

Display* SDLDisplay::clone()
{
  return new SDLDisplay(*this);
}

bool SDLDisplay::load_spritesheet_from_file(const string& path, SDL_Renderer* renderer)
{
  auto ss_it = spritesheets.find("");

  // If it already exists, destroy it.
  if (ss_it != spritesheets.end())
  {
    SDL_DestroyTexture(ss_it->second);
    spritesheets.erase(ss_it);
  }

  if (renderer == nullptr)
  {
    return false;
  }

  SDL_Texture* new_texture = load_texture(path, renderer);

  spritesheets[""] = new_texture;
  return new_texture != nullptr;
}

SDL_Texture* SDLDisplay::load_texture(const string& path, SDL_Renderer* renderer)
{
  ostringstream ss;
  SDL_Texture* new_texture = NULL;

  // Load image from path
  SDL_Surface* surface = IMG_Load(path.c_str());
  if (surface == NULL)
  {
    ss << "Unable to load SDL surface " << path << " - error: " << IMG_GetError();
    Log::instance().error(ss.str());
  }
  else
  {
    //Color key image
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));

    //Create texture from surface pixels
    new_texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (new_texture == NULL)
    {
      ss << "Unable to create texture from " << path << " - error: " << SDL_GetError();
      Log::instance().error(ss.str());
    }

    // Free up the old surface, which we no longer need.
    SDL_FreeSurface(surface);
  }

  return new_texture;
}

void SDLDisplay::free_spritesheets()
{
  for (auto& texture_pair : spritesheets)
  {
    SDL_Texture* texture = texture_pair.second;
    SDL_DestroyTexture(texture);
  }
}

void SDLDisplay::free_screens()
{
  for (SDL_Texture* t : screens)
  {
    SDL_DestroyTexture(t);
  }
}

void SDLDisplay::redraw_cursor(const DisplayMap& current_map, const CursorSettings& cs, const uint map_rows)
{
  if (!screens.empty() && !screen_cursors.empty())
  {
    if (get_cursor_mode(cs))
    {
      Coordinate cursor_coord = current_map.get_cursor_coordinate();
      SDLRender render(sdld);
      SDL_Colour cursor_colour = get_colour(Colour::COLOUR_WHITE);
      int map_row = cursor_coord.first + DisplayConstants::MAP_START_ROW;
      int map_col = cursor_coord.second + DisplayConstants::MAP_START_COL;

      // Draw the solid white cursor at the bottom of the current glyph
      SDL_Rect dst_rect;
      dst_rect.y = (map_row * sdld.get_glyph_height()) + static_cast<int>((sdld.get_glyph_height() * 0.8));
      dst_rect.x = map_col * sdld.get_glyph_width(); 
      dst_rect.w = sdld.get_glyph_width();
      dst_rect.h = static_cast<int>(sdld.get_glyph_height() * 0.2);

      render.fill_area(renderer, screens.back(), &dst_rect, cursor_colour);
    }
  }
}

ClassIdentifier SDLDisplay::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SDL_DISPLAY;
}

#ifdef UNIT_TESTS
#include "unit_tests/SDLDisplay_test.cpp"
#endif
