#include <future>
#include <thread>
#include "ActionTextKeys.hpp"
#include "CombatManager.hpp"
#include "Conversion.hpp"
#include "CoordUtils.hpp"
#include "CreatureProperties.hpp"
#include "CreatureUtils.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "DangerLevelCalculatorFactory.hpp"
#include "DangerLevelProperties.hpp"
#include "DecisionStrategyProperties.hpp"
#include "DigAction.hpp"
#include "DirectionUtils.hpp"
#include "FeatureAction.hpp"
#include "ForagablesCalculator.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "ItemProperties.hpp"
#include "Log.hpp"
#include "MapCreatureGenerator.hpp"
#include "MapExitUtils.hpp"
#include "MapItemGenerator.hpp"
#include "MapProperties.hpp"
#include "MapScript.hpp"
#include "MapTypeQueryFactory.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "MovementAction.hpp"
#include "MovementTextKeys.hpp"
#include "MovementTypes.hpp"
#include "RNG.hpp"
#include "SearchAction.hpp"
#include "Setting.hpp"
#include "SkillManager.hpp"
#include "SkillsCalculator.hpp"
#include "SoundEffectID.hpp"
#include "StairwayMovementAction.hpp"
#include "TerrainGeneratorFactory.hpp"
#include "TextKeys.hpp"
#include "TextMessages.hpp"
#include "TileMovementConfirmation.hpp"
#include "TileUtils.hpp"
#include "WorldWeatherUpdater.hpp"
#include "WorldMapLocationTextKeys.hpp"

using namespace std;

const int MovementAction::BASE_ASCEND_DESCEND_CHANCE = 35;

MovementAction::MovementAction()
{
}

MovementAction::~MovementAction()
{
}

bool MovementAction::operator==(const MovementAction& /* mm */) const
{
  return true;
}

ActionCostValue MovementAction::move(CreaturePtr creature, const Direction direction, const bool confirm_if_dangerous)
{
  ActionCostValue movement_acv = ActionCostConstants::NO_ACTION;
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
          movement_acv = move_off_map(creature, map, creatures_old_tile, direction);
        }
        else
        {
          add_cannot_escape_message(creature);
          movement_acv = ActionCostConstants::DEFAULT;
        }
      }
    }
    // Otherwise, it's a regular move within the current map.
    else
    {
      Coordinate new_coords = CoordUtils::get_new_coordinate(creature_location, direction);
      TilePtr creatures_new_tile = map->at(new_coords.first, new_coords.second);
      
      movement_acv = move_within_map(creature, map, creatures_old_tile, creatures_new_tile, new_coords, direction, confirm_if_dangerous);
    }

    // Update the loaded map details with the player's new coordinate,
    // assuming this is the player.
    if (creature->get_is_player())
    {
      Coordinate creature_location = map->get_location(creature->get_id());
      Game::instance().get_loaded_map_details_ref().update_engine_coord(creature_location);
    }
  }
  
  return movement_acv;
}

ActionCostValue MovementAction::move_off_map(CreaturePtr creature, MapPtr map, TilePtr creatures_old_tile, const Direction direction)
{
  ActionCostValue movement_acv = ActionCostConstants::NO_ACTION;

  if (creature != nullptr && map != nullptr)
  {
    Game& game = Game::instance();
    IMessageManager& manager = MM::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());
    IMessageManager& pl_man = MM::instance();

    Coordinate c = map->get_location(creature->get_id());
    Dimensions dim = map->size();

    Direction exit_direction = MapUtils::get_exit_direction(direction, dim, c);
    MapExitPtr map_exit = map->get_map_exit(exit_direction);

    if (map_exit == nullptr)
    {
      map_exit = map->get_map_exit();
    }

    Coordinate current_coord = map->get_location(creature->get_id());
    Coordinate proposed_new_coord = MapUtils::calculate_new_coord_for_multimap_movement(current_coord, creatures_old_tile, direction, map_exit);
    MapExitOutcome exit_outcome = MapUtils::can_exit_map(map, creature, map_exit, direction, proposed_new_coord);

    if (exit_outcome != MapExitOutcome::CAN_EXIT)
    {
      if (creature->get_is_player())
      {
        string movement_message = MovementTextKeys::get_cannot_exit_map_message(map->get_map_type(), exit_outcome);

        pl_man.add_new_message(movement_message);
        pl_man.send();
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
          MapUtils::potentially_set_permanence_if_leaving_followers_behind(map, creature);
          MapUtils::set_up_transitive_exits_as_necessary(map, map_exit);
          handle_properties_and_move(creature, creatures_old_tile, map, map_exit, proposed_new_coord);
          movement_acv = get_action_cost_value(creature);
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

        movement_acv = get_action_cost_value(creature);
      }
    }
  }
  
  return movement_acv;
}

