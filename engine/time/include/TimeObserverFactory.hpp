#pragma once
#include <map>
#include "ClassIdentifiers.hpp"
#include "ITimeObserver.hpp"

typedef std::map<ClassIdentifier, ITimeObserverPtr> TimeObserverSerializationMap;

class TimeObserverFactory
{
  public:
    static ITimeObserverPtr create_time_observer(const ClassIdentifier ci);

  protected:
    TimeObserverFactory();
    ~TimeObserverFactory();

    static void initialize_time_observer_map();

    static TimeObserverSerializationMap time_observer_map;
};

