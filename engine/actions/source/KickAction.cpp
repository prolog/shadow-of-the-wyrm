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

ActionCostValue KickAction::kick(CreaturePtr creature, const Direction kick_dir)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION;

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
        acv = kick_on_regular_map(creature, current_map, kick_dir);
      }
    }
  }
  
  return acv;
}

// Kicking on the world map doesn't do anything, but should display a message
// nonetheless.
ActionCostValue KickAction::kick_on_world_map(CreaturePtr creature, MapPtr current_map)
{
  if (creature != nullptr && creature->get_is_player() && current_map != nullptr)
  {
    IMessageManager& manager = MMF::instance();

    string kick_msg = StringTable::get(ActionTextKeys::ACTION_KICK_WORLD_MAP);
    manager.add_new_message(kick_msg);
    manager.send();
  }

  return 0;
}

// Handle kicking on a regular map: prompt the creature for a direction, then go from there.
ActionCostValue KickAction::kick_on_regular_map(CreaturePtr creature, MapPtr current_map, const Direction kick_dir)
{
  if (creature)
  {
    // If the creature is the player, get the kicking direction.
    if (creature->get_is_player())
    {
      IMessageManager& manager = MMF::instance();
      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_GET_DIRECTION));
      manager.send();
    }

    Direction d = kick_dir;

    if (d == Direction::DIRECTION_NULL)
    {
      // Try to get a direction.
      //
      // If automatic movement is engaged, use the direction that has already been
      // selected.  Otherwise, prompt the creature.
      CommandFactoryPtr command_factory = std::make_unique<CommandFactory>();
      KeyboardCommandMapPtr kb_command_map = std::make_unique<KeyboardCommandMap>();
      CommandPtr base_command = creature->get_decision_strategy()->get_nonmap_decision(false, creature->get_id(), command_factory.get(), kb_command_map.get(), 0, true);

      if (base_command)
      {
        DirectionalCommand* dcommand;
        dcommand = dynamic_cast<DirectionalCommand*>(base_command.get());

        if (dcommand)
        {
          d = dcommand->get_direction();
        }
      }
    }

    return kick_in_direction(creature, current_map, d);
  }

  return 0;
}

// Kick in a particular direction on a regular map.
ActionCostValue KickAction::kick_in_direction(CreaturePtr creature, MapPtr current_map, const Direction direction)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION;

  if (creature && current_map)
  {
    TilePtr k_tile = MapUtils::get_adjacent_tile(current_map, creature, direction);
    Coordinate k_coord = CoordUtils::get_new_coordinate(current_map->get_location(creature->get_id()), direction);

    IMessageManager& manager = MMF::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());

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
        acv = kick_item(creature, current_map, k_tile, new_tile);
      }
      // No creature to kick.  Is there a feature?
      else if (k_tile->has_feature())
      {
        if (!creature->has_status(StatusIdentifiers::STATUS_ID_INCORPOREAL))
        {
          acv = kick_feature(creature, current_map, k_tile, k_coord, k_tile->get_feature());
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
        IMessageManager& man = MMF::instance();
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
      IMessageManager& manager = MMF::instance(MessageTransmit::SELF, kicking_creature, kicking_creature && kicking_creature->get_is_player());
      manager.add_new_confirmation_message(TextMessages::get_confirmation_message(TextKeys::DECISION_ATTACK_FRIENDLY_CREATURE));
      attack = kicking_creature->get_decision_strategy()->get_confirmation();
    }

    if (attack)
    {
      // Do a kicking attack (force an unarmed, physical attack)
      CombatManager cm;
      acv = cm.attack(kicking_creature, kicked_creature, AttackType::ATTACK_TYPE_MELEE_TERTIARY_UNARMED, AttackSequenceType::ATTACK_SEQUENCE_INITIAL, true);
    }
  }

  return acv;
}

ActionCostValue KickAction::kick_feature(CreaturePtr creature, MapPtr current_map, TilePtr kick_tile, const Coordinate& kick_coord, FeaturePtr kick_feature)
{
  if (creature && current_map && kick_tile && kick_feature)
  {
    FeatureManipulatorPtr manipulator = IFeatureManipulatorFactory::create_manipulator(kick_feature);

    // Add a message about kicking the feature, whether it can be seen,
    // or not.
    IMessageManager& manager = MMF::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());
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
      manipulator->kick(creature, current_map, kick_tile, kick_coord, kick_feature);
    }
  }

  return get_action_cost_value(creature);
}

// Kick an item in the given tile.  Kicking moves the top item over by one
// tile, assuming that's a legal move (the new tile isn't null, etc).
ActionCostValue KickAction::kick_item(CreaturePtr creature, MapPtr current_map, TilePtr kick_tile, TilePtr new_tile)
{
  ActionCostValue acv = get_action_cost_value(creature);

  if (creature && current_map && kick_tile && !kick_tile->get_items()->empty())
  {
    // First, get the item.
    ItemPtr item = kick_tile->get_items()->at(0);

    CurrentCreatureAbilities cca;
    bool creature_blind = creature->get_is_player() && !cca.can_see(creature);

    // Add a message about kicking the item.
    ItemDescriberPtr describer = ItemDescriberFactory::create_item_describer(creature_blind, item);
    string object_desc = describer->describe_usage();
    string kick_msg = ActionTextKeys::get_kick_object_message(creature->get_description_sid(), object_desc, creature->get_is_player());

    // Kicking an unpaid item in a shop angers the shopkeeper.
    if (item->get_unpaid())
    {
      Coordinate kick_coord = current_map->get_location(creature->get_id());
      MapUtils::anger_shopkeeper_if_necessary(kick_coord, current_map, creature);
    }

    // If the new tile actually exists, and is not blocking (a wall, etc)
    // then add the item to its inventory and remove the item from its 
    // original tile.
    if (new_tile && !new_tile->get_is_blocking_for_item(item))
    {
      IMessageManager& manager = MMF::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());
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
  IMessageManager& manager = MMF::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());

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

ActionCostValue KickAction::get_action_cost_value(CreaturePtr /* creature */) const
{
  return 1;
}

