#pragma once
#include <string>

class DisplayIdentifier
{
  public:
    static const std::string DISPLAY_IDENTIFIER_CURSES;

  protected:
    DisplayIdentifier();
};

enum struct CursorSettings
{
  CURSOR_SETTINGS_USE_DEFAULT = 0,
  CURSOR_SETTINGS_SHOW_CURSOR = 1
};
