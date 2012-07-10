#pragma once
#include <map>
#include "ITimeObserver.hpp"

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
};
