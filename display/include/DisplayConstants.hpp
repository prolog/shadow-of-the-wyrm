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
    static const unsigned int MAP_START_ROW;
    static const unsigned int MAP_START_COL;
    static const unsigned int MESSAGE_BUFFER_END_ROW;
    static const unsigned int MESSAGE_BUFFER_ROWS;
};
