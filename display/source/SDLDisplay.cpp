#include "SDLDisplay.hpp"
#include "Log.hpp"
#include "MapDisplayArea.hpp"

using namespace std;

SDLDisplay::SDLDisplay()
{
  window = NULL;
  surface = NULL;
}

SDLDisplay::~SDLDisplay()
{
}

bool SDLDisplay::create()
{
  bool init = false;

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    Log::instance().error("Could not initialize SDL!");
  }
  else
  {
    // The window and surface we'll be rendering
    // ...
    
    init = true;
  }

  return init;
}

void SDLDisplay::tear_down()
{
  SDL_Quit();
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
