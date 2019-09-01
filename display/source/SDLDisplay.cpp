#include <boost/algorithm/string.hpp>
#include "Conversion.hpp"
#include "SDLKeyboardController.hpp"
#include "SDLDisplay.hpp"
#include "Game.hpp"
#include "Log.hpp"
#include "MapDisplayArea.hpp"
#include "Setting.hpp"
#include "TextKeys.hpp"

using namespace std;

// JCD TODO: x out of window

const int SDLDisplay::SCREEN_ROWS = 25;
const int SDLDisplay::SCREEN_COLS = 80;

SDLDisplay::SDLDisplay()
{
  window = NULL;
  renderer = NULL;
  tile_width = 0;
  tile_height = 0;
  screen_width = 0;
  screen_height = 0;
}

SDLDisplay::~SDLDisplay()
{
}

bool SDLDisplay::create()
{
  bool init = true;

  read_dimensions_from_settings();
  init = create_window_and_renderer();

  if (init)
  {
    read_font_into_texture();
  }

  return init;
}

void SDLDisplay::tear_down()
{
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

void SDLDisplay::read_dimensions_from_settings()
{
  string tile_size = get_property(Setting::DISPLAY_TILE_SIZE);
  vector<string> tile_spl;

  // The dimensions are in HxW format, eg, 8x8, 8x16, ...
  boost::split(tile_spl, tile_size, boost::is_any_of("x"));

  if (tile_spl.size() >= 2)
  {
    tile_width = String::to_int(tile_spl[0]);
    tile_height = String::to_int(tile_spl[1]);

    screen_width = SCREEN_COLS * tile_width;
    screen_height = SCREEN_ROWS * tile_height;
  }

  string tile_glyphs_per_line = get_property(Setting::DISPLAY_TILE_GLYPHS_PER_LINE);
  glyphs_per_line = String::to_int(tile_glyphs_per_line);
}

void SDLDisplay::read_font_into_texture()
{
  string font_path = get_property(Setting::DISPLAY_FONT);
  if (!font_spritesheet.load_from_file(font_path, renderer))
  {
    ostringstream ss;
    ss << "Could not read font from path: " << font_path;
    Log::instance().error(ss.str());
  }
}

bool SDLDisplay::create_window_and_renderer()
{
  bool wr_created = true;
  ostringstream ss;

  string window_title = StringTable::get(TextKeys::SW_TITLE);
  window = SDL_CreateWindow(window_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
  if (window == NULL)
  {
    ss << "Window could not be created! SDL Error: " << SDL_GetError();
    Log::instance().error(ss.str());

    wr_created = false;
  }
  else
  {
    //Create vsynced renderer for window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
      ss << "Renderer could not be created! SDL Error: %s\n" << SDL_GetError();
      Log::instance().error(ss.str());

      wr_created = false;
    }
  }

  return wr_created;
}

unsigned int SDLDisplay::get_width() const
{
  return 0;
}

unsigned int SDLDisplay::get_height() const
{
  return 0;
}

void SDLDisplay::clear_messages()
{
}

void SDLDisplay::clear_display()
{
}

void SDLDisplay::add_alert(const string& message, const bool prompt_for_input)
{
}

void SDLDisplay::add_message(const string& message, const bool reset_cursor)
{
}

void SDLDisplay::add_message(const string& message, const Colour colour, const bool clear_prior_to_adding_message)
{
}

string SDLDisplay::add_message_with_prompt(const string& message, const Colour colour, const bool clear_prior)
{
  string prompt;
  return prompt;
}

void SDLDisplay::halt_messages()
{
}

void SDLDisplay::draw(const DisplayMap& dm, const CursorSettings cs)
{
}

void SDLDisplay::redraw()
{
}

void SDLDisplay::draw_update_map(const DisplayMap& update_map, const CursorSettings cs)
{
}

void SDLDisplay::draw_tile(const uint y, const uint x, const DisplayTile& dt)
{
}

AnimationFactoryPtr SDLDisplay::create_animation_factory() const
{
  AnimationFactoryPtr af;
  return af;
}

void SDLDisplay::draw_animation(const Animation& animation)
{
}

void SDLDisplay::display(const DisplayStatistics& player_stats)
{
}

MapDisplayArea SDLDisplay::get_map_display_area()
{
  MapDisplayArea mda;

  return mda;
}

void SDLDisplay::confirm(const string& confirmation_message)
{
}

void SDLDisplay::clear_screen()
{
}

void SDLDisplay::refresh_and_clear_window()
{
}

void SDLDisplay::setup_new_screen()
{
}

void SDLDisplay::refresh_current_window()
{
  SDL_RenderPresent(renderer);
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
  string val;
  return val;
}

void SDLDisplay::display_header(const string& header_text, const int row)
{
}

void SDLDisplay::display_text_component(SDL_Window* window, int* row, int* col, TextComponentPtr tc, const uint line_incr)
{
  int cur_col = *col;

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
        display_text(window, *row, *col, c);
        cur_col += 1;
      }
    }

    *row += line_incr;
  }
}

void SDLDisplay::display_text(SDL_Window* window, int row, int col, const char c)
{
  SDL_Rect font_clip;

  // Look up the letter
  std::pair<int, int> ss_coords = get_glyph_location_from_spritesheet(c);

  // Set the proper coords
  font_clip.y = ss_coords.first * tile_height;
  font_clip.x = ss_coords.second * tile_width;
  font_clip.w = tile_width;
  font_clip.h = tile_height;

  int render_x = col * tile_width;
  int render_y = row * tile_height;

  font_spritesheet.render(render_y, render_x, renderer, &font_clip);
}

std::pair<int, int> SDLDisplay::get_glyph_location_from_spritesheet(char x)
{
  return {x / glyphs_per_line, x % glyphs_per_line};
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

      int ocol = *col;

      string display_option_s = display_option.str();
//      boost::replace_all(display_option_s, "%", "%%");

//      mvwprintw(window, *row, ocol, display_option_s.c_str());

//      getyx(window, *row, ocol);

      TextComponentPtr text = current_option.get_description();

      display_text_component(window, row, &ocol, text, DisplayConstants::OPTION_SPACING);
//      disable_colour(static_cast<int>(option_colour), window);

      options_added++;
      temp_row++;
    }
  }

  // No need to update *row
  // It will have been taken care of when displaying the TextComponent.
}

Display* SDLDisplay::clone()
{
  return new SDLDisplay(*this);
}

ClassIdentifier SDLDisplay::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SDL_DISPLAY;
}

#ifdef UNIT_TESTS
#include "unit_tests/SDLDisplay_test.cpp"
#endif
