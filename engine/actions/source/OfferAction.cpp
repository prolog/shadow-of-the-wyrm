#include "OfferAction.hpp"
#include "ActionManager.hpp"
#include "Game.hpp"
#include "ItemFilterFactory.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "SacrificeTextKeys.hpp"

using namespace std;

OfferAction::OfferAction()
{
}

// Sacrifice an item to one's deity.
ActionCostValue OfferAction::offer(CreaturePtr creature, ActionManager * const am)
{
  ActionCostValue acv = 0;

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
      acv = sacrifice_item(creature, am);
    }
    else
    {
      add_no_altar_message(creature);
    }
  }

  return acv;
}

// Prompt the creature to select an item for sacrifice.
ActionCostValue OfferAction::sacrifice_item(CreaturePtr creature, ActionManager * const am)
{
  ActionCostValue acv = 0;

  if (creature)
  {
    IMessageManager& manager = MessageManagerFactory::instance();

    if (creature->get_inventory()->empty() && creature->get_is_player())
    {
      manager.add_new_message(StringTable::get(SacrificeTextKeys::SACRIFICE_NO_ITEMS));
      manager.send();
    }
    else
    {
      acv = get_action_cost_value(creature);

      list<IItemFilterPtr> no_filter = ItemFilterFactory::create_empty_filter();
      ItemPtr item_to_sac = am->inventory(creature, creature->get_inventory(), no_filter, false);

      if (item_to_sac == nullptr)
      {
        manager.add_new_message(StringTable::get(SacrificeTextKeys::SACRIFICE_NO_ITEM_SELECTED));
        manager.send();
      }
      else
      {
      }
    }
  }

  return acv;
}

void OfferAction::add_no_altar_message(CreaturePtr creature)
{
  // No altar or other sacrifice-enabled feature present.
  if (creature->get_is_player())
  {
    string no_altar_msg = StringTable::get(SacrificeTextKeys::SACRIFICE_NO_ALTAR);
    IMessageManager& manager = MessageManagerFactory::instance();

    manager.add_new_message(no_altar_msg);
    manager.send();
  }
}

ActionCostValue OfferAction::get_action_cost_value(CreaturePtr creature) const
{
  return 1;
}

