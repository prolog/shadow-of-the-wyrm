#include "ActionManager.hpp"
#include "ActionTextKeys.hpp"
#include "Conversion.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "DropAction.hpp"
#include "ItemFilterFactory.hpp"
#include "ItemIdentifier.hpp"
#include "ItemProperties.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "SeedCalculator.hpp"
#include "TextMessages.hpp"
#include "Tile.hpp"
#include "TreeSpeciesFactory.hpp"

using namespace std;

// Drop the item on to the square, if possible.
ActionCostValue DropAction::drop(CreaturePtr creature, ActionManager * const am)
{  
  ActionCostValue action_cost_value = 0;
  
  Game& game = Game::instance();
  
  if (creature)
  {
    if (game.get_current_map()->get_map_type() == MapType::MAP_TYPE_WORLD)
    {
      handle_world_drop(creature);
    }
    else
    {
      list<IItemFilterPtr> no_filter = ItemFilterFactory::create_empty_filter();
      ItemPtr item_to_drop = am->inventory(creature, creature->get_inventory(), no_filter, false);
      
      if (!item_to_drop)
      {
        handle_no_item_dropped(creature);
      }
      else // Item selected
      {
        action_cost_value = do_drop(creature, game.get_current_map(), item_to_drop);
      }      
    }
  }
  
  return action_cost_value;
}

// Handle trying to drop stuff on the world map, which is not a valid case.
void DropAction::handle_world_drop(CreaturePtr creature)
{  
  if (creature && creature->get_is_player())
  {
    IMessageManager& manager = MessageManagerFactory::instance(creature, true);
    string drop_not_allowed = StringTable::get(ActionTextKeys::ACTION_DROP_NOT_ALLOWED);
    
    manager.add_new_message(drop_not_allowed);
    manager.send();
  }  
}

// Handle trying to drop an invalid quantity (0, "a bajillion", etc)
void DropAction::handle_invalid_drop_quantity(CreaturePtr creature)
{  
  if (creature && creature->get_is_player())
  {
    IMessageManager& manager = MessageManagerFactory::instance(creature, true);
    manager.clear_if_necessary();
    string invalid_drop_quantity = StringTable::get(ActionTextKeys::ACTION_DROP_INVALID_QUANTITY);
    manager.add_new_message(invalid_drop_quantity);
    manager.send();
  }
}

// Show the description of the item being dropped, if applicable
void DropAction::handle_item_dropped_message(CreaturePtr creature, ItemPtr item)
{  
  if (item && creature && creature->get_is_player())
  {
    IMessageManager& manager = MessageManagerFactory::instance(creature, true);

    manager.clear_if_necessary();
    
    uint quantity = item->get_quantity();
    
    CurrentCreatureAbilities cca;
    string drop_message = TextMessages::get_item_drop_message(!cca.can_see(creature), item);
    
    manager.add_new_message(drop_message);
    manager.send();
  }
  // If it's not the player, and the player is in range, inform the player
  // what the creature dropped.
  else
  {
    // ...
  }  
}

// Handle the case where the intent was to drop, but then nothing was selected.
void DropAction::handle_no_item_dropped(CreaturePtr creature)
{  
  if (creature && creature->get_is_player())
  {
    IMessageManager& manager = MessageManagerFactory::instance(creature, true);
    string no_item_to_drop = StringTable::get(ActionTextKeys::ACTION_DROP_NO_ITEM_SELECTED);
    
    manager.add_new_message(no_item_to_drop);
    manager.send();
  }
}

void DropAction::handle_seed_planted_message(CreaturePtr creature, ItemPtr seed)
{
  if (creature != nullptr && seed != nullptr && creature->get_is_player())
  {
    CurrentCreatureAbilities cca;
    IMessageManager& manager = MessageManagerFactory::instance(creature, true);
    ItemIdentifier iid;

    string seed_message = ActionTextKeys::get_seed_planted_message(!cca.can_see(creature), iid.get_appropriate_usage_description(seed));

    manager.add_new_message(seed_message);
    manager.send();
  }
}

