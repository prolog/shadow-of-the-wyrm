#pragma once
#include "HPRegenerationCalculator.hpp"
#include "ITimeObserver.hpp"

class CreatureTimeObserver : public ITimeObserver
{
  public:
    CreatureTimeObserver();
    
    void notify(const ulonglong minutes_elapsed);
    
  protected:
    HPRegenerationCalculator hp_regen_calc;
};
