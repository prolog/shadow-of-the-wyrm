#include "CursesKeyboardController.hpp"
#include "CursesPromptProcessor.hpp"
#include "Game.hpp"

using namespace std;

// Important: this currently only works on STDSCR!  If the general keyboard controller needs a particular window,
// extra code will be needed.
string CursesKeyboardController::get_line()
{
  CursesPromptProcessor ncpp;
  return ncpp.get_user_string(stdscr);
}

int CursesKeyboardController::get_char_as_int()
{
  Game& game = Game::instance();
  DisplayPtr display = game.get_display();

  // Hackery :(
  // But a curses display must always be paired with a curses
  // kb controller...
  std::shared_ptr<CursesDisplay> cdisplay = std::dynamic_pointer_cast<CursesDisplay>(display);

  int character;
  WINDOW* cur_win;

  if (cdisplay && ((cur_win = cdisplay->get_current_menu()) != NULL))
  {
    character = wgetch(cur_win);
  }
  else
  {
    character = getch();
  }

  return character;
}

Controller* CursesKeyboardController::clone()
{
  return new CursesKeyboardController(*this);
}

ClassIdentifier CursesKeyboardController::internal_class_identifier() const
{
  return CLASS_ID_CURSES_KEYBOARD_CONTROLLER;
}
