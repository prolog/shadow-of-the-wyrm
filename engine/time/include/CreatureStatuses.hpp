#pragma once
#include "HPRegenerationCalculator.hpp"
#include "ICreatureRegeneration.hpp"

class CreatureStatuses : public ICreatureRegeneration
{
  public:
    void tick(CreaturePtr creature, const ulonglong minutes_this_tick, const ulonglong total_minutes_elapsed);
};
