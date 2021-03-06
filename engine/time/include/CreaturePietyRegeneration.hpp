#pragma once
#include "ICreatureRegeneration.hpp"

class CreaturePietyRegeneration : public ICreatureRegeneration
{
  public:
    void tick(CreaturePtr creature, TilePtr tile, const ulonglong minutes_this_tick, const ulonglong total_minutes_elapsed) override;

  protected:
    int regenerate_piety(const int piety, const int piety_regen_bonus, const ulonglong minutes_elapsed, const bool crowned);
    int degenerate_piety(const int piety, const int piety_regen_bonus, const ulonglong minutes_elapsed);
    
    static int MINUTES_PER_POINT_OF_PIETY;
};
