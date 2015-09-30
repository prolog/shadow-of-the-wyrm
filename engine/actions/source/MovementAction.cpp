#include "ActionTextKeys.hpp"
#include "CombatManager.hpp"
#include "Conversion.hpp"
#include "CoordUtils.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "DangerLevelCalculatorFactory.hpp"
#include "DigAction.hpp"
#include "FeatureAction.hpp"
#include "Game.hpp"
#include "ItemProperties.hpp"
#include "Log.hpp"
#include "MapCreatureGenerator.hpp"
#include "MapProperties.hpp"
#include "MapTypeQueryFactory.hpp"
#include "MessageManagerFactory.hpp"
#include "MovementAction.hpp"
#include "StairwayMovementAction.hpp"
#include "MapExitUtils.hpp"
#include "MapUtils.hpp"
#include "MovementTextKeys.hpp"
#include "MovementTypes.hpp"
#include "RNG.hpp"
#include "SkillManager.hpp"
#include "TerrainGeneratorFactory.hpp"
#include "TextKeys.hpp"
#include "TextMessages.hpp"
#include "TileDescriber.hpp"
#include "TileMovementConfirmation.hpp"
#include "WorldMapLocationTextKeys.hpp"

using namespace std;

MovementAction::MovementAction()
{
}

MovementAction::~MovementAction()
{
}

bool MovementAction::operator==(const MovementAction& mm) const
{
  return true;
}

ActionCostValue MovementAction::move(CreaturePtr creature, const Direction direction)
{
  ActionCostValue movement_success = 0;
  Game& game = Game::instance();

  if (creature)
  {
    MapPtr map = game.get_current_map();
    
    // Get the creature's location from the map
    Coordinate creature_location = map->get_location(creature->get_id());

    // Get the old tile
    TilePtr creatures_old_tile = map->at(creature_location.first, creature_location.second);

    // Is the proposed movement valid?
    // If it is not, and there is no map exit, and the creature is the player, display a message.
    if (!CoordUtils::is_valid_move(map->size(), creature_location, direction))
    {
      CurrentCreatureAbilities cca;

      // Leaving the map only actually works if the creature can move - isn't
      // spellbound, etc.
      if (cca.can_move(creature, true))
      {
        SkillManager sm;
        // Otherwise, move the creature, if:
        // - there are no hostile adjacent creatures
        // - there is at least one hostile adjacent creature, and a successful Escape check is made.
        if (!MapUtils::adjacent_hostile_creature_exists(creature->get_id(), map) || sm.check_skill(creature, SkillType::SKILL_GENERAL_ESCAPE))
        {
          movement_success = move_off_map(creature, map, creatures_old_tile);
        }
        else
        {
          IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());  
          movement_success = true;
          string cannot_escape = StringTable::get(MovementTextKeys::ACTION_MOVE_ADJACENT_HOSTILE_CREATURE);
          manager.add_new_message(cannot_escape);
          manager.send();
        }
      }
    }
    // Otherwise, it's a regular move within the current map.
    else
    {
      Coordinate new_coords = CoordUtils::get_new_coordinate(creature_location, direction);
      TilePtr creatures_new_tile = map->at(new_coords.first, new_coords.second);
      
      movement_success = move_within_map(creature, map, creatures_old_tile, creatures_new_tile, new_coords, direction);
    }

    // Update the loaded map details with the player's new coordinate,
    // assuming this is the player.
    if (creature->get_is_player())
    {
      Coordinate creature_location = map->get_location(creature->get_id());
      Game::instance().get_loaded_map_details_ref().update_engine_coord(creature_location);
    }
  }
  
  return movement_success;
}

