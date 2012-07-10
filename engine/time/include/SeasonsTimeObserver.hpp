#pragma once
#include "ITimeObserver.hpp"

class SeasonsTimeObserver : public ITimeObserver
{
  public:
    SeasonsTimeObserver();
    
    void notify(const ulonglong minutes_elapsed);
    
  protected:
};
