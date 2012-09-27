#pragma once
#include <boost/serialization/base_object.hpp>
#include "ICreatureRegeneration.hpp"

namespace boost
{
  namespace serialization
  {
    class access;
  }
}

class CreaturePietyRegeneration : public ICreatureRegeneration
{
  public:
    void tick(CreaturePtr creature, const ulonglong minutes_this_tick, const ulonglong total_minutes_elapsed);
    
  protected:
    int regenerate_piety(const int piety, const int piety_regen_bonus, const ulonglong minutes_elapsed, const bool crowned);
    int degenerate_piety(const int piety, const int piety_regen_bonus, const ulonglong minutes_elapsed);
    
    static int MINUTES_PER_POINT_OF_PIETY;
    
  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<ICreatureRegeneration>(*this);
      ar & MINUTES_PER_POINT_OF_PIETY;
    }
};