ActionCostValue MovementAction::move_within_map(CreaturePtr creature, MapPtr map, TilePtr creatures_old_tile, TilePtr creatures_new_tile, const Coordinate& new_coords, const Direction d, const bool confirm_if_dangerous)
{
  Game& game = Game::instance();
  ActionCostValue movement_acv = ActionCostConstants::NO_ACTION;
  bool creature_incorporeal = creature && creature->has_status(StatusIdentifiers::STATUS_ID_INCORPOREAL);
  IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
  pair<bool, TilePtr> attack_at_range = MapUtils::get_melee_attack_target(map, creature, d);
  bool automelee = game.get_settings_ref().get_setting_as_bool(Setting::AUTOMELEE);

  if (creature && creatures_new_tile)
  {
    // If the creature is hidden, and the movement is to stay in place, ensure
    // that hiding remains active after the end of the turn.
    if (map && map->get_map_type() == MapType::MAP_TYPE_WORLD)
    {
      creature->set_free_hidden_actions(0);
    }
    else
    {
      check_movement_stealth(creature, d);
    }

    if (MapUtils::is_creature_present(creatures_new_tile))
    {
      movement_acv = handle_movement_into_occupied_tile(creature, creatures_new_tile, map, new_coords, d);
    }
    else if (attack_at_range.first && 
             attack_at_range.second != nullptr && 
             ((automelee && creature->get_is_player()) || 
              confirm_ranged_melee_attack(creature, attack_at_range.second->get_creature())))
    {
      CombatManager cm;
      movement_acv = cm.attack(creature, attack_at_range.second->get_creature(), AttackType::ATTACK_TYPE_MELEE_PRIMARY);
    }
    // Only try to handle a blocking terrain feature if the creature is corporeal.
    // Spirits don't care about closed doors, etc!
    else if (MapUtils::is_blocking_feature_present(creatures_new_tile) && !creature_incorporeal)
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
      movement_acv = ActionCostConstants::DEFAULT;
    }
    else if ((creatures_new_tile->get_is_blocking() && !creature_incorporeal) ||
             (creatures_new_tile->get_is_diggable() && creature->get_equipment().is_digging_implement_equipped()))
    {
      // Can the creature dig through the tile?
      ItemPtr wielded = creature->get_equipment().get_item(EquipmentWornLocation::EQUIPMENT_WORN_WIELDED);
      int tile_hardness = creatures_new_tile->get_hardness();
      bool dug = false;

      if (wielded != nullptr)
      {
        string dig_hardness = wielded->get_additional_property(ItemProperties::ITEM_PROPERTIES_DIG_HARDNESS);

        if (!dig_hardness.empty())
        {
          if (String::to_int(dig_hardness) >= tile_hardness)
          {
            DigAction da;
            movement_acv = da.dig_through(creature->get_id(), wielded, map, creatures_new_tile, new_coords, true, true);
            dug = true;
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
        movement_acv = ActionCostConstants::NO_ACTION;
      }

      if (tile_hardness > 0 && !dug)
      {
        Game().instance().get_sound(creature)->play(SoundEffectID::BUMP);
      }
    }
    else if (!creatures_new_tile->get_is_available_for_creature(creature))
    {
      manager.add_new_message(StringTable::get(MovementTextKeys::ACTION_MOVE_RACE_NOT_ALLOWED));
      manager.send();
    }
    else
    {
      CurrentCreatureAbilities cca;

      if (cca.can_move(creature, true))
      {
        if (!confirm_if_dangerous || confirm_move_to_tile_if_necessary(creature, map, creatures_old_tile, creatures_new_tile, new_coords))
        {
          ostringstream ss;
          ss << "Moving within map: ID " << creature->get_id() << " to " << new_coords.first << "," << new_coords.second;
          Log::instance().debug(ss.str());

          // Update the map info
          MapUtils::add_or_update_location(map, creature, new_coords, creatures_old_tile);
          movement_acv = get_action_cost_value(creature);

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

    // After moving, there is a chance to get a free search of the surrounding
    // tiles.
    //
    // For the initial check, don't mark the skill.  Detection should only
    // be marked if there's something to be found - let SearchAction handle
    // that.
    if (RNG::percent_chance(creature->get_skills().get_value(SkillType::SKILL_GENERAL_DETECTION)))
    {
      SearchAction search;
      search.search(creature, false);
    }
  }
  
  return movement_acv;
}

// Handle movement into an occupied tile.  First, check to see whether the
// creature will attack the occupying creature.  If so, attack the creature.
ActionCostValue MovementAction::handle_movement_into_occupied_tile(CreaturePtr creature, TilePtr creatures_new_tile, MapPtr map, const Coordinate& new_coords, const Direction d)
{
  ActionCostValue movement_acv = ActionCostConstants::NO_ACTION;

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
                      && confirm_move_to_tile_if_necessary(creature, map, current_tile, potential_squeeze_tile, potential_squeeze_coords));

          if (confirm)
          {
            MapUtils::squeeze_by(map, creature, new_coords, d);

            // Squeezing past should cost roughly twice as much as a single
            // move, since two squares are being traversed in a turn.
            movement_acv = creature->get_speed().get_current();
          }
          else
          {
            // Couldn't squeeze by, either due a monster being there, no
            // tile, the tile not allowing a creature on it, etc.
            IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
            manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_SQUEEZE_FAILURE));
            manager.send();
          }

          return movement_acv;
        }
        case MovementThroughTileType::MOVEMENT_SWITCH:
        {
          MapUtils::swap_places(map, creature, adjacent_creature);

          movement_acv = ActionCostConstants::DEFAULT;
          return movement_acv;
        }
        default:
        case MovementThroughTileType::MOVEMENT_NONE:
        {
          return movement_acv;
        }
      }
    }
  }

  // Prevent hirelings from trying to move into their leader's tile,
  // thereby trying to attack them.
  if (adjacent_creature != nullptr)
  {
    bool should_attack = true;

    if (creature != nullptr)
    {
      string leader_id = creature->get_leader_id();

      if (leader_id == adjacent_creature->get_id())
      {
        should_attack = false;
      }
    }

    if (should_attack)
    {
      CombatManager cm;

      // Call the directional attack function so that if the creature is
      // dual wielding weapons, both attacks are properly considered.
      movement_acv = cm.attack(creature, d);
    }
  }

  return movement_acv;
}

