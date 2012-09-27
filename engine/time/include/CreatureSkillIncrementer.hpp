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

class CreatureSkillIncrementer : public ICreatureRegeneration
{
  public:
    CreatureSkillIncrementer();
    CreatureSkillIncrementer(const uint new_minutes_interval);

    void tick(CreaturePtr creature, const ulonglong minutes_this_tick, const ulonglong total_minutes_elapsed);

  protected:
    int minutes_interval;
    
  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<ICreatureRegeneration>(*this);
      ar & minutes_interval;
    }
};
