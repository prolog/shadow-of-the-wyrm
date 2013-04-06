#include <boost/foreach.hpp>
#include <boost/make_shared.hpp>
#include <boost/timer/timer.hpp>
#include "global_prototypes.hpp"
#include "Conversion.hpp"
#include "CoordUtils.hpp"
#include "CreatureCalculator.hpp"
#include "CreatureDescriber.hpp"
#include "CreatureCoordinateCalculator.hpp"
#include "CreatureFeatures.hpp"
#include "Detection.hpp"
#include "FieldOfViewStrategy.hpp"
#include "FieldOfViewStrategyFactory.hpp"
#include "Game.hpp"
#include "CommandProcessor.hpp"
#include "CreatureTranslator.hpp"
#include "Log.hpp"
#include "MapCursor.hpp"
#include "MapUtils.hpp"
#include "PlayerConstants.hpp"
#include "WorldGenerator.hpp"
#include "MapTranslator.hpp"
#include "DisplayStatistics.hpp"
#include "MessageManager.hpp"
#include "Serialize.hpp"
#include "ViewMapTranslator.hpp"
#include "WorldTimeKeeperCoordinator.hpp"

// Used by serialization code:
#include "CommandFactoryFactory.hpp"
#include "DisplayFactory.hpp"
#include "KeyboardCommandMapFactory.hpp"
#include "WorldFactory.hpp"

using namespace std;

Game::Game()
: keep_playing(true), reload_game_loop(false), current_world_ix(0)
{
  // Setup the time keeper.  On a new game, this will initialize everything as
  // expected - when loading an existing game, this will be overwritten later,
  // which is fine.
  WorldTimeKeeperCoordinator time_coordinator;
  time_coordinator.setup_time_keeper(time_keeper);
}

Game::~Game()
{
}

void Game::set_display(DisplayPtr game_display)
{
  display = game_display;
}

DisplayPtr Game::get_display() const
{
  return display;
}

void Game::set_map_registry(const MapRegistry& new_map_registry)
{
  map_registry = new_map_registry;
}

MapRegistry& Game::get_map_registry_ref()
{
  return map_registry;
}

void Game::set_deities(const DeityMap& game_deities)
{
  deities = game_deities;
}

const DeityMap& Game::get_deities_ref() const
{
  return deities;
}

void Game::set_races(const RaceMap& game_races)
{
  races = game_races;
}

const RaceMap& Game::get_races_ref() const
{
  return races;
}

void Game::set_classes(const ClassMap& game_classes)
{
  classes = game_classes;
}

const ClassMap& Game::get_classes_ref() const
{
  return classes;
}

void Game::set_creatures(const CreatureMap& game_creatures)
{
  creatures = game_creatures;
}

void Game::set_spells(const SpellMap& game_spells)
{
  spells = game_spells;
}

const SpellMap& Game::get_spells_ref()
{
  return spells;
}

const CreatureMap& Game::get_creatures_ref() const
{
  return creatures;
}

void Game::set_creature_generation_values(const CreatureGenerationValuesMap& game_cgv)
{
  creature_generation_values = game_cgv;
}

CreatureGenerationValuesMap& Game::get_creature_generation_values_ref()
{
  return creature_generation_values;
}

void Game::set_item_generation_values(const GenerationValuesMap& game_igv)
{
  item_generation_values = game_igv;
}

GenerationValuesMap& Game::get_item_generation_values_ref()
{
  return item_generation_values;
}

void Game::set_items(const ItemMap& game_items)
{
  items = game_items;
}

const ItemMap& Game::get_items_ref() const
{
  return items;
}

void Game::set_custom_maps(const vector<MapPtr>& custom_maps)
{
  BOOST_FOREACH(MapPtr custom_map, custom_maps)
  {
    string id = custom_map->get_map_id();
    map_registry.set_map(id, custom_map);
  }
}

void Game::set_tile_display_info(const vector<DisplayTile>& game_tiles)
{
  tile_info = game_tiles;
}

const vector<DisplayTile>& Game::get_tile_display_info_ref() const
{
  return tile_info;
}

