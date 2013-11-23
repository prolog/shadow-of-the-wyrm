#pragma once
#include <memory>
#include "common.hpp"
#include "Creature.hpp"

class ICreatureRegeneration
{
  public:
    virtual ~ICreatureRegeneration() {};

    virtual void tick(CreaturePtr creature, const ulonglong minutes_this_tick, const ulonglong total_minutes_elapsed) = 0;
};

typedef std::shared_ptr<ICreatureRegeneration> ICreatureRegenerationPtr;