// Figure out what the creature wants to do in terms of getting through the occupied tile.
MovementThroughTileType MovementAction::get_movement_through_tile_type(CreaturePtr creature, CreaturePtr adjacent_creature, TilePtr creatures_new_tile)
{
  IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
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
    creature_can_enter_adjacent_tile = creatures_new_tile->get_is_available_for_creature(creature);
  }

  // Don't switch if the creature will resist.
  string res_sw = adjacent_creature->get_decision_strategy()->get_property(DecisionStrategyProperties::DECISION_STRATEGY_RESIST_SWITCH);
  if (!res_sw.empty() && (String::to_bool(res_sw) == true))
  {
    // Add a message about the creature not letting the player past.
    manager.add_new_message(StringTable::get(TextKeys::DECISION_RESIST_SWITCH));
    manager.send();

    // Switch back to the prompt for attack.
    mtt = MovementThroughTileType::MOVEMENT_ATTACK;
  }
  else
  {
    if (adjacent_creature_can_move && creature_can_enter_adjacent_tile)
    {
      mtt = get_friendly_movement_past_type(creature, TextKeys::DECISION_SWITCH_FRIENDLY_CREATURE, MovementThroughTileType::MOVEMENT_SWITCH, mtt);
    }
    else
    {
      if (creature_can_enter_adjacent_tile)
      {
        mtt = get_friendly_movement_past_type(creature, TextKeys::DECISION_SQUEEZE_FRIENDLY_CREATURE, MovementThroughTileType::MOVEMENT_SQUEEZE, mtt);
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
      MapPtr map = Game::instance().get_current_map();
      Game::instance().get_deity_action_manager_ref().notify_action(creature, map, CreatureActionKeys::ACTION_ATTACK_FRIENDLY);
    }
  }

  return mtt;
}

