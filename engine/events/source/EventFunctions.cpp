#include "EventFunctions.hpp"

using namespace std;

// The actual event functions
DeathEventFunctionMap EventFunctions::death_functions;

EventFunctions::EventFunctions()
{
}

EventFunctions::~EventFunctions()
{
}

DeathEventFunction EventFunctions::get_death_event_function(const string& death_function_name)
{
  // Initialize on first use.
  if (death_functions.empty())
  {
    initialize_death_functions();
  }

  DeathEventFunction death_function = boost::bind(&DeathEventFunctions::null, _1, _2, _3);

  DeathEventFunctionMap::iterator d_it = death_functions.find(death_function_name);

  if (d_it != death_functions.end())
  {
    death_function = d_it->second;
  }

  return death_function;
}

// Reset and re-initialize all the event functions.
void EventFunctions::initialize()
{
  initialize_death_functions();
}

// Reset and re-initialize all the death functions.
void EventFunctions::initialize_death_functions()
{
  death_functions.clear();

  DeathEventFunction win_function = boost::bind(&DeathEventFunctions::win, _1, _2, _3);

  death_functions.insert(make_pair(DeathEventFunctionNames::DEATH_EVENT_WIN, win_function));
}
