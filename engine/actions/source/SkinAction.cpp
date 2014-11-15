#include "global_prototypes.hpp"
#include "ActionTextKeys.hpp"
#include "Game.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "SkinAction.hpp"

using std::string;

SkinAction::SkinAction()
{
}

// Attempt to skin a corpse.  If successful, this will produce a skin which
// can be worked at a tannery to create leather armour.
ActionCostValue SkinAction::skin(CreaturePtr creature, const ActionManager * const am)
{
  ActionCostValue acv = 0;

  if (creature)
  {
    Game& game = Game::instance();
    MapPtr current_map = game.get_current_map();
    MapType map_type = current_map->get_map_type();

    if (map_type == MAP_TYPE_WORLD)
    {
      add_skin_world_map_message(creature);
    }
    // Overworld/underworld map - we can attempt to skin.
    else
    {
      TilePtr creature_tile = MapUtils::get_tile_for_creature(current_map, creature);

      if (creature_tile)
      {
        IInventoryPtr ground_items = creature_tile->get_items();
        
        if (ground_items)
        {
          if (ground_items->has_item_with_property(ConsumableConstants::CORPSE_DESCRIPTION_SID))
          {
            // ...

            acv = get_action_cost_value(creature);
          }
          else
          {
            add_no_corpses_message(creature);
          }
        }
      }
    }
  }

  return acv;
}

// Skinning can't be done on the world map - it must be done on an overworld
// or underworld map.
void SkinAction::add_skin_world_map_message(CreaturePtr creature)
{
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

  manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_SKIN_WORLD_MAP));
  manager.send();
}

// Skinning requires corpses on the ground.
void SkinAction::add_no_corpses_message(CreaturePtr creature)
{
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

  manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_SKIN_NO_CORPSES));
  manager.send();
}

ActionCostValue SkinAction::get_action_cost_value(CreaturePtr creature) const
{
  return 1;
}
