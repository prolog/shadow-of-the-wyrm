#include "ActionTextKeys.hpp"
#include "AltarManipulator.hpp"
#include "DeityDecisionStrategyFactory.hpp"
#include "Features.hpp"
#include "Game.hpp"
#include "MessageManagerFactory.hpp"

using namespace std;

AltarManipulator::AltarManipulator(FeaturePtr feature)
: FeatureManipulator(feature)
{
}

bool AltarManipulator::desecrate(CreaturePtr creature, MapPtr current_map)
{
  if (feature != nullptr)
  {
    Game::instance().get_deity_action_manager_ref().notify_action(creature, current_map, get_creature_action_key(), false);

    return true;
  }

  return false;
}

bool AltarManipulator::handle(TilePtr tile, CreaturePtr creature)
{
  if (creature && creature->get_is_player())
  {
    IMessageManager& manager = MM::instance();
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_HANDLE_ALTAR));
    manager.send();
  }

  return true;
}

bool AltarManipulator::drop(CreaturePtr dropping_creature, TilePtr tile, ItemPtr item)
{
  bool item_altered = false;

  if (dropping_creature != nullptr && item != nullptr && Game::instance().do_deities_exist())
  {
    AltarPtr altar = dynamic_pointer_cast<Altar>(feature);

    if (altar != nullptr)
    {
      string deity_id = altar->get_deity_id();

      IDeityDecisionStrategyPtr deity_decision_strategy = DeityDecisionStrategyFactory::create_deity_decision_strategy(deity_id);
      DeityDecisionStrategyHandlerPtr deity_decision_handler = deity_decision_strategy->get_decision_for_altar_drop(dropping_creature, feature, item);
      
      if (deity_decision_handler->decide(dropping_creature))
      {
        DeityDecisionImplications ddi = deity_decision_handler->handle_decision(dropping_creature, tile);
        ddi.adjust_creature_piety(dropping_creature, feature);

        item_altered = true;
      }
    }
  }

  return item_altered;
}

void AltarManipulator::kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, const Coordinate& feature_coord, FeaturePtr feature)
{
  desecrate(creature, current_map);
}