CreaturePtr Game::get_current_player() const
{
  CreaturePtr current_player = get_current_map()->get_creature(PlayerConstants::PLAYER_CREATURE_ID);
  return current_player;
}

// Create the new world, and set the player at the special "player's starting location" point.
void Game::create_new_world(CreaturePtr creature)
{
  WorldGenerator world_generator;
  MapPtr current_world = world_generator.generate();
  WorldPtr world(new World(current_world));
 
  worlds.push_back(world);
  set_current_map(current_world);  
  current_world_ix = (worlds.size() - 1);

  TilePtr tile = current_world->get_tile_at_location(WorldMapLocationTextKeys::STARTING_LOCATION);

  if (tile)
  {
    tile->set_creature(creature);

    // Set the starting location.
    if (creature->get_is_player())
    {
      Coordinate c = current_world->get_location(WorldMapLocationTextKeys::STARTING_LOCATION);
      MapUtils::add_or_update_location(current_world, creature, c);
    }
  }
  else
  {
    Log::instance().log("Couldn't get player's initial starting location!");
  }
}

// Update the display: the statistics area, and the current map.
void Game::update_display(CreaturePtr current_player, MapPtr current_map, MapPtr fov_map)
{
  if (current_player && current_map)
  {
    // boost::timer::auto_cpu_timer timer;
    MapDisplayArea display_area = display->get_map_display_area();

    DisplayStatistics display_stats = CreatureTranslator::create_display_statistics(current_player, current_map);
    display->display(display_stats);

    MapCursor mc;
    Coordinate reference_coords = mc.get_cursor_location(current_map);

    Coordinate display_coord = CreatureCoordinateCalculator::calculate_display_coordinate(display_area, current_map, reference_coords);
    loaded_map_details.update_display_coord(display_coord);
    bool redraw_needed = loaded_map_details.requires_full_map_redraw();

    DisplayMap display_map = MapTranslator::create_display_map(current_map, fov_map, display_area, reference_coords, redraw_needed);
    
    if (redraw_needed)
    {
      display->draw(display_map);
    }
    else
    {
      display->draw_update_map(display_map);
    }

    // As long as there are still player actions within the current map, and we've
    // not loaded a new map, a full redraw is not needed:
    loaded_map_details.synch();
  }
}

void Game::go()
{
  game_command_factory = boost::make_shared<CommandFactory>();
  game_kb_command_map = boost::make_shared<KeyboardCommandMap>();

  MapPtr current_map = get_current_map();
  CreaturePtr current_player = get_current_player();

  // To see if this is a new game, check the ActionCoordinator to see if there is
  // a map, yet.  If there isn't, the game hasn't been restored, so it must be a
  // new game.
  bool new_game = ac.get_current_map_id().empty();

  string welcome_message = TextMessages::get_welcome_message(current_player->get_name(), new_game);

  MessageManager& manager = MessageManager::instance();
  manager.add_new_message(welcome_message);
  manager.send();

  CreatureCalculator::update_calculated_values(current_player);
 
  string map_id = "";

  // Main game loop.
  while(keep_playing)
  {
    detect_creatures_if_necessary(current_player, map_id);
        
    current_map = get_current_map();

    // After loading the (new) map, a full redraw is needed.
    map_id = current_map_id;
    loaded_map_details.update_map_id(map_id);

    map<string, CreaturePtr> map_creatures = current_map->get_creatures();

    ac.reset_if_necessary(current_map->get_permanent(), current_map->get_map_id(), map_creatures);

    Calendar& calendar = worlds[current_world_ix]->get_calendar();
    
    while (ac.has_actions())
    {      
      // Update the list of creatures after each action; otherwise, creatures that are killed
      // might persist.
      map_creatures = current_map->get_creatures();

      CreaturePtr current_creature;
      ActionCost next_action_cost = ac.get_next_action_cost();
      string creature_id = ac.get_next_creature_id();      
      map<string, CreaturePtr>::iterator c_it = map_creatures.find(creature_id);

      if (c_it != map_creatures.end())
      {
        current_creature = c_it->second;
      }
      
      if (!current_creature)
      {
        // Creature's been killed - advance to the next creature in the
        // queue.
        ac.update_actions(); 
      }
      else // Creature's fine, process its action
      {
        // If we shouldn't keep playing (player has quit, has been killed, etc), then break out of the 
        // game loop.
        if (!keep_playing) break;
        
        process_elapsed_time(calendar, next_action_cost);

        // Player may have been killed by some time-related effect.
        if (!keep_playing) break;
                
        ActionCost action_cost = process_action_for_creature(current_creature, current_map);

        // Remove the creature's current action.  This is done after the "keep_playing"
        // check so that saving, etc., does not advance the turn.

        if (keep_playing)
        {
          ac.update_actions(); 
          ac.add(action_cost, current_creature->get_id());
        }
        
        if (reload_game_loop)
        {
          reload_game_loop = false;
          break;
        }
      }
    }
  }
}