ActionCostValue MovementAction::move_off_map(CreaturePtr creature, MapPtr map, TilePtr creatures_old_tile)
{
  ActionCostValue movement_success = 0;

  Game& game = Game::instance();
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());  
  MapExitPtr map_exit = map->get_map_exit();

  if (!MapUtils::can_exit_map(map_exit))
  {
    if (creature->get_is_player())
    { 
      string movement_message = StringTable::get(MovementTextKeys::ACTION_MOVE_OFF_WORLD_MAP);

      manager.add_new_message(movement_message);
      manager.send();
    }
  }
  else
  {
    if (creature->get_is_player())
    {
      string leave_area = TextMessages::get_confirmation_message(TextKeys::DECISION_LEAVE_AREA);
      game.display->confirm(leave_area);
      
      if (creature->get_decision_strategy()->get_confirmation())
      {
        handle_properties_and_move_to_new_map(creatures_old_tile, map, map_exit);
        movement_success = get_action_cost_value(creature);
      }
      
      // Regardless of whether we leave the map or not, clear the messages, so the text doesn't hang around.
      game.display->clear_messages();
    }
    // It's an NPC leaving the map - display the exit message.
    else
    {
      // Remove from tile and from map's creatures.
      creatures_old_tile->remove_creature();
      map->remove_creature(creature->get_id());
        
      string npc_exit_message = TextMessages::get_npc_escapes_message(StringTable::get(creature->get_description_sid()));
      manager.add_new_message(npc_exit_message);
      manager.send();
        
      movement_success = get_action_cost_value(creature);
    } 
  }
  
  return movement_success;
}

ActionCostValue MovementAction::move_within_map(CreaturePtr creature, MapPtr map, TilePtr creatures_old_tile, TilePtr creatures_new_tile, const Coordinate& new_coords, const Direction d)
{
  ActionCostValue movement_success = 0;
  bool creature_incorporeal = creature && creature->has_status(StatusIdentifiers::STATUS_ID_INCORPOREAL);
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

  if (creatures_new_tile)
  {
    // Only try to handle a blocking terrain feature if the creature is corporeal.
    // Spirits don't care about closed doors, etc!
    if (MapUtils::is_blocking_feature_present(creatures_new_tile) && !creature_incorporeal)
    {
      // If there is a feature, handle it, prompting the creature for confirmation
      // if necessary.
      FeatureAction fa;
      bool handled = fa.handle(creatures_new_tile, creatures_new_tile->get_feature(), creatures_old_tile->get_creature(), creatures_new_tile->get_creature() != nullptr);

      // Did the handling do anything?
      if (!handled)
      {
        string blocked = StringTable::get(ActionTextKeys::ACTION_MOVEMENT_BLOCKED);
        manager.add_new_message(blocked);
        manager.send();
      }
      
      // Regardless of whether the handling did anything, it still costs
      // an action.
      movement_success = 1;
    }
    else if (MapUtils::is_creature_present(creatures_new_tile))
    {
      movement_success = handle_movement_into_occupied_tile(creature, creatures_new_tile, map, new_coords, d);
    }
    else if (creatures_new_tile->get_is_blocking(creature) && !creature_incorporeal)
    {
      // Can the creature dig through the tile?
      ItemPtr wielded = creature->get_equipment().get_item(EquipmentWornLocation::EQUIPMENT_WORN_WIELDED);

      if (wielded != nullptr)
      {
        string dig_hardness = wielded->get_additional_property(ItemProperties::ITEM_PROPERTIES_DIG_HARDNESS);

        if (!dig_hardness.empty())
        {
          if (String::to_int(dig_hardness) >= creatures_new_tile->get_hardness())
          {
            DigAction da;
            movement_success = da.dig_through(creature, wielded, map, creatures_new_tile, d);
          }
          else
          {
            manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_DIG_TOO_HARD));
            manager.send();
          }
        }
      }
      else
      {
        // Can't move into the tile.  It's not a blocking feature (handled above),
        // nor is it a creature (ditto), nor can the creature dig through it, so 
        // most likely, it's impassable terrain - stone, etc.
        //
        // Do nothing.  Don't advance the turn.
        movement_success = 0;
      }
    }
    else
    {
      CurrentCreatureAbilities cca;

      if (cca.can_move(creature, true))
      {
        // JCD FIXME: Might want to update this once traps are done.
        if (confirm_move_to_tile_if_necessary(creature, creatures_old_tile, creatures_new_tile))
        {
          // Update the map info
          MapUtils::add_or_update_location(map, creature, new_coords, creatures_old_tile);
          TilePtr new_tile = MapUtils::get_tile_for_creature(map, creature);
        
          add_tile_related_messages(creature, new_tile);
          movement_success = get_action_cost_value(creature);
        }

        if (creatures_new_tile->has_feature())
        {
          FeaturePtr feature = creatures_new_tile->get_feature();

          // Some features, such as traps, are applied when moving into a tile.
          if (feature->apply_on_movement(creature))
          {
            // Apply the feature, now that the creature has moved into
            // the tile.
            FeatureAction fa;
            fa.handle(creatures_new_tile, feature, creature, true);
          }
        }
      }
    }
  }
  
  return movement_success;
}

