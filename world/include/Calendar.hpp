#pragma once
#include "common.hpp"

class Calendar
{
  public:
    Calendar();
    
    void add_seconds(const uint seconds);

  protected:
    // Number of seconds since day 1 of month 1 of year 832.
    ulonglong seconds;
};
