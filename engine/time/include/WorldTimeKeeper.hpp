#pragma once
#include <map>
#include "ITimeObserver.hpp"

namespace boost
{
  namespace serialization
  {
    class access;
  }
}

// The subject in the subject/observer pattern.
class WorldTimeKeeper
{
  public:
    WorldTimeKeeper();
    
    void register_observer(const uint minutes_key, ITimeObserverPtr new_observer);
    void deregister_observer(const uint minutes_key, ITimeObserverPtr old_observer);
    void reset();

    void tick(const double seconds);
    
  protected:
    double seconds_counter;
    double total_seconds_counter;
    
    std::map<uint, std::map<std::string, ITimeObserverPtr> > observers;
    
  private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & seconds_counter & total_seconds_counter & observers;
    }
};