// Handle movement into an occupied tile.  First, check to see whether the
// creature will attack the occupying creature.  If so, attack the creature.
ActionCostValue MovementAction::handle_movement_into_occupied_tile(CreaturePtr creature, TilePtr creatures_new_tile, MapPtr map, const Coordinate& new_coords, const Direction d)
{
  ActionCostValue movement_success = 0;

  // Do the necessary checks here to determine whether to attack...
  CreaturePtr adjacent_creature = creatures_new_tile->get_creature();
      
  // If the creature in the new tile isn't hostile to the creature in the
  // current tile, prompt to see whether the moving creature wants to
  // attack, assuming the moving creature isn't stunned.
  if (!adjacent_creature->get_decision_strategy()->get_threats_ref().has_threat(creature->get_id()).first)
  {
    if (creature->get_is_player())
    {
      MovementThroughTileType mtt = MovementThroughTileType::MOVEMENT_ATTACK;
      
      CurrentCreatureAbilities cca;

      // Only allow the creature to select whether to switch/attack if the creature
      // is not stunned - if the creature is stunned, then they should stagger
      // into the other creature and attack indiscriminately.
      if (cca.can_select_movement_direction(creature))
      {
        mtt = get_movement_through_tile_type(creature, adjacent_creature, creatures_new_tile);
      }

      switch (mtt)
      {
        case MovementThroughTileType::MOVEMENT_ATTACK:
        {
          // Fall through to the end of the function where we'll attack.
          break;
        }
        case MovementThroughTileType::MOVEMENT_SQUEEZE:
        {
          TilePtr current_tile = MapUtils::get_tile_for_creature(map, creature);
          Coordinate potential_squeeze_coords = CoordUtils::get_new_coordinate(new_coords, d, 1);
          TilePtr potential_squeeze_tile = map->at(potential_squeeze_coords);
          bool confirm = (MapUtils::can_squeeze_by(map, creature, new_coords, d) 
                      && confirm_move_to_tile_if_necessary(creature, current_tile, potential_squeeze_tile));

          if (confirm)
          {
            MapUtils::squeeze_by(map, creature, new_coords, d);

            // Squeezing past should cost roughly twice as much as a single
            // move, since two squares are being traversed in a turn.
            movement_success = creature->get_speed().get_current();
          }
          else
          {
            // Couldn't squeeze by, either due a monster being there, no
            // tile, the tile not allowing a creature on it, etc.
            IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
            manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_SQUEEZE_FAILURE));
            manager.send();
          }

          return movement_success;
        }
        case MovementThroughTileType::MOVEMENT_SWITCH:
        {
          MapUtils::swap_places(map, creature, adjacent_creature);

          movement_success = 1;
          return movement_success;
        }
        default:
        case MovementThroughTileType::MOVEMENT_NONE:
        {
          return movement_success;
        }
      }
    }
  }

  if (adjacent_creature != nullptr)
  {
    CombatManager cm;
    movement_success = cm.attack(creature, adjacent_creature);
  }

  return movement_success;
}

