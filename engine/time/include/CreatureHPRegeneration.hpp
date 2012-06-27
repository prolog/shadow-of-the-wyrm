#pragma once
#include "HPRegenerationCalculator.hpp"
#include "ICreatureRegeneration.hpp"

class CreatureHPRegeneration : public ICreatureRegeneration
{
  public:
    void regen(CreaturePtr creature, const ulonglong minutes_elapsed);
    
  protected:
    HPRegenerationCalculator hp_regen_calc;
};
