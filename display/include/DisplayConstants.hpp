#pragma once
#include <string>

class DisplayIdentifier
{
  public:
    static const std::string DISPLAY_IDENTIFIER_CURSES;
    static const std::string DISPLAY_IDENTIFIER_SDL_TEXT;
    static const std::string DISPLAY_IDENTIFIER_SDL_TILES;

  protected:
    DisplayIdentifier();
};

enum struct CursorSettings
{
  CURSOR_SETTINGS_USE_DEFAULT = 0,
  CURSOR_SETTINGS_SHOW_CURSOR = 1
};
