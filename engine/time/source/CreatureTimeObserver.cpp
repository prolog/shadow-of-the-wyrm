#include <boost/foreach.hpp>
#include <boost/make_shared.hpp>
#include "CreatureHPRegeneration.hpp"
#include "CreaturePietyRegeneration.hpp"
#include "CreatureSkillIncrementer.hpp"
#include "CreatureTimeObserver.hpp"
#include "Game.hpp"
#include "MovementAccumulationChecker.hpp"
#include "MovementAccumulator.hpp"
#include "RegenerationConstants.hpp"

using namespace std;

CreatureTimeObserver::CreatureTimeObserver()
: ITimeObserver()
{
  initialize_regeneration_helpers();
}

// Set the list of regeneration helpers to apply to each creature on each "tick" (1 min passed)
void CreatureTimeObserver::initialize_regeneration_helpers()
{
  // Regenerate the creature's HP
  ICreatureRegenerationPtr hp_regen     = boost::make_shared<CreatureHPRegeneration>();
  // Regenerate or degenerate the creature's piety, depending on the value.
  ICreatureRegenerationPtr piety_regen  = boost::make_shared<CreaturePietyRegeneration>();
  // Update the minute values for the current movement accumulations.
  ICreatureRegenerationPtr move_accum   = boost::make_shared<MovementAccumulator>();
  // Do things based on current movement accumulations - drown, fall from mountains, etc.
  ICreatureRegenerationPtr move_checkr  = boost::make_shared<MovementAccumulationChecker>();
  // Every day, increment the creature's skills if they have been used enough.
  ICreatureRegenerationPtr skill_checkr = boost::make_shared<CreatureSkillIncrementer>(1440);
  
  regen.push_back(hp_regen    );
  regen.push_back(piety_regen );
  regen.push_back(move_accum  );
  regen.push_back(move_checkr );
  regen.push_back(skill_checkr);
}

void CreatureTimeObserver::notify(const ulonglong minutes_this_tick)
{
  update_minutes_elapsed(minutes_this_tick);

  Game* game = Game::instance();

  if (game)
  {
    // Get the list of creatures.
    MapPtr current_map = game->get_current_map();
    map<string, CreaturePtr> creatures = current_map->get_creatures();
    
    // Apply each creature regeneration helper to each creature on the map
    for (map<string, CreaturePtr>::iterator c_it = creatures.begin(); c_it != creatures.end(); c_it++)
    {
      CreaturePtr creature = c_it->second;
      
      BOOST_FOREACH(ICreatureRegenerationPtr regen_helper, regen)
      {
        if (game->should_keep_playing())
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
}
