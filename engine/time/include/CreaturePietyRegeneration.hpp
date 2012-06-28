#pragma once
#include "ICreatureRegeneration.hpp"

class CreaturePietyRegeneration : public ICreatureRegeneration
{
  public:
    void regen(CreaturePtr creature, const ulonglong minutes_elapsed);
    
  protected:
    int regenerate_piety(const int piety, const int piety_regen_bonus, const ulonglong minutes_elapsed, const bool crowned);
    int degenerate_piety(const int piety, const int piety_regen_bonus, const ulonglong minutes_elapsed);
    
    static const int MINUTES_PER_POINT_OF_PIETY;
};
