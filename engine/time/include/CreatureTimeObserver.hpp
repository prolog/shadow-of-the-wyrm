#pragma once
#include <vector>
#include <boost/serialization/base_object.hpp>
#include "ICreatureRegeneration.hpp"
#include "ITimeObserver.hpp"

namespace boost
{
  namespace serialization
  {
    class access;
  }
}

class CreatureTimeObserver : public ITimeObserver
{
  public:
    CreatureTimeObserver();
    
    void notify(const ulonglong minutes_elapsed);
    
  protected:
    void initialize_regeneration_helpers();
  
    std::vector<ICreatureRegenerationPtr> regen;
    
  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<ITimeObserver>(*this);
      ar & regen;
    }
};
