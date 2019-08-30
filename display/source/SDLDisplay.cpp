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
}

void SDLDisplay::read_font_into_texture()
{
  string font = get_property(Setting::DISPLAY_FONT);

  // ...
}

bool SDLDisplay::create_window_and_renderer()
{
  bool wr_created = true;

  string window_title = StringTable::get(TextKeys::SW_TITLE);
  window = SDL_CreateWindow(window_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
  if (window == NULL)
  {
    cout << "Window could not be created! SDL Error: " << SDL_GetError();
    wr_created = false;
  }
  else
  {
    //Create vsynced renderer for window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
      cout << "Renderer could not be created! SDL Error: %s\n" << SDL_GetError();
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

string SDLDisplay::display_screen(const Screen& current_screen)
{
  string val;

  // TODO: Actually do stuff with the Screen components.
  // Call the menu wrapper to ensure the returned value is within the range.
  val = prompt_processor.get_prompt(window);

  return val;
}

void SDLDisplay::confirm(const string& confirmation_message)
{
}

void SDLDisplay::clear_screen()
{
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