// Update the calendar based on how much time elapsed to this creature's action
void Game::process_elapsed_time(Calendar& calendar, const ActionCost& next_action_cost)
{
  double seconds = ActionCostConverter::to_seconds(next_action_cost.get_cost(), get_current_map()->get_map_type());
  calendar.add_seconds(seconds);
  time_keeper.tick(seconds);
}

// Get and process the action for the current creature
ActionCost Game::process_action_for_creature(CreaturePtr current_creature, MapPtr current_map)
{
  ActionCost action_cost;
  
  if (current_creature)
  {
    DecisionStrategyPtr strategy = current_creature->get_decision_strategy();

    if (strategy)
    {
      bool advance = false;
      
      while (!advance)
      {
        // Comment/un-comment this as necessary to figure out if creatures are taking too long to process turns.
        //boost::timer::auto_cpu_timer timer;
        MapPtr view_map;
        MapPtr fov_map;

        // Skip the creature's action if it is not the player, and does not have LOS of the player.
        // This is necessary for speedup purposes when there are lots of creatures on the map.
        CreaturePtr player = get_current_player();

        if (current_creature->get_is_player() == false)
        {
          // The player shared pointer might be null (creature might be acting before the player
          // has been officially placed on the map).  Advance (skip) the creature's turn in this
          // case.
          if (!player)
          {
            action_cost.set_cost(current_creature->get_speed().get_current());
            advance = true;
            continue;
          }
          else
          {
            // Quick and dirty - check to see if the tile distance between the player
            // and the creature is more than the creature's LOS.
            int distance = CoordUtils::chebyshev_distance(current_map->get_location(player->get_id()), current_map->get_location(current_creature->get_id()));

            // For now, burn a creature's action (do nothing!) if the creature falls outside
            // of the player's LOS.
            if (distance > CreatureConstants::DEFAULT_CREATURE_LINE_OF_SIGHT_LENGTH)
            {
              action_cost.set_cost(current_creature->get_speed().get_current());
              advance = true;
              continue;
            }
          }
        }

        Coordinate creature_coords = current_map->get_location(current_creature->get_id());
        view_map = ViewMapTranslator::create_view_map_around_tile(current_map, creature_coords, CreatureConstants::DEFAULT_CREATURE_LINE_OF_SIGHT_LENGTH /* FIXME */);
        
        FieldOfViewStrategyPtr fov_strategy = FieldOfViewStrategyFactory::create_field_of_view_strategy(current_creature->get_is_player());
        fov_map = fov_strategy->calculate(view_map, creature_coords, CreatureConstants::DEFAULT_CREATURE_LINE_OF_SIGHT_LENGTH /* FIXME */);

        DecisionStrategyPtr decision_strategy = current_creature->get_decision_strategy();
        
        if (decision_strategy)
        {
          decision_strategy->set_fov_map(fov_map);
        }
        
        if (current_creature->get_is_player())
        {
          update_display(current_creature, current_map, fov_map);
        }

        CommandPtr command = strategy->get_decision(current_creature->get_id(), game_command_factory, game_kb_command_map, view_map /* fov_map */);
        
        // Clear the stored messages if we're about to receive the player's action.
        // The player will already have had a chance to read the messages.
        if (current_creature->get_is_player())
        {
          MessageManager::instance().clear_if_necessary();
        }

        action_cost = CommandProcessor::process(current_creature, command, display);

        // Poor NPCs...they're discriminated against even at the code level!
        advance = action_cost.get_turn_advanced();
        
        // This is purely to suss out the weird pathfinding issues where monsters are trying to move
        // to bad locations.
        if (!advance && !current_creature->get_is_player())
        {
          int x = 1;
          advance = true; // REMOVE THIS WHEN I GET ENTHUSIASTIC AND WANT TO DEBUG THE WOES...
        }
      }
      
      // Update the current creature 
      CreatureCalculator::update_calculated_values(current_creature);
      
      // Also update its number of turns, as long as we should keep playing
      // (player hasn't saved, been killed, and so on)
      if (keep_playing)
      {
        current_creature->increment_turns();
      }
    }
  }
  
  return action_cost;
}

