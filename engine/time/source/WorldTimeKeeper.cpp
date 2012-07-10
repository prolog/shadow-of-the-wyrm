#include "Game.hpp"
#include "WorldTimeKeeper.hpp"

using std::map;
using std::string;

WorldTimeKeeper::WorldTimeKeeper()
: seconds_counter(0), total_seconds_counter(0)
{
}

void WorldTimeKeeper::register_observer(const uint minutes_key, ITimeObserverPtr new_observer)
{
  if (new_observer)
  {
    map<uint, map<string, ITimeObserverPtr> >::iterator m_it = observers.find(minutes_key);

    if (m_it == observers.end())
    {
      map<string, ITimeObserverPtr> observer_map;
      observer_map.insert(make_pair(new_observer->get_id(), new_observer));
      observers.insert(make_pair(minutes_key, observer_map));
    }
    else
    {
      map<string, ITimeObserverPtr>& observer_map = m_it->second;
      observer_map.insert(make_pair(new_observer->get_id(), new_observer));
    }
  }
}

void WorldTimeKeeper::deregister_observer(const uint minutes_key, ITimeObserverPtr old_observer)
{
  if (old_observer)
  {
    map<uint, map<string, ITimeObserverPtr> >::iterator m_it = observers.find(minutes_key);
    
    if (m_it != observers.end())
    {
      observers[minutes_key].erase(old_observer->get_id());
    }
  }
}

void WorldTimeKeeper::reset()
{
  observers.clear();
}

void WorldTimeKeeper::tick(const double seconds)
{
  Game* game = Game::instance();
  seconds_counter += seconds;
  
  while (game && game->should_keep_playing() && seconds_counter > 60)
  {
    seconds_counter -= 60;
    total_seconds_counter += 60;
    
    ulonglong total_minutes = static_cast<ulonglong>(total_seconds_counter) / 60;

    for (map<uint, map<string, ITimeObserverPtr> >::iterator m_it = observers.begin(); m_it != observers.end(); m_it++)
    {
      uint minutes_value = m_it->first;
      
      if (total_minutes % minutes_value == 0)
      {
        map<string, ITimeObserverPtr>& observers_map = m_it->second;
        
        for (map<string, ITimeObserverPtr>::iterator obs_it = observers_map.begin(); obs_it != observers_map.end(); obs_it++)
        {
          obs_it->second->notify(minutes_value);
        }
      }
    }
  }  
}

