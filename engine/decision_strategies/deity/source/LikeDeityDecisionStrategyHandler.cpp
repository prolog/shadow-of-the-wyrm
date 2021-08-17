#include "LikeDeityDecisionStrategyHandler.hpp"
#include "DeityTextKeys.hpp"
#include "Game.hpp"
#include "ReligionManager.hpp"

using std::string;

const int LikeDeityDecisionStrategyHandler::LIKE_DECISION_PIETY = 50;

LikeDeityDecisionStrategyHandler::LikeDeityDecisionStrategyHandler(const string& new_deity_id)
: DeityDecisionStrategyHandler(new_deity_id), deity(nullptr)
{
}

LikeDeityDecisionStrategyHandler::LikeDeityDecisionStrategyHandler(Deity* new_deity)
: DeityDecisionStrategyHandler(new_deity->get_id()), deity(new_deity)
{
}

std::unique_ptr<DeityDecisionStrategyHandler> LikeDeityDecisionStrategyHandler::clone()
{
  std::unique_ptr<DeityDecisionStrategyHandler> handler = std::make_unique<LikeDeityDecisionStrategyHandler>(*this);
  return handler;
}

bool LikeDeityDecisionStrategyHandler::decide(CreaturePtr creature)
{
  bool decision = false;

  if (creature)
  {
    Religion& religion = creature->get_religion_ref();
    DeityRelations& relations = religion.get_deity_relations_ref();
    DeityStatus& status = relations[religion.get_active_deity_id()];
    
    decision = (status.get_piety() >= 0);
  }

  return decision;
}

DeityDecisionImplications LikeDeityDecisionStrategyHandler::handle_decision(CreaturePtr creature, TilePtr tile)
{
  // Do nothing for now.

  return get_deity_decision_implications(creature, tile);
}

int LikeDeityDecisionStrategyHandler::get_piety_amount() const
{
  return LIKE_DECISION_PIETY;
}

string LikeDeityDecisionStrategyHandler::get_message_sid() const
{
  if (deity != nullptr)
  {
    return deity->get_anger_message_sid();
  }
  else
  {
    return DeityTextKeys::DEITY_ACTION_PLEASED;
  }
}

