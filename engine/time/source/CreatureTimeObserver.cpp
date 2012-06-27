#include <boost/foreach.hpp>
#include <boost/make_shared.hpp>
#include "CreatureHPRegeneration.hpp"
#include "CreaturePietyRegeneration.hpp"
#include "CreatureTimeObserver.hpp"
#include "Game.hpp"
#include "RegenerationConstants.hpp"

using namespace std;
using boost::make_shared;

CreatureTimeObserver::CreatureTimeObserver()
: ITimeObserver()
{
  initialize_regeneration_helpers();
}

// Set the list of regeneration helpers to apply to each creature on each "tick" (1 min passed)
void CreatureTimeObserver::initialize_regeneration_helpers()
{
  ICreatureRegenerationPtr hp_regen    = make_shared<CreatureHPRegeneration>();
  ICreatureRegenerationPtr piety_regen = make_shared<CreaturePietyRegeneration>();
  
  regen.push_back(hp_regen);
  regen.push_back(piety_regen);
}

void CreatureTimeObserver::notify(const ulonglong additional_minutes_elapsed)
{
  update_minutes_elapsed(additional_minutes_elapsed);

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
        if (regen_helper)
        {
          regen_helper->regen(creature, minutes_elapsed); 
        }
      }
    }
  }
}
