#include <boost/foreach.hpp>
#include "Game.hpp"
#include "Serialize.hpp"
#include "WorldTimeKeeper.hpp"

// Needed by serialization
#include "TimeObserverFactory.hpp"

using namespace std;

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
  Game& game = Game::instance();
  seconds_counter += seconds;
  
  while (game.should_keep_playing() && seconds_counter > 60)
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

// Serialize the time observers and time keeping details.
bool WorldTimeKeeper::serialize(ostream& stream)
{
  Serialize::write_double(stream, seconds_counter);
  Serialize::write_double(stream, total_seconds_counter);

  serialize_observers(stream);

  return true;
}

// Do the actual serialization of the observers map
bool WorldTimeKeeper::serialize_observers(ostream& stream)
{
  Serialize::write_size_t(stream, observers.size());

  BOOST_FOREACH(WorldTimeKeeperObserverMap::value_type& observer_pair, observers)
  {
    uint pair_first = observer_pair.first;

    Serialize::write_uint(stream, observer_pair.first);

    TimeObserverMap pair_second = observer_pair.second;

    Serialize::write_size_t(stream, pair_second.size());

    BOOST_FOREACH(TimeObserverMap::value_type& time_observer_pair, pair_second)
    {
      string time_observer_first = time_observer_pair.first;
      ITimeObserverPtr time_observer_ptr = time_observer_pair.second;

      Serialize::write_string(stream, time_observer_first);
      Serialize::write_class_id(stream, time_observer_ptr->get_class_identifier());
      time_observer_ptr->serialize(stream);
    }
  }

  return true;
}

// Deserialize the time observers and time keeping details.
bool WorldTimeKeeper::deserialize(istream& stream)
{
  Serialize::read_double(stream, seconds_counter);
  Serialize::read_double(stream, total_seconds_counter);

  deserialize_observers(stream);

  return true;
}

bool WorldTimeKeeper::deserialize_observers(istream& stream)
{
  size_t observers_size;
  Serialize::read_size_t(stream, observers_size);

  observers.clear();

  for (unsigned int i = 0; i < observers_size; i++)
  {
    uint map_first;
    Serialize::read_uint(stream, map_first);

    size_t map_size;
    Serialize::read_size_t(stream, map_size);

    TimeObserverMap to_map;

    for (unsigned int j = 0; j < map_size; j++)
    {
      string to_first;
      Serialize::read_string(stream, to_first);

      ClassIdentifier to_ci;
      Serialize::read_class_id(stream, to_ci);
      ITimeObserverPtr to_second = TimeObserverFactory::create_time_observer(to_ci);
      if (!to_second) return false;
      if (!to_second->deserialize(stream)) return false;

      to_map.insert(make_pair(to_first, to_second));
    }

    observers.insert(make_pair(map_first, to_map));    
  }

  return true;
}

ClassIdentifier WorldTimeKeeper::internal_class_identifier() const
{
  return CLASS_ID_WORLD_TIME_KEEPER;
}

#ifdef UNIT_TESTS
#include "unit_tests/WorldTimeKeeper_test.cpp"
#endif