void Game::stop_playing()
{
  keep_playing = false;
}

bool Game::should_keep_playing() const
{
  return keep_playing;
}

void Game::reload_map()
{
  reload_game_loop = true;
}

void Game::detect_creatures_if_necessary(CreaturePtr player, const string& original_map_id)
{
  Detection detection;
  detection.detect_creatures_if_necessary(player, get_current_map(), original_map_id, current_map_id);
}

// Set the current map in the map registry.
void Game::set_current_map(MapPtr map)
{
  // Unload the current map
  string old_map_id = current_map_id;
  MapPtr old_map = map_registry.get_map(old_map_id);
  
  if (!old_map || !old_map->get_permanent())
  {
    map_registry.remove_map(old_map_id); // Boom.
  }
  
  // Make the new map the current
  current_map_id = map->get_map_id();
  map_registry.set_map(current_map_id, map);
}

// Get the current map from the map registry.
MapPtr Game::get_current_map() const
{
  return map_registry.get_map(current_map_id);
}

ActionManager& Game::get_action_manager_ref()
{
  return actions;
}

DeityActionManager& Game::get_deity_action_manager_ref()
{
  return deity_actions;
}

ScriptEngine& Game::get_script_engine_ref()
{
  return script_engine;
}

Mortuary& Game::get_mortuary_ref()
{
  return mortuary;
}

Quests& Game::get_quests_ref()
{
  return quests;
}

void Game::set_sid_ini_filename(const string& new_sid_ini_filename)
{
  sid_ini_filename = new_sid_ini_filename;
}

string Game::get_sid_ini_filename() const
{
  return sid_ini_filename;
}

WorldPtr Game::get_current_world()
{
  return worlds[current_world_ix];
}

LoadedMapDetails& Game::get_loaded_map_details_ref()
{
  return loaded_map_details;
}

bool Game::serialize(ostream& stream)
{
  Log::instance().trace("Game::serialize - start");

  // Write a synopsis about the player's character, to be used when viewing
  // the list of saved games.
  CreatureDescriber cd(get_current_player());
  Serialize::write_string(stream, cd.describe_for_save_file());

  // Ignore keep_playing
  Serialize::write_bool(stream, reload_game_loop);
  // Ignore game_instance - it's a singleton, and the write/read code is already handling it
  Serialize::write_class_id(stream, display->get_class_identifier());
  display->serialize(stream);

  map_registry.serialize(stream);

  // Ignore deity map - this will be built up on startup.
  // Ignore race map - this will be built up on startup.
  // Ignore class map - this will be built up on startup.
  // Ignore creature map - this will be built up on startup.
  // Ignore spell map - this will be built up on startup.

  // The creature generation values map needs to be serialized because it
  // contains information on the current and maximum allowable values for
  // generation.
  size_t cgv_size = creature_generation_values.size();
  Serialize::write_size_t(stream, cgv_size);

  if (cgv_size > 0)
  {
    BOOST_FOREACH(CreatureGenerationValuesMap::value_type& cgv_val, creature_generation_values)
    {
      Serialize::write_string(stream, cgv_val.first);
      cgv_val.second.serialize(stream);
    }
  }

  // Item generation values
  size_t igv_size = item_generation_values.size();
  Serialize::write_size_t(stream, igv_size);

  if (igv_size > 0)
  {
    BOOST_FOREACH(GenerationValuesMap::value_type& igv_val, item_generation_values)
    {
      Serialize::write_string(stream, igv_val.first);
      igv_val.second.serialize(stream);
    }
  }

  // Ignore items map - this will be built up on startup.
  // Ignore tile_info map - this will be built up on startup.

  size_t num_worlds = worlds.size();
  Serialize::write_size_t(stream, num_worlds);

  BOOST_FOREACH(WorldPtr world, worlds)
  {
    world->serialize(stream);
  }

  Serialize::write_uint(stream, current_world_ix);
  Serialize::write_string(stream, current_map_id);

  actions.serialize(stream);

  // deity_actions is stateless, and doesn't need to be saved.

  ac.serialize(stream);
    
  time_keeper.serialize(stream);

  // script engine is stateless, and doesn't need to be saved.

  mortuary.serialize(stream);

  quests.serialize(stream);

  // Ignore sid ini filename.

  // Game command factory and keyboard map get built up every time - don't save these.

  // Persist the map-redraw values so that the same logic can be applied after
  // a game is reloaded.
  loaded_map_details.serialize(stream);
    
  Log::instance().trace("Game::serialize - end");

  return true;
}

