#pragma once
#include <boost/serialization/base_object.hpp>
#include "Creature.hpp"
#include "ICreatureRegeneration.hpp"

namespace boost
{
  namespace serialization
  {
    class access;
  }
}

// Checks things like swimming, mountain climbing, etc., that are based off
// the movement accumulation mechanism and player skills.
class MovementAccumulationChecker : public ICreatureRegeneration
{
  public:
    void tick(CreaturePtr creature, const ulonglong minutes_this_tick, const ulonglong minutes_elapsed);

  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<ICreatureRegeneration>(*this);
    }
};
