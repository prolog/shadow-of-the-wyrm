#include "ActionTextKeys.hpp"
#include "CombatManager.hpp"
#include "Commands.hpp"
#include "CoordUtils.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "Game.hpp"
#include "FeatureDescriberFactory.hpp"
#include "IFeatureManipulatorFactory.hpp"
#include "ItemDescriberFactory.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "TextKeys.hpp"
#include "TextMessages.hpp"
#include "KickAction.hpp"

using std::string;

KickAction::KickAction()
{
}

ActionCostValue KickAction::kick(CreaturePtr creature)
{
  ActionCostValue acv = 0;

  if (creature)
  {
    CurrentCreatureAbilities cca;

    string kick_msg;
    
    if (cca.can_move(creature))
    {
      Game& game = Game::instance();
      MapPtr current_map = game.get_current_map();
      MapType map_type = current_map->get_map_type();

      if (map_type == MapType::MAP_TYPE_WORLD)
      {
        acv = kick_on_world_map(creature, current_map);
      }
      else
      {
        acv = kick_on_regular_map(creature, current_map);
      }
    }
  }
  
  return acv;
}

// Kicking on the world map doesn't do anything, but should display a message
// nonetheless.
ActionCostValue KickAction::kick_on_world_map(CreaturePtr creature, MapPtr current_map)
{
  if (creature && creature->get_is_player())
  {
    IMessageManager& manager = MM::instance();

    string kick_msg = StringTable::get(ActionTextKeys::ACTION_KICK_WORLD_MAP);
    manager.add_new_message(kick_msg);
    manager.send();
  }

  return 0;
}

// Handle kicking on a regular map: prompt the creature for a direction, then go from there.
ActionCostValue KickAction::kick_on_regular_map(CreaturePtr creature, MapPtr current_map)
{
  if (creature)
  {

    // If the creature is the player, get the kicking direction.
    if (creature->get_is_player())
    {
      IMessageManager& manager = MM::instance();
      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_GET_DIRECTION));
      manager.send();
    }

    // Try to get a direction.
    //
    // If automatic movement is engaged, use the direction that has already been
    // selected.  Otherwise, prompt the creature.
    CommandFactoryPtr command_factory = std::make_shared<CommandFactory>();
    KeyboardCommandMapPtr kb_command_map = std::make_shared<KeyboardCommandMap>();
    CommandPtr base_command = creature->get_decision_strategy()->get_nonmap_decision(false, creature->get_id(), command_factory, kb_command_map, 0);

    if (base_command)
    {
      std::shared_ptr<DirectionalCommand> dcommand;
      dcommand = std::dynamic_pointer_cast<DirectionalCommand>(base_command);

      if (dcommand)
      {
        return kick_in_direction(creature, current_map, dcommand->get_direction());
      }
    }
  }

  return 0;
}

// Kick in a particular direction on a regular map.
ActionCostValue KickAction::kick_in_direction(CreaturePtr creature, MapPtr current_map, const Direction direction)
{
  ActionCostValue acv = 0;

  if (creature && current_map)
  {
    TilePtr k_tile = MapUtils::get_adjacent_tile(current_map, creature, direction);
    IMessageManager& manager = MM::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());

    if (k_tile)
    {
      acv = get_action_cost_value(creature);

      manager.add_new_message(ActionTextKeys::get_kick_message(creature->get_description_sid(), creature->get_is_player()));
      manager.send(); // Send immediately so that things don't look weird if interrupted by a confirmation.

      // Is there a creature?
      if (k_tile->has_creature())
      {
        CreaturePtr kicked_creature = k_tile->get_creature();
        
        acv = kick_creature(creature, kicked_creature);
      }
      // Are there items present?
      else if (!k_tile->get_items()->empty())
      {
        // Kick the top item in the pile in the given direction.
        TilePtr new_tile = MapUtils::get_adjacent_tile(current_map, creature, direction, 2);
        acv = kick_item(creature, k_tile, new_tile, direction);
      }
      // No creature to kick.  Is there a feature?
      else if (k_tile->has_feature())
      {
        if (!creature->has_status(StatusIdentifiers::STATUS_ID_INCORPOREAL))
        {
          acv = kick_feature(creature, current_map, k_tile, k_tile->get_feature());
        }
        else
        {
          manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_KICK_PASSES_THROUGH));
        }
      }
      else
      {
        acv = kick_tile(creature, k_tile);
      }
    }
    else
    {
      if (creature->get_is_player())
      {
        IMessageManager& man = MM::instance();
        man.add_new_message(StringTable::get(ActionTextKeys::ACTION_KICK_NOTHING_TO_KICK_AT));
        man.send();
      }
    }

    manager.send();
  }

  return acv;
}

