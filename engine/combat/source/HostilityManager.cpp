#include "CombatConstants.hpp"
#include "Game.hpp"
#include "HostilityManager.hpp"
#include "PlayerConstants.hpp"

using namespace std;

// Set the creature hostile to another creature with the given creature_id.
void HostilityManager::set_hostility_to_creature(CreaturePtr creature, const string& hostile_to_creature_id)
{
  DecisionStrategyPtr decision_strategy = creature->get_decision_strategy();
  ThreatRatings& threat_ratings = decision_strategy->get_threats_ref();

  if (creature->get_id() != hostile_to_creature_id)
  {
    pair<bool, int> threat_exists = threat_ratings.has_threat(hostile_to_creature_id);
    int old_threat_rating = threat_exists.second;

    if (threat_exists.first)
    {
      int new_threat_rating = std::max<int>(old_threat_rating, old_threat_rating + CombatConstants::THREAT_RATING_INCREMENT);
      threat_ratings.update_threat(hostile_to_creature_id, threat_exists.second, new_threat_rating);
    }
    else
    {
      threat_ratings.add_threat(hostile_to_creature_id, CombatConstants::INITIAL_THREAT_RATING);
    }
  }
}

// Set the creature hostile to the player.
void HostilityManager::set_hostility_to_player(CreaturePtr creature)
{
  set_hostility_to_creature(creature, PlayerConstants::PLAYER_CREATURE_ID);
}

