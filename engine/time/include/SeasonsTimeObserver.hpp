#pragma once
#include "ITimeObserver.hpp"

namespace boost
{
  namespace serialization
  {
    class access;
  }
}

class SeasonsTimeObserver : public ITimeObserver
{
  public:
    SeasonsTimeObserver();
    
    void notify(const ulonglong minutes_elapsed);
    
  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<ITimeObserver>(*this);
    }
};