// "Friendly movement" should default to selecting yes from the confirmation.
MovementThroughTileType MovementAction::get_friendly_movement_past_type(CreaturePtr creature, const string& prompt_sid, const MovementThroughTileType selected_type, const MovementThroughTileType fallback_type)
{
  MovementThroughTileType mtt = fallback_type;

  if (creature != nullptr)
  {
    if (creature->get_automatic_movement_ref().get_engaged())
    {
      mtt = selected_type;
    }
    else
    {
      IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
      manager.add_new_confirmation_message(TextMessages::get_confirmation_message(prompt_sid));

      bool switch_places = creature->get_decision_strategy()->get_confirmation(true);

      if (switch_places)
      {
        mtt = selected_type;
      }
    }
  }

  return mtt;
}

// Generate and move to the new map using the tile type and subtype present
// on the tile, rather than a source like the map exit.
ActionCostValue MovementAction::generate_and_move_to_new_map(CreaturePtr creature, MapPtr map, MapExitPtr map_exit, TilePtr tile, const ExitMovementType emt)
{
  ActionCostValue action_cost_value = ActionCostConstants::NO_ACTION;

  if (creature && tile && map)
  {
    return generate_and_move_to_new_map(creature, map, map_exit, tile, tile->get_tile_type(), tile->get_tile_subtype(), {}, emt);
  }

  return action_cost_value;
}

ActionCostValue MovementAction::generate_and_move_to_new_map(CreaturePtr creature, MapPtr map, MapExitPtr map_exit, TilePtr tile, const TileType tile_type, const TileType tile_subtype, const std::map<std::string, std::string>& map_exit_properties, const ExitMovementType emt)
{
  ActionCostValue action_cost_value = ActionCostConstants::NO_ACTION;

  if (creature && tile && map)
  {
    Game& game = Game::instance();
    ControllerPtr creature_controller = creature->get_decision_strategy()->get_controller();
    promise<ActionCostValue> ap;
    future<ActionCostValue> af = ap.get_future();
    std::thread thread([&]() {
      ActionCostValue acv = do_generate_and_move_to_new_map(creature, map, map_exit, tile, tile_type, tile_subtype, map_exit_properties, emt);
      ap.set_value(acv);
    });

    game.set_loading();

    while (af.wait_for(std::chrono::milliseconds(250)) != std::future_status::ready)
    {
      creature_controller->poll_event();
    }

    game.set_ready();

    thread.join();
    action_cost_value = af.get();
  }

  return action_cost_value;
}


