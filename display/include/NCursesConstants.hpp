#pragma once

// Once other platforms are supported, use appropriate ifdefs.
#define NC_BACKSPACE_KEY 8
#define NC_ENTER_KEY 10

class NCursesConstants
{
  public:
    static const unsigned int MAP_START_ROW;
    static const unsigned int MAP_START_COL;
    static const unsigned int MESSAGE_BUFFER_END_ROW;
    
  protected:
    NCursesConstants();
    ~NCursesConstants();
};
