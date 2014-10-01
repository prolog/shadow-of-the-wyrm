#include "OfferAction.hpp"
#include "ActionTextKeys.hpp"
#include "Game.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"

using namespace std;

OfferAction::OfferAction()
{
}

// Sacrifice an item to one's deity.
ActionCostValue OfferAction::offer(CreaturePtr creature)
{
  ActionCostValue acv = get_action_cost_value(creature);

  if (creature)
  {
    // Is the creature on an altar?
    Game& game = Game::instance();
    MapPtr current_map = game.get_current_map();
    TilePtr tile = MapUtils::get_tile_for_creature(current_map, creature);
    FeaturePtr feature = tile->get_feature();

    // On an altar - pick an item to sacrifice
    if (tile && feature && feature->can_offer())
    {
    }
    else
    {
      add_no_altar_message(creature);
    }
  }

  return acv;
}

void OfferAction::add_no_altar_message(CreaturePtr creature)
{
  // No altar or other sacrifice-enabled feature present.
  if (creature->get_is_player())
  {
    string no_altar_msg = StringTable::get(ActionTextKeys::ACTION_SACRIFICE_NO_ALTAR);
    IMessageManager& manager = MessageManagerFactory::instance();

    manager.add_new_message(no_altar_msg);
    manager.send();
  }
}

ActionCostValue OfferAction::get_action_cost_value(CreaturePtr creature) const
{
  return 1;
}

