#pragma once

// Once other platforms are supported, use appropriate ifdefs.
#define NC_BACKSPACE_KEY 8
#define NC_ALTERNATIVE_BACKSPACE_KEY 7
#define NC_ENTER_KEY 10
#define NC_ESCAPE_KEY 27

enum struct CursorMode
{
  CURSOR_MODE_MIN = 0,
  CURSOR_MODE_NO_CURSOR = 0,
  CURSOR_MODE_NORMAL_VISIBILITY = 1,
  CURSOR_MODE_HIGH_VISIBILITY = 2,
  CURSOR_MODE_MAX = 2
};

