#pragma once
#include <map>
#include "ClassIdentifiers.hpp"
#include "ITimeObserver.hpp"

using TimeObserverSerializationMap = std::map<ClassIdentifier, ITimeObserverPtr>;

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

