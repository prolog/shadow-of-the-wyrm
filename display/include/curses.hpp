#pragma once
#ifdef _MSC_VER
#include <curses.h>
#else
  #ifndef NCURSES_OPAQUE
    constexpr auto NCURSES_OPAQUE = 0;
  #endif
#include <ncurses.h>
#endif

// These aren't going to make things magically work in Linux/ncurses,
// but it will at least define the same constants so the SDL code
// can use the common constants.
#ifndef CTL_LEFT
#define CTL_LEFT 0x1bb
#endif

#ifndef CTL_RIGHT
#define CTL_RIGHT 0x1bc
#endif
