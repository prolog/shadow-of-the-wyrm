#pragma once
#include "ICreatureRegeneration.hpp"

class CreatureStatisticsModifiers : public ICreatureRegeneration
{
  public:
    void tick(CreaturePtr creature, const ulonglong minutes_this_tick, const ulonglong total_minutes_elapsed) override;
};
