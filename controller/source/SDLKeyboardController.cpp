#ifdef _MSC_VER
#include <curses.h>
#else
#include <ncurses.h>
#endif

#include <map>
#include <sstream>
#include "Log.hpp"
#include "SDLKeyboardController.hpp"
#include "SDL.h"

using namespace std;

bool SDLKeyboardController::SDL_initialized = false;

SDLKeyboardController::SDLKeyboardController()
{
  if (!SDL_initialized)
  {
    // Temporary code, will be moved elsewhere once the display is working.
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
      ostringstream ss;
      ss << "Unable to initialize SDL: " << SDL_GetError();
      Log::instance().error(ss.str());

      SDL_initialized = true;
    }
  }
}

SDLKeyboardController::~SDLKeyboardController()
{
  SDL_Quit();
}

string SDLKeyboardController::get_line()
{
/* CursesPromptProcessor ncpp;
  return ncpp.get_user_string(stdscr); */

  // JCD FIXME
  // This *works*, but doesn't.  This needs to ultimately also display the
  // result on the screen, not just read it silently.
  SDL_Event event;
  std::ostringstream ss;
  SDL_StartTextInput();

  SDL_PollEvent(&event);

  while (event.key.keysym.sym != SDLK_RETURN)
  {
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_TEXTINPUT)
      {
        ss << event.text.text;
      }
    }
  }

  return ss.str();
}

int SDLKeyboardController::read_char_as_int()
{
  int return_val = 0;
  bool done = false;

  SDL_Event event;

  while (!done)
  {
    SDL_PollEvent(&event);

    if (event.type == SDL_KEYDOWN)
    {
      SDL_Keycode key = event.key.keysym.sym;

      // SotW allows letters, numbers, function keys, ESC.
      //
      // The list of mappings in KeyboardCommandMap should be considered
      // authoritative.
      if ((key >= SDLK_F1 && event.key.keysym.sym <= SDLK_F12) ||
          (key >= SDLK_a && key <= SDLK_z) ||
          (key >= SDLK_0 && key <= SDLK_9) ||
          (key == SDLK_ESCAPE))
      {
        done = true;
        return_val = event.key.keysym.sym;
      }
    }
  }

  return return_val;
}

pair<bool, int> SDLKeyboardController::read_char_as_int_nb()
{
  pair<bool, int> character = make_pair(false, -1);

/*  DisplayPtr display = Game::instance().get_display();
  std::shared_ptr<CursesDisplay> cdisplay = std::dynamic_pointer_cast<CursesDisplay>(display);

  WINDOW* cur_win = nullptr;

  if (cdisplay && ((cur_win = cdisplay->get_current_screen()) != nullptr))
  {
    // Turn on nodelay to try to get a character without blocking
    nodelay(stdscr, true);

    int win_char = wgetch(cur_win);
    
    if (win_char != ERR)
    {
      character.first = true;
      character.second = win_char;
    }

    // Once we're done, turn off nodelay so that we're back to
    // polling for input.
    nodelay(stdscr, false);
  }
  */
  return character;
}

// Convert SDL keys to the curses equivalent - the curses values are 
// considered the underlying values in SotW.
int SDLKeyboardController::translate_kb_input(const int input)
{
  int return_val = input;
  map<int, int> map_vals = { {SDLK_F1, KEY_F(1)},
                            {SDLK_F2, KEY_F(2)},
                            {SDLK_F3, KEY_F(3)},
                            {SDLK_F4, KEY_F(4)},
                            {SDLK_F5, KEY_F(5)},
                            {SDLK_F6, KEY_F(6)},
                            {SDLK_F7, KEY_F(7)},
                            {SDLK_F8, KEY_F(8)},
                            {SDLK_F9, KEY_F(9)},
                            {SDLK_F10, KEY_F(10)},
                            {SDLK_F11, KEY_F(11)},
                            {SDLK_F12, KEY_F(12)},
                            {SDLK_UP, KEY_UP},
                            {SDLK_DOWN, KEY_DOWN},
                            {SDLK_LEFT, KEY_LEFT},
                            {SDLK_RIGHT, KEY_RIGHT},
                            {SDLK_LALT, 27 /* curses left alt */}};
  
  auto k_it = map_vals.find(input);

  if (k_it != map_vals.end())
  {
    return_val = k_it->second;
  }

  return return_val;
}

Controller* SDLKeyboardController::clone()
{
  return new SDLKeyboardController(*this);
}

ClassIdentifier SDLKeyboardController::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SDL_KEYBOARD_CONTROLLER;
}
