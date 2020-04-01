#include "DislikeDeityDecisionStrategyHandler.hpp"
#include "DeityTextKeys.hpp"
#include "Game.hpp"
#include "ReligionManager.hpp"

using std::string;

const int DislikeDeityDecisionStrategyHandler::DISLIKE_DECISION_PIETY_LOSS = 750;
const int DislikeDeityDecisionStrategyHandler::DISLIKE_DECISION_ANGER_THRESHOLD = -1000;

DislikeDeityDecisionStrategyHandler::DislikeDeityDecisionStrategyHandler(const string& new_deity_id)
: DeityDecisionStrategyHandler(new_deity_id), deity(nullptr)
{
}

DislikeDeityDecisionStrategyHandler::DislikeDeityDecisionStrategyHandler(Deity* new_deity)
: DeityDecisionStrategyHandler(new_deity->get_id()), deity(new_deity)
{
}

std::unique_ptr<DeityDecisionStrategyHandler> DislikeDeityDecisionStrategyHandler::clone()
{
  std::unique_ptr<DeityDecisionStrategyHandler> handler = std::make_unique<DislikeDeityDecisionStrategyHandler>(*this);
  return handler;
}

// The Nine only dislike those with negative piety.
//
// They're very scientific, and it makes it easy to model.
bool DislikeDeityDecisionStrategyHandler::decide(CreaturePtr creature)
{
  bool decision = false;

  if (creature)
  {
    Religion& religion = creature->get_religion_ref();
    DeityRelations& relations = religion.get_deity_relations_ref();
    DeityStatus& status = relations[religion.get_active_deity_id()];
    
    decision = (status.get_piety() < 0);
  }

  return decision;
}

DeityDecisionImplications DislikeDeityDecisionStrategyHandler::handle_decision(CreaturePtr creature, TilePtr tile)
{
  ReligionManager rm;
  Deity* deity = rm.get_deity(deity_id);

  if (deity != nullptr)
  {
    int piety = rm.get_piety_for_active_deity(creature);
    MapPtr map = Game::instance().get_current_map();

    if (piety < DISLIKE_DECISION_ANGER_THRESHOLD && map != nullptr)
    {
      ScriptEngine& se = Game::instance().get_script_engine_ref();
      string anger_script = deity->get_anger_script();
      bool is_world_map = map->get_map_type() == MapType::MAP_TYPE_WORLD;

      se.execute(anger_script, {});
      se.call_function("anger", { "string", "string", "boolean" }, { creature->get_id(), deity->get_id(), std::to_string(is_world_map) }, 0);
    }
  }

  return get_deity_decision_implications(creature, tile);
}

int DislikeDeityDecisionStrategyHandler::get_piety_loss() const
{
  return DISLIKE_DECISION_PIETY_LOSS;
}

string DislikeDeityDecisionStrategyHandler::get_message_sid() const
{
  if (deity != nullptr)
  {
    return deity->get_anger_message_sid();
  }
  else
  {
    return DeityTextKeys::DEITY_ACTION_DISPLEASED;
  }
}

