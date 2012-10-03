#pragma once
#include <boost/shared_ptr.hpp>
#include "common.hpp"
#include "Creature.hpp"

class ICreatureRegeneration
{
  public:
    virtual ~ICreatureRegeneration() {};

    virtual void tick(CreaturePtr creature, const ulonglong minutes_this_tick, const ulonglong total_minutes_elapsed) = 0;
};

typedef boost::shared_ptr<ICreatureRegeneration> ICreatureRegenerationPtr;
