#pragma once

// Once other platforms are supported, use appropriate ifdefs.
#define NC_BACKSPACE_KEY 8
#define NC_ENTER_KEY 10

class CursesConstants
{
  public:
    static const unsigned int MAP_START_ROW;
    static const unsigned int MAP_START_COL;
    static const unsigned int MESSAGE_BUFFER_END_ROW;
    
  protected:
    CursesConstants();
    ~CursesConstants();
};

enum struct CursorMode
{
  CURSOR_MODE_MIN = 0,
  CURSOR_MODE_NO_CURSOR = 0,
  CURSOR_MODE_NORMAL_VISIBILITY = 1,
  CURSOR_MODE_HIGH_VISIBILITY = 2,
  CURSOR_MODE_MAX = 2
};

