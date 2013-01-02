#pragma once
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "DeathEventFunctions.hpp"

// Engine death functions return no value, and take three pointers:
// - To the attacking creature (may be null - damage is not always dealt
//   by a creature)
// - To the dead creature (should never be null)
// - To the current map 
typedef boost::function<void(boost::shared_ptr<Creature>, boost::shared_ptr<Creature>, boost::shared_ptr<Map>)> DeathEventFunction;
typedef std::map<std::string, DeathEventFunction> DeathEventFunctionMap;

class EventFunctions
{
  public:
    static DeathEventFunction get_death_event_function(const std::string& function_name);
     
  protected:
    static void initialize();
    static void initialize_death_functions();

    static DeathEventFunctionMap death_functions;

    EventFunctions();
    ~EventFunctions();
};

