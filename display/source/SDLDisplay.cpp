#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include "SDL_image.h"
#include "Conversion.hpp"
#include "SDLKeyboardController.hpp"
#include "SDLDisplay.hpp"
#include "SDLRender.hpp"
#include "Game.hpp"
#include "Log.hpp"
#include "MapDisplayArea.hpp"
#include "Screen.hpp"
#include "Setting.hpp"
#include "TextKeys.hpp"
#include "TextMessages.hpp"

using namespace std;

// JCD TODO: x out of window

const int SDLDisplay::SCREEN_ROWS = 25;
const int SDLDisplay::SCREEN_COLS = 80;
const int SDLDisplay::NUM_SDL_BASE_COLOURS = 16;
SDLDisplay::SDLDisplay()
{
  window = nullptr;
  renderer = nullptr;
  font_spritesheet = nullptr;

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

  init = read_dimensions_from_settings();
  init = init && create_window_and_renderer();
  init = init && read_font_into_texture();
  
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
  free_font_spritesheet();

  for (SDL_Texture* t : screens)
  {
    SDL_DestroyTexture(t);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

void SDLDisplay::initialize_colours()
{
  colours = { /* black                */ {0, {0,0,0,255} }, // jcd fixme these are bright
              /* red                  */ {1, {139,0,0,255} },
              /* green                */ {2, {0,139,0,255} },
              /* yellow               */ {3, {139,139,0,255} },
              /* blue                 */ {4, {0,0,139,255} },
              /* magenta              */ {5, {139,0,139,255} },
              /* cyan                 */ {6, {0,139,139,255} },
              /* white                */ {7, {200,200,200,255} },
              /* bold black/dark gray */ {8, {59,59,59,255} },
              /* bold red             */ {9, {255,0,0,255} },
              /* bold green           */ {10, {0,255,0,255} },
              /* bold yellow          */ {11, {255,255,0,255} },
              /* bold blue            */ {12, {0,0,255,255} },
              /* bold magenta         */ {13, {255,0,255,255} },
              /* bold cyan            */ {14, {0,255,255,255} },
              /* bold white           */ {15, {255,255,255,255} }
  };
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
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
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
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
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
  clear_messages();
  add_message(message, Colour::COLOUR_BOLD_RED, false);
  refresh_current_window();

  if (prompt_for_input)
  {
    prompt_processor.get_prompt(window);
    clear_messages();
  }
}

void SDLDisplay::add_message(const string& to_add_message, const Colour colour, const bool clear_prior_to_adding_message)
{
  if (!screens.empty() && !screen_cursors.empty())
  {
    SDL_Texture* screen = screens.at(0);
    string message = to_add_message;

    SDLCursorLocation& sdlc = screen_cursors.back();
    pair<int, int> orig_curs_loc = sdlc.get_yx();

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
          render.render_text(sdlc, renderer, font_spritesheet, screen, cur_y, cur_x, "...", sdld.get_fg_colour(), sdld.get_bg_colour());
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

      render.render_text(sdlc, renderer, font_spritesheet, screen, cur_y, cur_x, current_token, sdld.get_fg_colour(), sdld.get_bg_colour());
    }

    disable_colour(colour);
  }

  refresh_current_window();
}

string SDLDisplay::add_message_with_prompt(const string& message, const Colour colour, const bool clear_prior)
{
  string prompt_result;

  if (!screens.empty() && !screen_cursors.empty())
  {
    SDLRenderPtr render = std::make_shared<SDLRender>(sdld);

    add_message(message, colour, clear_prior);
    prompt_result = prompt_processor.get_user_string(sdld, screen_cursors.back(), render, renderer, font_spritesheet, screens.back(), true /* allow arbitrary non-alphanumeric characters */);
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
  // ...
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
    int col = current_tile.get_colour();
    Colour colour = static_cast<Colour>(col);

    enable_colour(colour);
    render.render_text(screen_cursors.back(), renderer, font_spritesheet, screens.back(), terminal_row, terminal_col, current_tile.get_symbol(), sdld.get_fg_colour(), sdld.get_bg_colour());
    disable_colour(colour);
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
  }
}

void SDLDisplay::refresh_and_clear_window()
{
  if (!screens.empty() && !screen_cursors.empty())
  {
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderClear(renderer);
    SDL_SetRenderTarget(renderer, screens.back());
    screen_cursors.back().reset();
  }
}

void SDLDisplay::setup_new_screen()
{
  SDL_RenderClear(renderer);

  SDL_Texture* screen = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, sdld.get_screen_width(), sdld.get_screen_height());
  screens.push_back(screen);

  SDLCursorLocation cursor_loc(get_max_rows(), get_max_cols());
  screen_cursors.push_back(cursor_loc);

  SDL_SetRenderTarget(renderer, screen);
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

    SDLRenderPtr text_renderer = std::make_shared<SDLRender>(sdld);
    PromptPtr prompt = screen.get_prompt();
    prompt_processor.show_prompt(sdld, cursor_loc, text_renderer, renderer, font_spritesheet, current_screen, prompt, row, col, get_max_rows(), get_max_cols());
    refresh_current_window();

    prompt_val = prompt_processor.get_prompt(sdld, cursor_loc, text_renderer, renderer, font_spritesheet, current_screen, menu_wrapper, prompt);
  }

  return prompt_val;
}

