#include "CreatureTimeObserver.hpp"
#include "Game.hpp"
#include "RegenerationConstants.hpp"

using namespace std;

CreatureTimeObserver::CreatureTimeObserver()
: ITimeObserver()
{
}

void CreatureTimeObserver::notify(const ulonglong additional_minutes_elapsed)
{
  update_minutes_elapsed(additional_minutes_elapsed);

  Game* game = Game::instance();

  // JCD FIXME: Move this to separate classes for HP, MP, etc.
  if (game)
  {
    // Get the list of creatures.
    MapPtr current_map = game->get_current_map();
    map<string, CreaturePtr> creatures = current_map->get_creatures();
    
    // Calculate minutes-per-HP for each.
    for (map<string, CreaturePtr>::iterator c_it = creatures.begin(); c_it != creatures.end(); c_it++)
    {
      CreaturePtr creature = c_it->second;
      
      if (creature && !creature->is_hp_full())
      {
        // If any of them pass the check, regenerate a hit point.
        uint minutes_per_hp = hp_regen_calc.calculate_minutes_per_hit_point(creature);
        
        if (minutes_elapsed % minutes_per_hp == 0)
        {
          creature->increment_hit_points(1);
        }
      }
    }
  }
}
