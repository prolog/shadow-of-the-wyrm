#pragma once
#include <boost/serialization/base_object.hpp>
#include "HPRegenerationCalculator.hpp"
#include "ICreatureRegeneration.hpp"

namespace boost
{
  namespace serialization
  {
    class access;
  }
}

class CreatureHPRegeneration : public ICreatureRegeneration
{
  public:
    void tick(CreaturePtr creature, const ulonglong minutes_this_tick, const ulonglong total_minutes_elapsed);
    
  protected:
    HPRegenerationCalculator hp_regen_calc;
    
  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<ICreatureRegeneration>(*this);
      ar & hp_regen_calc;
    }
};