// General version that can handle tile type/subtype from any source - the tile
// itself, a map exit, etc. This function should really never be called
// directly - it should be called asynchronously from 
// do_generate_and_move_to_new_map.
ActionCostValue MovementAction::do_generate_and_move_to_new_map(CreaturePtr creature, MapPtr map, MapExitPtr map_exit, TilePtr tile, const TileType tile_type, const TileType tile_subtype, const std::map<std::string, std::string>& map_exit_properties, const ExitMovementType emt)
{
  ActionCostValue action_cost_value = ActionCostConstants::NO_ACTION;

  // If permanent, set the previous map ID, so that if there are staircases, etc., the
  // link to the current map can be maintained.
  if (map->get_permanent())
  {
    tile->set_additional_property(TileProperties::TILE_PROPERTY_PREVIOUS_MAP_ID, map->get_map_id());
  }

  // The exits may have properties - these are typically set on custom maps
  // for things like dungeon depth increments, etc.  The properties should 
  // be copied over to the tile prior to the creation of the generator, so 
  // they can be properly re-applied to the map, potentially.
  TileUtils::copy_exit_properties_to_tile(tile);

  GeneratorPtr generator = TerrainGeneratorFactory::create_generator(tile, map, map->get_map_id(), tile_type, tile_subtype, emt);

  // Ensure that the overworld map ID is always available to the generator!
  map->get_map_type() == MapType::MAP_TYPE_WORLD ? generator->set_additional_property(TileProperties::TILE_PROPERTY_ORIGINAL_MAP_ID, map->get_map_id())
    : generator->set_additional_property(TileProperties::TILE_PROPERTY_ORIGINAL_MAP_ID, tile->get_additional_property(TileProperties::TILE_PROPERTY_ORIGINAL_MAP_ID));

  Game& game = Game::instance();

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
      pair<bool, bool> override_depth = generator->override_depth_update_defaults();
      DangerLevelCalculatorPtr calc = DangerLevelCalculatorFactory::create_danger_level_calculator(map->get_map_type(), override_depth.second, emt);
      calc->set_property(DangerLevelProperties::DANGER_LEVEL_PROPERTIES_TILE_TYPE, std::to_string(static_cast<int>(tile_type)));
      uint danger_level = calc->calculate(map);

      Dimensions dim = map->size();
      Depth& depth = dim.depth_ref();
      IMapTypeQueryPtr mtq = MapTypeQueryFactory::create_map_type_query(generator->get_map_type());

      // Check to see if the depth should be updated.  For things like fields
      // and forests, it shouldn't, but for dungeons/caverns/etc., it should.
      if (mtq && (mtq->should_update_depth() || (override_depth.first && override_depth.second)))
      {
        // If the tile has a set depth associated with it, then use that.
        // Otherwise, use the specified depth increment.
        string initial_depth = tile->get_additional_property(MapProperties::MAP_PROPERTIES_DEPTH);
        int depth_increment = MapUtils::calculate_depth_delta(map, tile, emt);

        if (!initial_depth.empty())
        {
          int tile_initial_depth = String::to_int(initial_depth);
          depth.set_current(tile_initial_depth);
        }
        else
        {
          depth.set_current(depth.get_current() + depth_increment);
        }

        if (depth_increment != 0) 
        {
          generator->set_additional_property(TileProperties::TILE_PROPERTY_DEPTH_INCREMENT, std::to_string(depth_increment));
        }
      }

      // If this is an overworld map, add a chance of foragables and
      // healing herbs.
      ForagablesCalculator fc;
      int pct_chance_foragables = fc.calculate_pct_chance_foragables(creature);
      int pct_chance_herbs = fc.calculate_pct_chance_herbs(creature);

      // JCD FIXME refactor
      // Add whether there's ocean in each direction, to guide procgen.
      if (map->get_map_type() == MapType::MAP_TYPE_WORLD)
      {
        Coordinate cr_coord = map->get_location(creature->get_id());
        vector<Direction> coast_dirs = MapUtils::get_coastline_directions(map, cr_coord);
        MapUtils::set_coastline_generator_dirs(generator.get(), coast_dirs);
      }

      auto perm_it = map_exit_properties.find(MapProperties::MAP_PROPERTIES_PERMANENCE);

      if (perm_it != map_exit_properties.end())
      {
        generator->set_additional_property(MapProperties::MAP_PROPERTIES_PERMANENCE, perm_it->second);
      }

      generator->set_additional_property(MapProperties::MAP_PROPERTIES_DANGER_LEVEL_OVERRIDE, tile->get_additional_property(MapProperties::MAP_PROPERTIES_DANGER_LEVEL_OVERRIDE));
      generator->set_additional_property(MapProperties::MAP_PROPERTIES_PCT_CHANCE_FORAGABLES, to_string(pct_chance_foragables));
      generator->set_additional_property(MapProperties::MAP_PROPERTIES_PCT_CHANCE_HERBS, to_string(pct_chance_herbs));
      generator->set_additional_property(MapProperties::MAP_PROPERTIES_EXIT_MOVEMENT_TYPE, to_string(static_cast<int>(emt)));
      generator->set_additional_property(TileProperties::TILE_PROPERTY_NAME, tile->get_additional_property(TileProperties::TILE_PROPERTY_NAME));

      if (MapUtils::has_known_treasure(tile, creature, true))
      {
        int treasure_total_skill_value = SkillsCalculator::calculate_hidden_treasure_total_skill_value(creature, map->get_map_type(), String::to_int(tile->get_additional_property(TileProperties::TILE_PROPERTY_MIN_LORE_REQUIRED)));
        generator->set_additional_property(TileProperties::TILE_PROPERTY_MIN_LORE_REQUIRED, std::to_string(treasure_total_skill_value));
      }

      if (MapUtils::has_known_shipwreck(map, tile, creature, true))
      {
        int treasure_total_skill_value = SkillsCalculator::calculate_hidden_treasure_total_skill_value(creature, map->get_map_type(), String::to_int(MapUtils::get_shipwreck_min_lore(map, tile)));
        generator->set_additional_property(TileProperties::TILE_PROPERTY_UNDERWATER_MIN_LORE_REQUIRED, std::to_string(treasure_total_skill_value));
      }

      new_map = generator->generate_and_initialize(danger_level, depth);

      // If a map exit's been provided, check to see if there's an event
      // scripts map that needs to be set on the map after generation.
      if (map_exit != nullptr)
      {
        EventScriptsMap me_esm = map_exit->get_event_scripts();

        if (!me_esm.empty())
        {
          new_map->set_event_scripts(me_esm);
        }
      }

      EventScriptsMap esm = new_map->get_event_scripts();
      auto es_it = esm.find(MapEventScripts::MAP_EVENT_SCRIPT_CREATE);

      if (new_map && es_it != esm.end())
      {
        ScriptDetails sd = es_it->second;
        ScriptEngine& se = Game::instance().get_script_engine_ref();
        MapScript ms;

        if (RNG::percent_chance(sd.get_chance()))
        {
          // Ensure the map's in the registry, so that if the script needs to
          // reference it, the map can be retrieved.
          game.get_map_registry_ref().set_map(new_map->get_map_id(), new_map);

          // JCD FIXME: Future events should be ms.execute_create, execute_something_else, etc.
          ms.execute(se, sd.get_script(), new_map);
        }
      }

      // Set a link back to the old tile.
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

        string song_location = tile->get_additional_property(MapProperties::MAP_PROPERTIES_SONG_LOCATION);

        if (!song_location.empty())
        {
          new_map->set_property(MapProperties::MAP_PROPERTIES_SONG_LOCATION, song_location);
        }
      }
    }
                
    // Set the map's MapExitPtr to point to the previous map.  But only if 
    // it's an overworld map.  Underworld maps (dungeons, sewers, etc)
    // will have stairway exits.  Underwater maps (Telari and others)
    // TBD.
    if (new_map->get_map_type() == MapType::MAP_TYPE_OVERWORLD && 
        map->get_property(MapProperties::MAP_PROPERTIES_NO_WORLD_LINKAGE) != std::to_string(true))
    {
      MapExitUtils::add_exit_to_map(new_map, map->get_map_id());
    }
                
    // If we're moving on to an existing map, handle any tile properties
    // that may be present.  Don't worry about this when we're moving
    // to a brand-new map, as tile properties will be automatically 
    // handled during map generation, and will be removed after creating
    // items and creatures.
    add_initial_map_messages(creature, new_map, generator->get_terrain_type());
    handle_properties_and_move_to_new_map(creature, tile, map, new_map, map_exit);
    action_cost_value = get_action_cost_value(creature);
  }
 
  return action_cost_value;
}

