#include "Game.hpp"
#include "HostilityManager.hpp"
#include "PlayerConstants.hpp"

using std::string;

// Set the creature hostile to another creature with the given creature_id.
void HostilityManager::set_hostility_to_creature(CreaturePtr creature, const string& hostile_to_creature_id)
{
  DecisionStrategyPtr decision_strategy = creature->get_decision_strategy();
  ThreatRatings& threat_ratings = decision_strategy->get_threats_ref();

  // JCD FIXME: It would be good to increase this every time at
  // some point, so that continually attacking a creature makes
  // it more and more hostile to you over any other...
  if (creature->get_id() != hostile_to_creature_id)
  {
    threat_ratings.add_threat(hostile_to_creature_id, 100); // JCD FIXME magic number
  }
}

// Set the creature hostile to the player.
void HostilityManager::set_hostility_to_player(CreaturePtr creature)
{
  set_hostility_to_creature(creature, PlayerConstants::PLAYER_CREATURE_ID);
}

