#pragma once
#include "HPRegenerationCalculator.hpp"
#include "ITimeObserver.hpp"

class HPRegenerationTimeObserver : public ITimeObserver
{
  public:
    HPRegenerationTimeObserver();
    
    void notify(const ulonglong minutes_elapsed);
    
  protected:
    HPRegenerationCalculator hp_regen_calc;
};