// Do the actual dropping of items.
ActionCostValue DropAction::do_drop(CreaturePtr creature, MapPtr current_map, ItemPtr item_to_drop)
{
  ActionCostValue action_cost_value = 0;
  TilePtr creatures_tile = MapUtils::get_tile_for_creature(current_map, creature);

  if (item_to_drop)
  {
    uint quantity = item_to_drop->get_quantity();
    uint selected_quantity = quantity;

    if (quantity > 1)
    {
      selected_quantity = get_drop_quantity(creature, quantity);
    }

    // Drop quantity
    if (!item_to_drop->is_valid_quantity(selected_quantity))
    {
      handle_invalid_drop_quantity(creature);
    }
    else
    {
      ItemPtr new_item = ItemPtr(item_to_drop->create_with_new_id());
      new_item->set_quantity(selected_quantity);
      
      uint old_item_quantity = item_to_drop->get_quantity() - selected_quantity;
      item_to_drop->set_quantity(old_item_quantity);

      // If the item is a seed or a pit, don't actually set it on the tile,
      // and set the relevant tile and map properties.
      string tree_species_id = item_to_drop->get_additional_property(ItemProperties::ITEM_PROPERTIES_TREE_SPECIES_ID);

      if (!tree_species_id.empty() && creatures_tile->has_been_dug())
      {
        bool planted = plant_seed(creature, tree_species_id, MapUtils::get_coordinate_for_creature(current_map, creature), creatures_tile, current_map);

        if (planted)
        {
          handle_seed_planted_message(creature, item_to_drop);
        }
      }
      else
      {
        if (creatures_tile)
        {
          IInventoryPtr inv = creatures_tile->get_items();
          inv->merge_or_add(new_item, InventoryAdditionType::INVENTORY_ADDITION_FRONT);

          // Display a message if appropriate.
          // If it's the player, remind the user what he or she dropped.
          handle_item_dropped_message(creature, new_item);
        }
      }
      
      // Remove it from the inventory, if the quantity is now zero.
      if (item_to_drop->get_quantity() == 0)
      {
        creature->get_inventory()->remove(item_to_drop->get_id());
      }

      // Advance the turn
      action_cost_value = get_action_cost_value(creature);
    }
  }
  
  return action_cost_value;
}

// Get the quantity to drop
uint DropAction::get_drop_quantity(CreaturePtr creature, const uint max_quantity) const
{  
  if (creature && creature->get_is_player())
  {
    IMessageManager& manager = MessageManagerFactory::instance(creature, true);
    Game& game = Game::instance();
    game.update_display(creature, game.get_current_map(), creature->get_decision_strategy()->get_fov_map(), false);
              
    // Prompt the user in the message buffer
    string quantity_prompt = StringTable::get(ActionTextKeys::ACTION_DROP_QUANTITY_PROMPT);

    manager.add_new_message(quantity_prompt);
    manager.send();
  }
  
  // Get quantity
  return creature->get_decision_strategy()->get_count(max_quantity);
}

// Plant a seed for a particular type of tree.
bool DropAction::plant_seed(CreaturePtr creature, const string& tree_species_id, const Coordinate& coords, TilePtr tile, MapPtr current_map)
{
  bool planted = false;

  if (!tree_species_id.empty() && current_map)
  {
    Game& game = Game::instance();
    WorldPtr world = game.get_current_world();
    planted = true;

    // Regardless of whether anything can actually grow on the tile, mark
    // it as planted.
    tile->set_additional_property(TileProperties::TILE_PROPERTY_PLANTED, to_string(true));

    if (world && current_map->get_map_type() == MapType::MAP_TYPE_OVERWORLD)
    {
      TreeSpeciesFactory tsf;

      TreeSpecies ts = tsf.create_tree_species(static_cast<TreeSpeciesID>(String::to_int(tree_species_id)));
      TileTransform tt(coords, ts.get_tile_type(), TileType::TILE_TYPE_UNDEFINED, { { ItemProperties::ITEM_PROPERTIES_TREE_SPECIES_ID, tree_species_id } });

      SeedCalculator sc;
      Date current_date = world->get_calendar().get_date();
      double sprout_time = sc.calculate_sprouting_seconds(current_date);
      vector<TileTransform>& tt_v = current_map->get_tile_transforms_ref()[sprout_time];

      tt_v.push_back(tt);

      // Planting a tree alters the world by making the map permanent, if it 
      // was not already so.
      if (!current_map->get_permanent() && current_map->get_map_type() == MapType::MAP_TYPE_OVERWORLD)
      {
        make_map_permanent(game, creature, current_map);
      }
    }
  }
  
  return planted;
}

void DropAction::make_map_permanent(Game& game, CreaturePtr creature, MapPtr current_map)
{
  if (current_map != nullptr)
  {
    current_map->set_permanent(true);
    string current_map_id = current_map->get_map_id();
    game.get_map_registry_ref().set_map(current_map_id, current_map);

    // Assumption: if a creature (realistically, the player) is in a
    // previously-random map on the overworld, it is connected to
    // the player's position on that map.
    MapPtr world_map = game.get_map_registry_ref().get_map(MapID::MAP_ID_WORLD_MAP);

    if (world_map != nullptr)
    {
      Coordinate location = world_map->get_location(creature->get_id());
      TilePtr creature_wm_tile = world_map->at(location);

      if (creature_wm_tile != nullptr)
      {
        creature_wm_tile->set_custom_map_id(current_map_id);
      }
    }
  }
}

// Dropping always has a base action cost of 1.
ActionCostValue DropAction::get_action_cost_value(CreaturePtr creature) const
{
  return 1;
}
