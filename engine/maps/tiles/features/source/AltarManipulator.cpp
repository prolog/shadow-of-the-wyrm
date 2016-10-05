#include "ActionTextKeys.hpp"
#include "Altar.hpp"
#include "AltarManipulator.hpp"
#include "DeityDecisionStrategyFactory.hpp"
#include "MessageManagerFactory.hpp"

using namespace std;

AltarManipulator::AltarManipulator(FeaturePtr feature)
: IFeatureManipulator(feature)
{
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

  if (dropping_creature != nullptr && item != nullptr)
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
        int piety_loss = ddi.adjust_creature_piety(dropping_creature, feature);

        // TODO: Item alteration message based on piety loss.
        // 0 piety = cross-aligned, item cursed
        // > 0 piety = co-aligned, item blessed

        item_altered = true;
      }
    }
  }

  return item_altered;
}