// Figure out what the creature wants to do in terms of getting through the occupied tile.
MovementThroughTileType MovementAction::get_movement_through_tile_type(CreaturePtr creature, CreaturePtr adjacent_creature, TilePtr creatures_new_tile)
{
  MovementThroughTileType mtt = MovementThroughTileType::MOVEMENT_ATTACK;

  // When prompting for switching, we need to consider that immobile creatures don't want
  // to move, and the moving creature will need to find another way around.
  bool adjacent_creature_can_move = adjacent_creature->get_decision_strategy()->can_move();

  // Ensure the creature can actually enter the tile before prompting the switch.  This is
  // almost always the case, but if the nearby creature is incorporeal and the switching
  // creature is not, no prompt should occur.
  bool creature_can_enter_adjacent_tile = false;
  
  if (creatures_new_tile)
  {
    creature_can_enter_adjacent_tile = !creatures_new_tile->get_is_blocking_ignore_present_creature(creature);
  }

  // Maybe the creature just wants to switch?
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

  if (adjacent_creature_can_move && creature_can_enter_adjacent_tile)
  {
    manager.add_new_confirmation_message(TextMessages::get_confirmation_message(TextKeys::DECISION_SWITCH_FRIENDLY_CREATURE));
    bool switch_places = creature->get_decision_strategy()->get_confirmation();

    if (switch_places)
    {
      mtt = MovementThroughTileType::MOVEMENT_SWITCH;
    }
  }
  else
  {
    if (creature_can_enter_adjacent_tile)
    { 
      manager.add_new_confirmation_message(TextMessages::get_confirmation_message(TextKeys::DECISION_SQUEEZE_FRIENDLY_CREATURE));
      bool squeeze_past = creature->get_decision_strategy()->get_confirmation();

      if (squeeze_past)
      {
        mtt = MovementThroughTileType::MOVEMENT_SQUEEZE;
      }
    }
  }

  // If we need to switch, don't prompt to attack.
  if (mtt == MovementThroughTileType::MOVEMENT_ATTACK)
  {
    manager.add_new_confirmation_message(TextMessages::get_confirmation_message(TextKeys::DECISION_ATTACK_FRIENDLY_CREATURE));
    bool attack = creature->get_decision_strategy()->get_confirmation();

    if (!attack)
    {
      mtt = MovementThroughTileType::MOVEMENT_NONE;
    }
    else
    {
      // Not all deities approve of attacking friendlies...
      Game::instance().get_deity_action_manager_ref().notify_action(creature, CreatureActionKeys::ACTION_ATTACK_FRIENDLY);
    }
  }

  return mtt;
}

// Generate and move to the new map using the tile type and subtype present
// on the tile, rather than a source like the map exit.
ActionCostValue MovementAction::generate_and_move_to_new_map(CreaturePtr creature, MapPtr map, TilePtr tile, const int depth_increment)
{
  ActionCostValue action_cost_value = 0;

  if (creature && tile && map)
  {
    return generate_and_move_to_new_map(creature, map, tile, tile->get_tile_type(), tile->get_tile_subtype(), depth_increment);
  }

  return action_cost_value;
}

