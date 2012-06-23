#pragma once
#include <map>
#include "ITimeObserver.hpp"

// The subject in the subject/observer pattern.
class WorldTimeKeeper
{
  public:
    WorldTimeKeeper();
    
    void register_observer(ITimeObserverPtr new_observer);
    void deregister_observer(ITimeObserverPtr old_observer);
    void reset();

    void tick(const double seconds);

  protected:
    void notify_all(const int minutes_passed);
    
    double seconds_counter;
    
    std::map<std::string, ITimeObserverPtr> observers;
};
