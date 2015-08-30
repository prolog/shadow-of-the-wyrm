#pragma once
#include <memory>
#include "common.hpp"
#include "Creature.hpp"

class ICreatureRegeneration
{
  public:
    virtual ~ICreatureRegeneration() {};

    virtual void tick(CreaturePtr creature, TilePtr tile, const ulonglong minutes_this_tick, const ulonglong total_minutes_elapsed) = 0;
};

using ICreatureRegenerationPtr = std::shared_ptr<ICreatureRegeneration>;