ActionCostValue KickAction::kick_creature(CreaturePtr kicking_creature, CreaturePtr kicked_creature)
{
  ActionCostValue acv = get_action_cost_value(kicking_creature);
  bool attack = true;

  if (kicking_creature && kicked_creature)
  {
    // Check to see if the creature is friendly - if so, prompt for
    // confirmation.
    if (!kicked_creature->get_decision_strategy()->get_threats_ref().has_threat(kicking_creature->get_id()).first)
    {
      IMessageManager& manager = MM::instance(MessageTransmit::FOV, kicking_creature, kicking_creature && kicking_creature->get_is_player());
      manager.add_new_confirmation_message(TextMessages::get_confirmation_message(TextKeys::DECISION_ATTACK_FRIENDLY_CREATURE));
      attack = kicking_creature->get_decision_strategy()->get_confirmation();
    }

    if (attack)
    {
      // Do a kicking attack (force an unarmed, physical attack)
      CombatManager cm;
      acv = cm.attack(kicking_creature, kicked_creature, AttackType::ATTACK_TYPE_MELEE_TERTIARY_UNARMED, true);
    }
  }

  return acv;
}

ActionCostValue KickAction::kick_feature(CreaturePtr creature, MapPtr current_map, TilePtr kick_tile, FeaturePtr kick_feature)
{
  if (creature && current_map && kick_tile && kick_feature)
  {
    IFeatureManipulatorPtr manipulator = IFeatureManipulatorFactory::create_manipulator(kick_feature);

    // Add a message about kicking the feature, whether it can be seen,
    // or not.
    IMessageManager& manager = MM::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());
    CurrentCreatureAbilities cca;
    bool creature_blind = creature->get_is_player() && !cca.can_see(creature);
    FeatureDescriberPtr fd = FeatureDescriberFactory::create_feature_describer(creature_blind, kick_feature);

    // Might be the feature, or might be "something".
    string object_desc = fd->describe();
    string kick_msg = ActionTextKeys::get_kick_object_message(creature->get_description_sid(), object_desc, creature->get_is_player());

    manager.add_new_message(kick_msg);

    if (manipulator)
    {
      // Do any specific logic required due to the kicking.
      manipulator->kick(creature, current_map, kick_tile, kick_feature);
    }
  }

  return get_action_cost_value(creature);
}

// Kick an item in the given tile.  Kicking moves the top item over by one
// tile, assuming that's a legal move (the new tile isn't null, etc).
ActionCostValue KickAction::kick_item(CreaturePtr creature, TilePtr kick_tile, TilePtr new_tile, const Direction direction)
{
  ActionCostValue acv = get_action_cost_value(creature);

  if (creature && kick_tile && !kick_tile->get_items()->empty())
  {
    // First, get the item.
    ItemPtr item = kick_tile->get_items()->at(0);

    CurrentCreatureAbilities cca;
    bool creature_blind = creature->get_is_player() && !cca.can_see(creature);

    // Add a message about kicking the item.
    ItemDescriberPtr describer = ItemDescriberFactory::create_item_describer(creature_blind, item);
    string object_desc = describer->describe_usage();
    string kick_msg = ActionTextKeys::get_kick_object_message(creature->get_description_sid(), object_desc, creature->get_is_player());

    // If the new tile actually exists, and is not blocking (a wall, etc)
    // then add the item to its inventory and remove the item from its 
    // original tile.
    if (new_tile && !new_tile->get_is_blocking_for_item(item))
    {
      IMessageManager& manager = MM::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());
      manager.add_new_message(kick_msg);

      kick_tile->get_items()->remove(item->get_id());
      new_tile->get_items()->add(item);
    }
  }

  return acv;
}

// Kick at a particular tile, being sure to handle the incorporeal case.
ActionCostValue KickAction::kick_tile(CreaturePtr creature, TilePtr kick_tile)
{
  IMessageManager& manager = MM::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());

  // Creatures can't kick solid tiles, unless they're incorporeal, or can
  // otherwise pass through such things.
  if (kick_tile->get_movement_multiplier() == 0)
  {
    if (!creature->has_status(StatusIdentifiers::STATUS_ID_INCORPOREAL))
    {
      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_KICK_SOLID_TILE));
    }
    else
    {
      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_KICK_PASSES_THROUGH));
    }
  }
  // Kicking a water tile generates a message
  else if (kick_tile->get_tile_super_type() == TileSuperType::TILE_SUPER_TYPE_WATER)
  {
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_KICK_WATER_TILE));
  }
  else
  {
    // ...
  }

  ActionCostValue acv = get_action_cost_value(creature);
  return acv;
}

ActionCostValue KickAction::get_action_cost_value(CreaturePtr creature) const
{
  return 1;
}

