#include "DeityTextKeys.hpp"
#include "CombatManager.hpp"
#include "Game.hpp"
#include "MapUtils.hpp"
#include "SmiteDeityDecisionStrategyHandler.hpp"

using namespace std;

const int SmiteDeityDecisionStrategyHandler::ADJACENT_HOSTILE_SMITE_THRESHOLD = 2;
const int SmiteDeityDecisionStrategyHandler::SMITE_LEVEL_DAMAGE_MULTIPLIER = 5;

SmiteDeityDecisionStrategyHandler::SmiteDeityDecisionStrategyHandler(const string& new_deity_id)
: DeityDecisionStrategyHandler(new_deity_id)
{
  deity_id = new_deity_id;
}

bool SmiteDeityDecisionStrategyHandler::decide(CreaturePtr creature)
{
  Game& game = Game::instance();
  MapPtr map = game.get_current_map();
  int adj_hostile = 0;

  CreatureDirectionMap cdm = MapUtils::get_adjacent_creatures(map, creature);

  for (auto cdm_pair : cdm)
  {
    CreaturePtr adj_creature = cdm_pair.second;

    if (adj_creature != nullptr)
    {
      // Is the creature hostile to the player?
      if (adj_creature->hostile_to(creature->get_id()))
      {
        adj_hostile++;
      }
    }
  }
  
  return (adj_hostile >= ADJACENT_HOSTILE_SMITE_THRESHOLD);
}

DeityDecisionImplications SmiteDeityDecisionStrategyHandler::handle_decision(CreaturePtr creature, TilePtr tile)
{
  if (creature != nullptr && tile != nullptr)
  {
    Game& game = Game::instance();
    MapPtr map = game.get_current_map();

    CreatureDirectionMap cdm = MapUtils::get_adjacent_creatures(map, creature);
    CombatManager cm;

    for (auto cdm_pair : cdm)
    {
      CreaturePtr adj_creature = cdm_pair.second;

      // Smite the adjacent creatures!
      if (adj_creature != nullptr && adj_creature->hostile_to(creature->get_id()))
      {
        int damage = creature->get_level().get_current() * SMITE_LEVEL_DAMAGE_MULTIPLIER;
        cm.deal_damage(nullptr, adj_creature, damage);
      }
    }
  }

  return get_deity_decision_implications(creature, tile);
}

// Divine intervention is a very costly thing!
int SmiteDeityDecisionStrategyHandler::get_piety_loss() const
{
  return 5000;
}

string SmiteDeityDecisionStrategyHandler::get_message_sid() const
{
  string message_sid = DeityTextKeys::PRAYER_SMITE;
  return message_sid;
}