void MovementAction::add_initial_map_messages(CreaturePtr creature, MapPtr map, const TileType tile_type)
{
  // Add a message about the terrain type.
  IMessageManager& manager = MM::instance(MessageTransmit::MAP, creature, creature && creature->get_is_player());
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
bool MovementAction::confirm_move_to_tile_if_necessary(CreaturePtr creature, MapPtr current_map, TilePtr creatures_old_tile, TilePtr creatures_new_tile, const Coordinate& creatures_new_tile_coords)
{
  TileMovementConfirmation tmc;
  Coordinate old_tile_coords = {0, 0};
  bool is_automoving = false;

  if (creature != nullptr && current_map != nullptr)
  {
    old_tile_coords = current_map->get_location(creature->get_id());
    is_automoving = creature->get_automatic_movement_ref().get_engaged();
  }

  auto details = tmc.get_confirmation_details(creature, current_map, creatures_old_tile, old_tile_coords, creatures_new_tile, creatures_new_tile_coords);
  bool needs_confirmation = details.get_require_prompt();

  if (needs_confirmation)
  {
    bool confirmation = false;

    Game& game = Game::instance();
    Settings& settings = game.get_settings_ref();
    bool never_move_to_danger = String::to_bool(settings.get_setting(Setting::NEVER_MOVE_TO_DANGER_TILES));
    bool is_player = creature->get_is_player();

    if (is_player && never_move_to_danger == false && is_automoving == false)
    {
      IMessageManager& manager = MM::instance();
      manager.add_new_confirmation_message(details.get_confirmation_message());

      confirmation = (creature->get_decision_strategy()->get_confirmation());
      manager.clear_if_necessary();
    }
    else if (!is_player)
    {
      confirmation = creature->get_decision_strategy()->get_move_to_dangerous_tile(current_map, creature, creatures_new_tile);
    }

    if (confirmation)
    {
      // Play a sound, if specified.
      string sound_id = details.get_sound_effect_id();

      if (is_player && !sound_id.empty())
      {
        Game::instance().get_sound()->play(sound_id);
      }

      // Add any post-movement message.
      string post_movement_message_sid = details.get_post_movement_message_sid();

      if (!post_movement_message_sid.empty())
      {
        IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
        manager.add_new_message(StringTable::get(post_movement_message_sid));
        manager.send();
      }
    }

    return confirmation;      
  }
  
  return true;  
}

ActionCostValue MovementAction::handle_properties_and_move_to_new_map(CreaturePtr creature, TilePtr current_tile, MapPtr old_map, MapPtr new_map, MapExitPtr map_exit)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION;

  if (new_map && current_tile)
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

    if (current_tile->has_additional_property(MapProperties::MAP_PROPERTIES_INITIAL_ITEMS))
    {
      MapItemGenerator mig;
      bool items_generated = mig.generate_initial_set_items(new_map, current_tile->get_additional_properties());

      if (items_generated)
      {
        current_tile->remove_additional_property(MapProperties::MAP_PROPERTIES_INITIAL_ITEMS);
      }
    }

    // Update the weather, if we're coming off the world map.
    WorldWeatherUpdater wwu;
    TilePtr old_tile;

    if (old_map != nullptr)
    {
      old_tile = MapUtils::get_tile_for_creature(old_map, creature);
    }

    wwu.update_weather_for_map(old_map, old_tile, new_map);

    move_to_new_map(current_tile, old_map, new_map, map_exit);
    acv = get_action_cost_value(nullptr);
  }

  return acv;
}

