#include "AgeTimeObserver.hpp"
#include "CombatManager.hpp"
#include "DeathManagerFactory.hpp"
#include "DeathSourceTextKeys.hpp"
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

      if (age.get_current() > age.get_base())
      {
        int oldage_damage = creature->get_hit_points().get_current() + 10;
        Damage oldage_default;
        oldage_default.set_modifier(oldage_damage);

        CombatManager cm;
        cm.deal_damage(nullptr, creature, AttackType::ATTACK_TYPE_MELEE_TERTIARY_UNARMED, "", oldage_damage, oldage_default, "", DeathSourceTextKeys::DEATH_SOURCE_OLD_AGE);
      }
      else
      {
        // Creature has lived to see another year.
        creature->set_age(age);
      }
    }
  }
}

std::unique_ptr<ITimeObserver> AgeTimeObserver::clone()
{
  std::unique_ptr<ITimeObserver> ato = std::make_unique<AgeTimeObserver>(*this);
  return ato;
}

ClassIdentifier AgeTimeObserver::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_AGE_TIME_OBSERVER;
}

#ifdef UNIT_TESTS
#include "unit_tests/AgeTimeObserver_test.cpp"
#endif

