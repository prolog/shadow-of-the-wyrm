#include "DeityTextKeys.hpp"
#include "CombatManager.hpp"
#include "DeathSourceTextKeys.hpp"
#include "DeityTextKeys.hpp"
#include "Game.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "SmiteDeityDecisionStrategyHandler.hpp"

using namespace std;

const int SmiteDeityDecisionStrategyHandler::ADJACENT_HOSTILE_SMITE_THRESHOLD = 2;
const int SmiteDeityDecisionStrategyHandler::SMITE_LEVEL_DAMAGE_MULTIPLIER = 5;
const int SmiteDeityDecisionStrategyHandler::SMITE_EFFECT_BONUS = 100;

SmiteDeityDecisionStrategyHandler::SmiteDeityDecisionStrategyHandler(const string& new_deity_id)
: DeityDecisionStrategyHandler(new_deity_id)
{
}

std::unique_ptr<DeityDecisionStrategyHandler> SmiteDeityDecisionStrategyHandler::clone()
{
  std::unique_ptr<DeityDecisionStrategyHandler> handler = std::make_unique<SmiteDeityDecisionStrategyHandler>(*this);
  return handler;
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

    if (!cdm.empty())
    {
      IMessageManager& manager = MMF::instance();
      manager.add_new_message(StringTable::get(DeityTextKeys::PRAYER_SMITE_DIVINE_LIGHTNING));
      manager.send();

      for (auto cdm_pair : cdm)
      {
        CreaturePtr adj_creature = cdm_pair.second;

        // Smite the adjacent creatures!
        if (adj_creature != nullptr && adj_creature->hostile_to(creature->get_id()))
        {
          int damage = creature->get_level().get_current() * SMITE_LEVEL_DAMAGE_MULTIPLIER;
          Damage smite_damage;
          smite_damage.set_modifier(damage);
          smite_damage.set_effect_bonus(SMITE_EFFECT_BONUS);
          // Smites set the vorpal flag.
          smite_damage.set_damage_flag(DamageFlagType::DAMAGE_FLAG_VORPAL, true);
          smite_damage.set_damage_type(DamageType::DAMAGE_TYPE_LIGHTNING);

          string source_id = ""; // source id - deity is causing the damage, but doesn't actually exist and so doesn't get exp

          cm.deal_damage(nullptr, adj_creature, AttackType::ATTACK_TYPE_MAGICAL, source_id, damage, smite_damage, "", DeathSourceTextKeys::DEATH_SOURCE_SMITE);
        }
      }
    }
  }

  return get_deity_decision_implications(creature, tile);
}

// Divine intervention is a very costly thing!
int SmiteDeityDecisionStrategyHandler::get_piety_amount() const
{
  return 5000;
}

string SmiteDeityDecisionStrategyHandler::get_message_sid() const
{
  string message_sid = DeityTextKeys::PRAYER_SMITE;
  return message_sid;
}
