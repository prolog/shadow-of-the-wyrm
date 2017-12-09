#include "Game.hpp"
#include "HostilityManager.hpp"
#include "ThreatConstants.hpp"

using namespace std;

// Set the creature hostile to another creature with the given creature_id.
void HostilityManager::set_hostility_to_creature(CreaturePtr creature, const string& hostile_to_creature_id, const int hostility_level)
{
  if (creature != nullptr)
  {
    DecisionStrategyPtr decision_strategy = creature->get_decision_strategy();
    ThreatRatings& threat_ratings = decision_strategy->get_threats_ref();

    if (creature->get_id() != hostile_to_creature_id)
    {
      pair<bool, int> threat_exists = threat_ratings.has_threat(hostile_to_creature_id);
      int old_threat_rating = threat_exists.second;

      if (threat_exists.first)
      {
        int new_threat_rating = std::max<int>(old_threat_rating, old_threat_rating + ThreatConstants::THREAT_RATING_INCREMENT);
        threat_ratings.update_threat(hostile_to_creature_id, threat_exists.second, new_threat_rating);
      }
      else
      {
        threat_ratings.add_threat(hostile_to_creature_id, hostility_level);
      }
    }
  }
}

// Set the creature hostile to the player.
void HostilityManager::set_hostility_to_player(CreaturePtr creature, const bool hostile, const int hostility_level)
{
  if (hostile)
  {
    set_hostility_to_creature(creature, CreatureID::CREATURE_ID_PLAYER, hostility_level);
  }
  else
  {
    DecisionStrategyPtr decision_strategy = creature->get_decision_strategy();
    ThreatRatings& threat_ratings = decision_strategy->get_threats_ref();

    pair<bool, int> threat_exists = threat_ratings.has_threat(CreatureID::CREATURE_ID_PLAYER);
    threat_ratings.remove_threat(CreatureID::CREATURE_ID_PLAYER, threat_exists.second);
  }
}

void HostilityManager::remove_hostility_to_creature(CreaturePtr creature, const string& hostile_to_creature_id)
{
  if (creature != nullptr)
  {
    DecisionStrategyPtr decision_strategy = creature->get_decision_strategy();
    ThreatRatings& threat_ratings = decision_strategy->get_threats_ref();

    if (creature->get_id() != hostile_to_creature_id)
    {
      pair<bool, int> threat_exists = threat_ratings.has_threat(hostile_to_creature_id);
      if (threat_exists.first)
      {
        threat_ratings.remove_threat(hostile_to_creature_id, threat_exists.second);
      }
    }
  }
}