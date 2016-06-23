#include "global_prototypes.hpp"
#include "ActionTextKeys.hpp"
#include "Conversion.hpp"
#include "Game.hpp"
#include "ItemFilterFactory.hpp"
#include "ItemManager.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "RNG.hpp"
#include "SkinAction.hpp"
#include "CorpseCalculator.hpp"
#include "SkinningConstants.hpp"

using namespace std;

SkinAction::SkinAction()
{
}

// Attempt to skin a corpse.  If successful, this will produce a skin which
// can be worked at a tannery to create leather armour.
ActionCostValue SkinAction::skin(CreaturePtr creature, ActionManager * const am)
{
  ActionCostValue acv = 0;

  if (creature)
  {
    Game& game = Game::instance();
    MapPtr current_map = game.get_current_map();
    MapType map_type = current_map->get_map_type();

    if (map_type == MapType::MAP_TYPE_WORLD)
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
          int num_corpses = ground_items->count_items_with_property(ConsumableConstants::CORPSE_DESCRIPTION_SID);
          ItemPtr selected_corpse;

          if (num_corpses == 1)
          {
            acv = get_action_cost_value(creature);

            list<ItemPtr>& items = ground_items->get_items_ref();
            
            for (ItemPtr item : items)
            {
              if (item->has_additional_property(ConsumableConstants::CORPSE_DESCRIPTION_SID))
              {
                selected_corpse = item;
                break;
              }
            }

            acv = attempt_skin(creature, selected_corpse, creature_tile);
          }
          else if (num_corpses > 1)
          {
            list<IItemFilterPtr> corpse_filter = ItemFilterFactory::create_item_property_type_filter(vector<pair<string, string>>{make_pair(ConsumableConstants::CORPSE_DESCRIPTION_SID, "")});
            selected_corpse = am->inventory(creature, ground_items, corpse_filter, {}, false);

            acv = attempt_skin(creature, selected_corpse, creature_tile);
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

ActionCostValue SkinAction::attempt_skin(CreaturePtr creature, ItemPtr item, TilePtr tile)
{
  ActionCostValue acv = 0;
  Game& game = Game::instance();

  if (creature && item && tile)
  {
    CorpseCalculator cc;
    int chance_skin = cc.calculate_chance_successful_skin(creature);

    if (RNG::percent_chance(chance_skin))
    {
      creature->get_skills().mark(SkillType::SKILL_GENERAL_SKINNING);
      add_skin_successful_message(creature); 
      create_skin_and_add_to_tile(creature, item, tile);
    }
    else
    {
      add_mangled_corpse_skin_message(creature);
    }

    // Remove the corpse from the ground.
    tile->get_items()->remove(item->get_id());

    acv = get_action_cost_value(creature);
  }

  return acv;
}

// Create the skin and add it to the tile.  The skin's resistances should
// be based off the corpse of the creature skinned.
void SkinAction::create_skin_and_add_to_tile(CreaturePtr creature, ItemPtr corpse, TilePtr tile)
{
  if (corpse && tile)
  {
    ItemManager im;

    ItemPtr skin = im.create_item(SkinningConstants::SKIN_ID, 1);
    skin->set_additional_property(SkinningConstants::SKIN_IS_SKIN, Bool::to_string(true));
    skin->set_additional_property(SkinningConstants::SKIN_DESCRIPTION_SID, corpse->get_additional_property(ConsumableConstants::CORPSE_SHORT_DESCRIPTION_SID));
  	skin->set_additional_property(SkinningConstants::SKIN_USAGE_DESCRIPTION_SID, corpse->get_additional_property(ConsumableConstants::CORPSE_DESCRIPTION_SID));
    skin->set_additional_property(SkinningConstants::SKIN_SOAK, corpse->get_additional_property(SkinningConstants::SKIN_SOAK));

    // Update the skin's resistances based on corpse resistances.
    Resistances res = corpse->get_resistances();
    skin->set_resistances(res);

    if (skin)
    {
      tile->get_items()->add(skin);
    }
  }
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

void SkinAction::add_skin_successful_message(CreaturePtr creature)
{
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

  manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_SKIN_SUCCESSFUL));
  manager.send();
}

// Failing to skin a corpse mangled it, and it disappears.
void SkinAction::add_mangled_corpse_skin_message(CreaturePtr creature)
{
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

  manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_SKIN_MANGLED_CORPSE));
  manager.send();
}

ActionCostValue SkinAction::get_action_cost_value(CreaturePtr creature) const
{
  return 1;
}
