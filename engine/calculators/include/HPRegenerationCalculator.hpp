#pragma once
#include "common.hpp"
#include "Creature.hpp"

namespace boost
{
  namespace serialization
  {
    class access;
  }
}

class HPRegenerationCalculator
{
  public:
    uint calculate_minutes_per_hit_point(CreaturePtr creature);
    
  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
    }
};
