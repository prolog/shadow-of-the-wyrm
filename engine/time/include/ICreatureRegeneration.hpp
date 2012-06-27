#pragma once
#include <boost/shared_ptr.hpp>
#include "common.hpp"
#include "Creature.hpp"

class ICreatureRegeneration
{
  public:
    virtual void regen(CreaturePtr creature, const ulonglong minutes_elapsed) = 0;
};

typedef boost::shared_ptr<ICreatureRegeneration> ICreatureRegenerationPtr;
