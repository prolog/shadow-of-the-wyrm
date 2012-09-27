#pragma once
#include <boost/shared_ptr.hpp>
#include "common.hpp"
#include "Creature.hpp"

namespace boost
{
  namespace serialization
  {
    class access;
  }
}

class ICreatureRegeneration
{
  public:
    virtual ~ICreatureRegeneration() {};

    virtual void tick(CreaturePtr creature, const ulonglong minutes_this_tick, const ulonglong total_minutes_elapsed) = 0;
    
  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
    }
};

typedef boost::shared_ptr<ICreatureRegeneration> ICreatureRegenerationPtr;
