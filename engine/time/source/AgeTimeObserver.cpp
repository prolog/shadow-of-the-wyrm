#include "AgeTimeObserver.hpp"
#include "DeathManagerFactory.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "MapUtils.hpp"
#include "RaceManager.hpp"
#include "RNG.hpp"

using std::string;

AgeTimeObserver::AgeTimeObserver()
{
}

void AgeTimeObserver::notify(const ulonglong minutes_passed)
{
  Game& game = Game::instance();
  MapRegistry& mr = game.get_map_registry_ref();

  MapRegistryMap& maps = mr.get_maps_ref();

  for (auto& m_pair : maps)
  {
    MapPtr cur_map = m_pair.second;

    if (cur_map != nullptr)
    {
      process_creatures(cur_map, cur_map->get_creatures_ref());
    }
  }
}

// Add a year to each creature in the map.
// If the creature has aged too much, remove the creature from the game.
// Death is a cruel mistress.
void AgeTimeObserver::process_creatures(MapPtr cur_map, CreatureMap& creature_map)
{
  RaceManager rm;

  for (auto& c_pair : creature_map)
  {
    CreaturePtr creature = c_pair.second;

    if (creature != nullptr)
    {
      Statistic age = creature->get_age();
      age.set_current(age.get_current() + 1);

      RacePtr creature_race = rm.get_race(creature->get_race_id());
      AgeInfo age_info = creature_race->get_age_info();
      Range<uint> max_age_range = age_info.get_maximum_age();
      uint max = RNG::range(max_age_range.get_min(), max_age_range.get_max());

      if (age.get_current() > age.get_base())
      {
        DeathManagerPtr dm = DeathManagerFactory::create_death_manager(nullptr, creature, cur_map);

        if (dm != nullptr)
        {
          dm->die();
        }
      }
      else
      {
        // Creature has lived to see another year.
        creature->set_age(age);
      }
    }
  }
}

ITimeObserver* AgeTimeObserver::clone() 
{
  return new AgeTimeObserver(*this);
}

ClassIdentifier AgeTimeObserver::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_AGE_TIME_OBSERVER;
}

#ifdef UNIT_TESTS
#include "unit_tests/AgeTimeObserver_test.cpp"
#endif