void MovementAction::move_to_new_map(TilePtr current_tile, MapPtr old_map, MapPtr new_map, MapExitPtr map_exit)
{
  GameUtils::move_to_new_map(current_tile, old_map, new_map, map_exit);

  bool checkpoint_save = String::to_bool(Game::instance().get_settings_ref().get_setting(Setting::CHECKPOINT_SAVE));

  if (checkpoint_save)
  {
    Game& game = Game::instance();
    game.get_action_manager_ref().save(game.get_current_player(), false);

    // Normally when saving, check_scores is set to false so that a score file
    // entry won't be generated.  But checkpoint saves don't exit the game, so
    // ensure check_scores is reset to true and score file entries can happen.
    game.set_check_scores(true);
  }
}

void MovementAction::handle_properties_and_move(CreaturePtr creature, TilePtr old_tile, MapPtr old_map, MapExitPtr map_exit, const Coordinate& proposed_new_coord)
{
  Game& game = Game::instance();
  
  if (map_exit)
  {
    if (map_exit->is_using_map_id())
    {
      string new_map_id = map_exit->get_map_id();
      MapPtr new_map = game.map_registry.get_map(new_map_id);

      if (creature != nullptr && !CoordUtils::is_end(proposed_new_coord))
      {
        new_map->add_or_update_location(creature->get_id(), proposed_new_coord);
      }
      
      handle_properties_and_move_to_new_map(creature, old_tile, old_map, new_map, map_exit);
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
  ActionCostValue movement_acv = ActionCostConstants::NO_ACTION;

  if (cca.can_move(creature, true))
  {
    Game& game = Game::instance();
    MapPtr map = game.get_current_map();
    StairwayMovementAction smm;
    SkillManager sm;

    if (!MapUtils::adjacent_hostile_creature_exists(creature->get_id(), map) 
      || sm.check_skill(creature, SkillType::SKILL_GENERAL_ESCAPE)
      || RNG::percent_chance(BASE_ASCEND_DESCEND_CHANCE))
    {
      movement_acv = smm.ascend(creature, this);
    }
    else
    {
      add_cannot_escape_message(creature);
      movement_acv = ActionCostConstants::DEFAULT;
    }
  }

  return movement_acv;
}

// Descend, if the creature can move.  Or, if the creature has the appropriate
// item, dig.
ActionCostValue MovementAction::descend(CreaturePtr creature)
{
  CurrentCreatureAbilities cca;
  ActionCostValue movement_acv = ActionCostConstants::NO_ACTION;

  if (cca.can_move(creature, true))
  {
    Game& game = Game::instance();
    MapPtr map = game.get_current_map();
    StairwayMovementAction smm;
    SkillManager sm;

    if (!MapUtils::adjacent_hostile_creature_exists(creature->get_id(), map) 
      || sm.check_skill(creature, SkillType::SKILL_GENERAL_ESCAPE)
      || RNG::percent_chance(BASE_ASCEND_DESCEND_CHANCE))
    {
      movement_acv = smm.descend(creature, this);
    }
    else
    {
      add_cannot_escape_message(creature);
      movement_acv = ActionCostConstants::DEFAULT;
    }
  }

  return movement_acv;
}

bool MovementAction::confirm_ranged_melee_attack(CreaturePtr creature, CreaturePtr attacked_creature)
{
  bool confirm = false;

  if (creature != nullptr)
  {
    if (creature->get_is_player())
    {
      Game& game = Game::instance();
      string confirm_attack = TextMessages::get_confirmation_message(TextKeys::DECISION_CONFIRM_RANGED_MELEE_ATTACK);
      game.display->confirm(confirm_attack);

    }

    confirm = creature->get_decision_strategy()->get_attack_confirmation(attacked_creature);
  }

  return confirm;
}

void MovementAction::add_cannot_escape_message(const CreaturePtr& creature)
{
  if (creature && creature->get_is_player())
  {
    IMessageManager& manager = MM::instance();
    string cannot_escape = StringTable::get(MovementTextKeys::ACTION_MOVE_ADJACENT_HOSTILE_CREATURE);
    manager.add_new_message(cannot_escape);
    manager.send();
  }
}

ActionCostValue MovementAction::get_action_cost_value(CreaturePtr creature) const
{
  ActionCostValue acv = ActionCostConstants::DEFAULT;

  if (creature != nullptr)
  {
    // When timewalking, movement is free.
    if (creature->has_status(StatusIdentifiers::STATUS_ID_TIMEWALK))
    {
      acv = ActionCostConstants::NO_ACTION;
    }
    else
    {
      int stumble_chance = static_cast<int>(creature->get_blood().get_blood_alcohol_content() * 100);

      if (RNG::percent_chance(stumble_chance))
      {
        // Add a message about stumbling.
        IMessageManager& manager = MM::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());
        manager.add_new_message(ActionTextKeys::get_stumble_message(creature->get_description_sid(), creature->get_is_player()));
        manager.send();
        
        return ActionCostConstants::STUMBLE;
      }
    }
  }

  return acv;
}

void MovementAction::check_movement_stealth(CreaturePtr creature, const Direction d)
{
  if (creature != nullptr)
  {
    // Hidden creatures null-moving are always safe.  Movement in other
    // directions requires a successful stealth check.
    if (creature->has_status(StatusIdentifiers::STATUS_ID_HIDE))
    {
      SkillManager sm;
      bool stealth_successful = sm.check_skill(creature, SkillType::SKILL_GENERAL_STEALTH);

      if (d == Direction::DIRECTION_NULL || (stealth_successful && RNG::percent_chance(95)))
      {
        creature->increment_free_hidden_actions();
      }
      else
      {
        creature->set_free_hidden_actions(0);
      }
    }
  }
}

