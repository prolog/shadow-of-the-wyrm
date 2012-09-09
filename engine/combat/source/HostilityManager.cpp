#include "Game.hpp"
#include "HostilityManager.hpp"

using std::string;

// Set the creature hostile to another creature with the given creature_id.
void HostilityManager::set_hostility_to_creature(CreaturePtr creature, const string& hostile_to_creature_id)
{
  Game* game = Game::instance();
  
  if (game)
  {
    CreaturePtr threat_creature = game->get_current_map()->get_creature(hostile_to_creature_id);
    
    if (threat_creature)
    {
      DecisionStrategyPtr decision_strategy = creature->get_decision_strategy();
      ThreatRatings& threat_ratings = decision_strategy->get_threats_ref();
      threat_ratings.add_threat(hostile_to_creature_id, 100);
    }
  }
}

// Set the creature hostile to the player.
void HostilityManager::set_hostility_to_player(CreaturePtr creature)
{
  set_hostility_to_creature(creature, PlayerConstants::PLAYER_CREATURE_ID);
}