bool Game::deserialize(istream& stream)
{
  Log::instance().trace("Game::deserialize - start");

  Serialize::consume_string(stream); // character synopsis

  // Ignore keep_playing
  Serialize::read_bool(stream, reload_game_loop);
  // Ignore game_instance - it's a singleton, and the write/read code is already handling it
  
  ClassIdentifier display_ci;
  Serialize::read_class_id(stream, display_ci);
  display = DisplayFactory::create_display(display_ci);
  if (!display) return false;
  if (!display->deserialize(stream)) return false;

  map_registry.deserialize(stream);

  // Ignore deity map - this will be built up on startup.
  // Ignore race map - this will be built up on startup.
  // Ignore class map - this will be built up on startup.
  // Ignore creature map - this will be built up on startup.
  // Ignore spell map - this will be built up on startup.

  // Keep track of creature generation values for the current/maximum allowable
  // generation amounts.
  size_t cgv_size = 0;
  Serialize::read_size_t(stream, cgv_size);

  if (cgv_size > 0)
  {
    creature_generation_values.clear();

    for (uint i = 0; i < cgv_size; i++)
    {
      string creature_id;
      Serialize::read_string(stream, creature_id);

      CreatureGenerationValues cgv;
      cgv.deserialize(stream);

      creature_generation_values.insert(make_pair(creature_id, cgv));
    }
  }

  // Keep track of item generation values for current/maximum allowed,
  // same as for creatures.
  size_t igv_size = 0;
  Serialize::read_size_t(stream, igv_size);

  if (igv_size > 0)
  {
    item_generation_values.clear();

    for (uint i = 0; i < igv_size; i++)
    {
      string item_id;
      Serialize::read_string(stream, item_id);

      GenerationValues gv;
      gv.deserialize(stream);

      item_generation_values.insert(make_pair(item_id, gv));
    }
  }

  // Ignore items map - this will be built up on startup.
  // Ignore tile_info map - this will be built up on startup.

  size_t num_worlds;
  Serialize::read_size_t(stream, num_worlds);

  worlds.clear();

  for (unsigned int i = 0; i < num_worlds; i++)
  {
    WorldPtr world = WorldFactory::create_world();
    if (!world) return false;
    if (!world->deserialize(stream)) return false;
    worlds.push_back(world);
  }

  Serialize::read_uint(stream, current_world_ix);
  Serialize::read_string(stream, current_map_id);

  actions.deserialize(stream);

  // deity_actions is stateless, and doesn't need to be saved.
    
  ac.deserialize(stream);

  time_keeper.deserialize(stream);

  // script engine is stateless and doesn't need to be saved.

  mortuary.deserialize(stream);

  quests.deserialize(stream);

  // Ignore sid ini filename

  // Game command factory and keyboard map get built up every time - don't load these.

  loaded_map_details.deserialize(stream);

  Log::instance().trace("Game::deserialize - end");
  return true;
}

ClassIdentifier Game::internal_class_identifier() const
{
  return CLASS_ID_GAME;
}

#ifdef UNIT_TESTS
#include "unit_tests/Game_test.cpp"
#endif