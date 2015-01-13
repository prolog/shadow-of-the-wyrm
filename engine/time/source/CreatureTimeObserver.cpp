#include "CreatureAlcoholTimer.hpp"
#include "CreatureAPRegeneration.hpp"
#include "CreatureHPRegeneration.hpp"
#include "CreatureHungerTimer.hpp"
#include "CreaturePietyRegeneration.hpp"
#include "CreatureSkillIncrementer.hpp"
#include "CreatureStatisticsModifiers.hpp"
#include "CreatureStatuses.hpp"
#include "CreatureTimeObserver.hpp"
#include "Game.hpp"
#include "MovementAccumulationChecker.hpp"
#include "MovementAccumulator.hpp"
#include "RegenerationConstants.hpp"
#include "Serialize.hpp"

using namespace std;

CreatureTimeObserver::CreatureTimeObserver()
: ITimeObserver()
{
  initialize_regeneration_helpers();
}

// Set the list of regeneration helpers to apply to each creature on each "tick" (1 min passed)
void CreatureTimeObserver::initialize_regeneration_helpers()
{
  regen.clear();

  // Regenerate the creature's HP
  ICreatureRegenerationPtr hp_regen     = std::make_shared<CreatureHPRegeneration>();
  // Regenerate the creature's AP
  ICreatureRegenerationPtr ap_regen     = std::make_shared<CreatureAPRegeneration>();
  // Regenerate or degenerate the creature's piety, depending on the value.
  ICreatureRegenerationPtr piety_regen  = std::make_shared<CreaturePietyRegeneration>();
  // Update the minute values for the current movement accumulations.
  ICreatureRegenerationPtr move_accum   = std::make_shared<MovementAccumulator>();
  // Do things based on current movement accumulations - drown, fall from mountains, etc.
  ICreatureRegenerationPtr move_checkr  = std::make_shared<MovementAccumulationChecker>();
  // Every day, increment the creature's skills if they have been used enough.
  ICreatureRegenerationPtr skill_checkr = std::make_shared<CreatureSkillIncrementer>(1440);
  // Every minute, reduce the player's hunger clock...
  ICreatureRegenerationPtr hungr_checkr = std::make_shared<CreatureHungerTimer>();
  // Every minute, call the tick() function for each status the creature has.
  ICreatureRegenerationPtr status_chekr = std::make_shared<CreatureStatuses>();
  // Every half an hour to an hour, do alcohol absorption and metabolism.
  ICreatureRegenerationPtr alcohol_chkr = std::make_shared<CreatureAlcoholTimer>();
  // Every minute, check to see if the creature has spell statistics modifiers that should be removed.
  ICreatureRegenerationPtr sp_stat_chkr = std::make_shared<CreatureStatisticsModifiers>();

  regen.push_back(hp_regen    );
  regen.push_back(ap_regen    );
  regen.push_back(piety_regen );
  regen.push_back(move_accum  );
  regen.push_back(move_checkr );
  regen.push_back(skill_checkr);
  regen.push_back(hungr_checkr);
  regen.push_back(status_chekr);
  regen.push_back(alcohol_chkr);
  regen.push_back(sp_stat_chkr);
}

void CreatureTimeObserver::notify(const ulonglong minutes_this_tick)
{
  update_minutes_elapsed(minutes_this_tick);

  Game& game = Game::instance();

  // Get the list of creatures.
  MapPtr current_map = game.get_current_map();
  map<string, CreaturePtr> creatures = current_map->get_creatures();
    
  // Apply each creature regeneration helper to each creature on the map
  for (map<string, CreaturePtr>::iterator c_it = creatures.begin(); c_it != creatures.end(); c_it++)
  {
    CreaturePtr creature = c_it->second;
      
    for (ICreatureRegenerationPtr regen_helper : regen)
    {
      if (game.should_keep_playing())
      {
        if (regen_helper)
        {
          regen_helper->tick(creature, minutes_this_tick, minutes_elapsed); 
        }
      }
      else
      {
        return;
      }
    }
  }
}

ITimeObserver* CreatureTimeObserver::clone()
{
  CreatureTimeObserver* creature_observer = new CreatureTimeObserver(*this);

  // Ensure that the new CreatureTimeObserver points to a *different*
  // set of regeneration helpers than the current object.
  creature_observer->initialize_regeneration_helpers();

  return creature_observer;
}

// No need to serialize the vector - a new list gets built up each time the object is created,
// and it's never actually updated (yet, anyway).
bool CreatureTimeObserver::serialize(ostream& stream) const
{
  ITimeObserver::serialize(stream);

  return true;
}

// See serialization note.
bool CreatureTimeObserver::deserialize(istream& stream)
{
  ITimeObserver::deserialize(stream);

  return true;
}

ClassIdentifier CreatureTimeObserver::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_CREATURE_TIME_OBSERVER;
}

#ifdef UNIT_TESTS
#include "unit_tests/CreatureTimeObserver_test.cpp"
#endif