// General version that can handle tile type/subtype from any source - the tile
// itself, a map exit, etc.
ActionCostValue MovementAction::generate_and_move_to_new_map(CreaturePtr creature, MapPtr map, TilePtr tile, const TileType tile_type, const TileType tile_subtype, const int depth_increment)
{
  ActionCostValue action_cost_value = 0;

  // If permanent, set the previous map ID, so that if there are staircases, etc., the
  // link to the current map can be maintained.
  if (map->get_permanent())
  {
    tile->set_additional_property(TileProperties::TILE_PROPERTY_PREVIOUS_MAP_ID, map->get_map_id());
  }

  GeneratorPtr generator = TerrainGeneratorFactory::create_generator(tile, map->get_map_id(), tile_type, tile_subtype);

  // Ensure that the overworld map ID is always available to the generator!
  map->get_map_type() == MapType::MAP_TYPE_WORLD ? generator->set_additional_property(TileProperties::TILE_PROPERTY_ORIGINAL_MAP_ID, map->get_map_id())
    : generator->set_additional_property(TileProperties::TILE_PROPERTY_ORIGINAL_MAP_ID, tile->get_additional_property(TileProperties::TILE_PROPERTY_ORIGINAL_MAP_ID));

  Game& game = Game::instance();
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

  if (generator)
  {
    MapPtr new_map;

    // If a custom map ID is specified, use that:
    string custom_map_id = tile->get_custom_map_id();

    if (!custom_map_id.empty())
    {
      new_map = game.get_map_registry_ref().get_map(custom_map_id);
    }
    else
    {
      // Otherwise, if there's no custom map ID, generate the map:
      IDangerLevelCalculatorPtr calc = DangerLevelCalculatorFactory::create_danger_level_calculator(map->get_map_type());
      uint danger_level = calc->calculate(map);

      Dimensions dim = map->size();
      Depth& depth = dim.depth_ref();
      IMapTypeQueryPtr mtq = MapTypeQueryFactory::create_map_type_query(generator->get_map_type());

      // Check to see if the depth should be updated.  For things like fields
      // and forests, it shouldn't, but for dungeons/caverns/etc., it should.
      if (mtq && mtq->should_update_depth())
      {
        // If the tile has a set depth associated with it, then use that.
        // Otherwise, use the specified depth increment.
        string initial_depth = tile->get_additional_property(UnderworldProperties::UNDERWORLD_STRUCTURE_DEPTH);
        if (!initial_depth.empty())
        {
          int tile_initial_depth = String::to_int(initial_depth);
          depth.set_current(tile_initial_depth);
        }
        else
        {
          depth.set_current(depth.get_current() + depth_increment);
        }

        if (depth_increment > 0) 
        {
          generator->set_additional_property(TileProperties::TILE_PROPERTY_DEPTH_INCREMENT, std::to_string(depth_increment));
        }
      }

      new_map = generator->generate_and_initialize(danger_level, depth);

      if (new_map->get_permanent())
      {
        // If it's a permanent map, set up a link between
        // the tile and the new map.
        tile->set_custom_map_id(new_map->get_map_id());
      }

      if (new_map->get_map_type() != MapType::MAP_TYPE_WORLD)
      {
        // Set the danger level appropriately, using the OLD MAP's map type.
        int new_danger = calc->calculate(map, new_map);
        new_map->set_danger(new_danger);

        // Now that the danger level's been calculated, generate the creatures
        // and items on the new map.
        generator->create_entities(new_map, new_danger);
        tile->remove_additional_property(MapProperties::MAP_PROPERTIES_INITIAL_CREATURES);
      }
    }
                
    // - Set the map's MapExitPtr to point to the previous map.
    //   But only if it's an overworld map.
    if (new_map->get_map_type() == MapType::MAP_TYPE_OVERWORLD)
    {
      MapExitUtils::add_exit_to_map(new_map, map->get_map_id());
    }
                
    // If the map has a last known player location (e.g., up staircase),
    // use that.  Otherwise, start at the first open location.
    string player_loc = WorldMapLocationTextKeys::CURRENT_PLAYER_LOCATION;
    Coordinate starting_coords;
    
    TilePtr new_creature_tile = new_map->at(starting_coords);

    // If we're moving on to an existing map, handle any tile properties
    // that may be present.  Don't worry about this when we're moving
    // to a brand-new map, as tile properties will be automatically 
    // handled during map generation, and will be removed after creating
    // items and creatures.
    handle_properties_and_move_to_new_map(tile, map, new_map);
                
    add_initial_map_messages(creature, new_map, tile_type);                
    add_tile_related_messages(creature, new_creature_tile);

    action_cost_value = get_action_cost_value(creature);
  }

  return action_cost_value;
}

