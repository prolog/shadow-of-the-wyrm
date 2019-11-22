// Needed for KEY_F(n) constants
#ifdef _MSC_VER
#include <curses.h>
#else
#include <ncurses.h>
#endif

#include <map>
#include <sstream>
#include "CursesConstants.hpp"
#include "Game.hpp"
#include "Log.hpp"
#include "SDLKeyboardController.hpp"

#ifdef _MSC_VER
#include "SDL.h"
#else
#include "SDL2/SDL.h"
#endif

#include "SDL.hpp"

using namespace std;

unordered_map<int, int> SDLKeyboardController::keymap;

SDLKeyboardController::SDLKeyboardController()
{
  if (keymap.empty())
  {
    init_keymap();
  }
}

void SDLKeyboardController::init_keymap()
{
  keymap = { {SDLK_F1, KEY_F(1)},
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
             {SDLK_ESCAPE, 27},
             {SDLK_LALT, 27},
             {SDLK_BACKSPACE, NC_BACKSPACE_KEY},
             {SDLK_RETURN, '\r'}
  };
}

// Poll and probably ignore.  The one event we actually want to keep track
// of is SDL_QUIT, which should cause the game to gracefully exit.
void SDLKeyboardController::poll_event()
{
  SDL_Event event;
  SDL_PollEvent(&event);

  if (event.type == SDL_QUIT)
  {
    SDL sdl;
    sdl.tear_down();

    exit(0);
  }
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

      if (event.type == SDL_QUIT)
      {
        SDL sdl;
        sdl.tear_down();

        exit(0);
      }
    }
  }

  SDL_StopTextInput();
  return ss.str();
}

int SDLKeyboardController::read_char_as_int()
{
  int return_val = 0;
  bool done = false;

  SDL_Event event;
  SDL_StartTextInput();

  while (!done)
  {
    SDL_PollEvent(&event);
    int key = event.key.keysym.sym;

    if (event.type == SDL_TEXTINPUT)
    {
      // JCD FIXME I16n later? This is single-byte, won't work nicely with
      // e.g. Chinese characters.
      return_val = event.text.text[0];
      done = true;
    }
    // If we got a keydown event, check the keymap to see if it's allowed.
    else if (event.type == SDL_KEYDOWN)
    {
      if (keymap.find(key) != keymap.end())
      {
        return_val = event.key.keysym.sym;
        done = true;
      }
    }
    else if (event.type == SDL_QUIT)
    {
      SDL sdl;
      sdl.tear_down();

      exit(0);
    }
  }

  SDL_StopTextInput();
  return return_val;
}

pair<bool, int> SDLKeyboardController::read_char_as_int_nb()
{
  pair<bool, int> character = make_pair(false, -1);
  SDL_Event event;

  while (SDL_PollEvent(&event))
  {
    if (event.type == SDL_KEYDOWN)
    {
      character.first = true;
      character.second = event.key.keysym.sym;
      
      break;
    }
    else if (event.type == SDL_QUIT)
    {
      SDL sdl;
      sdl.tear_down();

      exit(0);
    }
  }

  return character;
}

// Convert SDL keys to the curses equivalent - the curses values are 
// considered the underlying values in SotW.
int SDLKeyboardController::translate_kb_input(const int input)
{
  int return_val = input;  
  auto k_it = keymap.find(input);

  if (k_it != keymap.end())
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
