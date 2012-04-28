#include "ReligionManager.hpp"
#include "Game.hpp"

using std::string;

ReligionManager::ReligionManager()
{
}

string ReligionManager::get_deity_name_sid(const string& deity_id) const
{
  string deity_name_sid;
  
  Game* game = Game::instance();
  
  if (game)
  {
    DeityMap deities = game->get_deities_ref();
    DeityPtr deity   = deities[deity_id];
    
    if (deity)
    {
      deity_name_sid = deity->get_name_sid();
    }
  }
  
  return deity_name_sid;
}
