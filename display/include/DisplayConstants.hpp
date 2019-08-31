#pragma once
#include <string>

class DisplayIdentifier
{
  public:
    static const std::string DISPLAY_IDENTIFIER_CURSES;
    static const std::string DISPLAY_IDENTIFIER_SDL;

  protected:
    DisplayIdentifier();
};

enum struct CursorSettings
{
  CURSOR_SETTINGS_USE_DEFAULT = 0,
  CURSOR_SETTINGS_SHOW_CURSOR = 1
};

class DisplayConstants
{
  public:
    static const int OPTION_SPACING;
    static const int ROWS_FOR_MESSAGE_BUFFER_AND_SYNOPSIS;
};