void SDLDisplay::display_header(const string& header_text, const int row)
{
  if (!screens.empty() && !screen_cursors.empty())
  {
    SDLRender render(sdld);

    string full_header = TextMessages::get_full_header_text(header_text, sdld.get_screen_cols());
    render.render_text(screen_cursors.back(), renderer, font_spritesheet, screens.back(), row, 0, full_header, sdld.get_fg_colour(), sdld.get_bg_colour());
  }
}

void SDLDisplay::display_text_component(SDL_Window* window, int* row, int* col, TextComponentPtr tc, const uint line_incr)
{
  if (!screens.empty() && !screen_cursors.empty())
  {
    SDLRender text_renderer(sdld);
    SDL_Texture* texture = screens.back();

    if (tc != nullptr && row != nullptr && col != nullptr)
    {
      vector<pair<string, Colour>> current_text = tc->get_text();

      for (auto& text_line : current_text)
      {
        string cur_text = text_line.first;
        Colour colour = text_line.second;
        
        // Loop through the given string.  For each character, render it,
        // and increment the column.
        for (const char c : cur_text)
        {
          text_renderer.render_text(screen_cursors.back(), renderer, font_spritesheet, texture, *row, *col, c, sdld.get_fg_colour(), sdld.get_bg_colour());
          *col += 1;
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
    text_renderer.render_text(screen_cursors.back(), renderer, font_spritesheet, screens.back(), row, col, s, sdld.get_fg_colour(), sdld.get_bg_colour());
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

// When displaying a general screen, reset the colour to white.
string SDLDisplay::display_screen(const Screen& current_screen)
{
  enable_colour(Colour::COLOUR_WHITE);
  return Display::display_screen(current_screen);
}


bool SDLDisplay::serialize(std::ostream& stream) const
{
  Display::serialize(stream);

  // Window, raw screen textures, the font spritesheet, and renderer will 
  // all be set up outside of this function. They're not serialized.  
  // Ignore them.

  sdld.serialize(stream);

  return true;
}

bool SDLDisplay::deserialize(std::istream& stream)
{
  Display::deserialize(stream);

  // Window, raw screen textures, the font spritesheet, and renderer will 
  // all be set up outside of this function. They're not serialized.  
  // Ignore them.

  sdld.deserialize(stream);

  return true;
}

Display* SDLDisplay::clone()
{
  return new SDLDisplay(*this);
}

bool SDLDisplay::load_spritesheet_from_file(const string& path, SDL_Renderer* renderer)
{
  free_font_spritesheet();
  ostringstream ss;

  if (renderer == nullptr)
  {
    return false;
  }

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

  font_spritesheet = new_texture;
  return font_spritesheet != nullptr;
}

void SDLDisplay::free_font_spritesheet()
{
  if (font_spritesheet != nullptr)
  {
    SDL_DestroyTexture(font_spritesheet);
    font_spritesheet = nullptr;
  }
}

ClassIdentifier SDLDisplay::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SDL_DISPLAY;
}

#ifdef UNIT_TESTS
#include "unit_tests/SDLDisplay_test.cpp"
#endif