void MovementAction::add_initial_map_messages(CreaturePtr creature, MapPtr map, const TileType tile_type)
{
  // Add a message about the terrain type.
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
  manager.add_new_message(TextMessages::get_area_entrance_message_given_terrain_type(tile_type));

  // Add any messages for special features.
  string feature_message_sid_csv = map->get_property(MapProperties::MAP_PROPERTIES_FEATURE_ENTRY_TEXT_SIDS);

  if (!feature_message_sid_csv.empty())
  {
    vector<string> feature_sids = String::create_string_vector_from_csv_string(feature_message_sid_csv);

    for (const string& feature_sid : feature_sids)
    {
      manager.add_new_message(StringTable::get(feature_sid));
    }

    // Remove the properties so that they are no longer present when the creature
    // enters the map the second time.
    map->remove_property(MapProperties::MAP_PROPERTIES_FEATURE_ENTRY_TEXT_SIDS);
  }

  manager.send();
}

// Confirm if moving to a potentially dangerous tile.
bool MovementAction::confirm_move_to_tile_if_necessary(CreaturePtr creature, TilePtr creatures_old_tile, TilePtr creatures_new_tile)
{
  TileMovementConfirmation tmc;
  pair<bool, string> details = tmc.get_confirmation_details(creature, creatures_old_tile, creatures_new_tile);
  bool needs_confirmation = details.first;

  if (needs_confirmation)
  {
    bool confirmation = false;
    IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
    
    if (creature->get_is_player())
    { 
      manager.add_new_confirmation_message(details.second);
      
      confirmation = (creature->get_decision_strategy()->get_confirmation());
      manager.clear_if_necessary();
    }

    return confirmation;      
  }
  
  return true;  
}

ActionCostValue MovementAction::handle_properties_and_move_to_new_map(TilePtr current_tile, MapPtr old_map, MapPtr new_map)
{
  ActionCostValue acv = 0;
  Game& game = Game::instance();

  if (new_map)
  {
    // The map may have a set of creatures defined (e.g., a custom map with a
    // list of creatures set programmatically by a script).  Generate these,
    // if present.
    if (current_tile->has_additional_property(MapProperties::MAP_PROPERTIES_INITIAL_CREATURES))
    {
      MapCreatureGenerator mcg;
      mcg.generate_initial_set_creatures(new_map, current_tile->get_additional_properties());

      current_tile->remove_additional_property(MapProperties::MAP_PROPERTIES_INITIAL_CREATURES);
    }

    move_to_new_map(current_tile, old_map, new_map);
    acv = get_action_cost_value(nullptr);
  }

  return acv;
}

void MovementAction::move_to_new_map(TilePtr current_tile, MapPtr old_map, MapPtr new_map)
{
  Game& game = Game::instance();
  
  if (new_map)
  {
    // Remove the creature from its present tile, and from the temporary
    // vector of creatures as well.
    CreaturePtr current_creature = current_tile->get_creature();
    MapUtils::remove_creature(old_map, current_creature);

    MapUtils::place_creature_on_previous_or_first_available_location(new_map, current_creature, current_creature->get_id());

    // Set the new map to be loaded in the next iteration of the game loop.
    game.set_current_map(new_map);
    game.reload_map();    
  }
}

void MovementAction::handle_properties_and_move_to_new_map(TilePtr old_tile, MapPtr old_map, MapExitPtr map_exit)
{
  Game& game = Game::instance();
  
  if (map_exit)
  {
    if (map_exit->is_using_map_id())
    {
      string new_map_id = map_exit->get_map_id();
      MapPtr new_map = game.map_registry.get_map(new_map_id);
      
      handle_properties_and_move_to_new_map(old_tile, old_map, new_map);
    }
    else
    {
      // A random terrain map.
      // JCD FIXME fill this in later.
    }
  }
}

// Ascend, if the creature can move.
ActionCostValue MovementAction::ascend(CreaturePtr creature)
{
  CurrentCreatureAbilities cca;

  if (cca.can_move(creature, true))
  {
    StairwayMovementAction smm;
    return smm.ascend(creature, this);
  }
  else
  {
    return 0;
  }
}

// Descend, if the creature can move.  Or, if the creature has the appropriate
// item, dig.
ActionCostValue MovementAction::descend(CreaturePtr creature)
{
  CurrentCreatureAbilities cca;

  if (cca.can_move(creature, true))
  {
    StairwayMovementAction smm;
    return smm.descend(creature, this);
  }
  else
  {
    return 0;
  }
}

// Add any messages after moving to a particular tile:
// - Should a message be displayed about the tile automatically? (staircases, etc)
//       If so, add it.
// - Are there any items on the tile?
//       If so, add the appropriate message.
void MovementAction::add_tile_related_messages(const CreaturePtr& creature, TilePtr tile)
{
  bool tile_message_added = add_message_about_tile_if_necessary(creature, tile);
  bool item_message_added = add_message_about_items_on_tile_if_necessary(creature, tile);

  if (tile_message_added || item_message_added)
  {
    IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
    manager.send();
  }
}

// Add a message about the tile if necessary.
bool MovementAction::add_message_about_tile_if_necessary(const CreaturePtr& creature, TilePtr tile)
{
  bool msg_added = false;

  if (creature && tile && creature->get_is_player())
  {
    if (tile->display_description_on_arrival() || tile->has_extra_description())
    {
      IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
      TileDescriber td(tile);
      manager.add_new_message(td.describe());
      msg_added = true;
    }
  }

  return msg_added;
}

// Add a message if the creature is the player, and if there are items on
// the tile.
bool MovementAction::add_message_about_items_on_tile_if_necessary(const CreaturePtr& creature, TilePtr tile)
{
  bool msg_added = false;

  if (creature && creature->get_is_player())
  {
    IInventoryPtr tile_items = tile->get_items();
    
    if (!tile_items->empty())
    {
      string item_message;
      
      // One item
      if (tile_items->size() == 1)
      {
        ItemPtr item_on_tile = tile_items->at(0);
        
        if (item_on_tile)
        {
          CurrentCreatureAbilities cca;
          item_message = TextMessages::get_item_on_ground_description_message(!cca.can_see(creature), item_on_tile);
        }
      }
      // Multiple items
      else
      {
        item_message = StringTable::get(MovementTextKeys::ITEMS_ON_TILE);
      }
      
      // Send the message
      if (!item_message.empty())
      {
        IMessageManager& manager = MessageManagerFactory::instance(creature, true);
        manager.add_new_message(item_message);
        msg_added = true;
      }
    }
  }

  return msg_added;
}

ActionCostValue MovementAction::get_action_cost_value(CreaturePtr creature) const
{
  ActionCostValue acv = 1;

  if (creature != nullptr)
  {
    // When timewalking, movement is free.
    if (creature->has_status(StatusIdentifiers::STATUS_ID_TIMEWALK))
    {
      acv = 0;
    }
    else
    {
      int stumble_chance = static_cast<int>(creature->get_blood().get_blood_alcohol_content() * 100);

      if (RNG::percent_chance(stumble_chance))
      {
        // Add a message about stumbling.
        IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
        manager.add_new_message(ActionTextKeys::get_stumble_message(creature->get_description_sid(), creature->get_is_player()));
        manager.send();
        return 15;
      }
    }
  }

  return acv;
}

// If the creature is drunk, it may stumble, causing it to move slower 
// than normal.
ActionCostValue MovementAction::get_stumble_action_cost_value() const
{
  return 15;
}