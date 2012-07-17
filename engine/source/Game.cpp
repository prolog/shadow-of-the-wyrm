#include <boost/make_shared.hpp>
#include "global_prototypes.hpp"
#include "ActionCoordinator.hpp"
#include "Conversion.hpp"
#include "CreatureCalculator.hpp"
#include "CreatureFeatures.hpp"
#include "Detection.hpp"
#include "FieldOfViewStrategy.hpp"
#include "FieldOfViewStrategyFactory.hpp"
#include "Game.hpp"
#include "CommandProcessor.hpp"
#include "CreatureTranslator.hpp"
#include "Log.hpp"
#include "MapUtils.hpp"
#include "WorldGenerator.hpp"
#include "MapTranslator.hpp"
#include "DisplayStatistics.hpp"
#include "MessageManager.hpp"
#include "ViewMapTranslator.hpp"
#include "WorldTimeKeeperCoordinator.hpp"

using namespace std;
using boost::make_shared;

Game* Game::game_instance = NULL;

void Game::FIXME_REMOVE_THIS_FUNCTION(CreaturePtr player)
{
  actions.handle_item(player, ITEM_ACTION_EQUIP, ItemManager::create_item("cap"));
  actions.handle_item(player, ITEM_ACTION_EQUIP, ItemManager::create_item("dagger"));
  actions.handle_item(player, ITEM_ACTION_PICK_UP, ItemManager::create_item("dirt"));
  actions.handle_item(player, ITEM_ACTION_PICK_UP, ItemManager::create_item("coracle"));
}

Game::Game()
: keep_playing(true), reload_game_loop(false), current_world_ix(0)
{
}

Game::~Game()
{
}

Game* Game::instance()
{
  if (!game_instance)
  {
    game_instance = new Game();
  }

  return game_instance;
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

const CreatureMap& Game::get_creatures_ref() const
{
  return creatures;
}

void Game::set_creature_generation_values(const CreatureGenerationValuesMap& game_cgv)
{
  creature_generation_values = game_cgv;
}

const CreatureGenerationValuesMap& Game::get_creature_generation_values_ref() const
{
  return creature_generation_values;
}

void Game::set_items(const ItemMap& game_items)
{
  items = game_items;
}

const ItemMap& Game::get_items_ref() const
{
  return items;
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
  CreaturePtr current_player = players.at(current_world_ix);
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

  players.push_back(creature);

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
    Log::instance()->log("Couldn't get player's initial starting location!");
  }
}

// Update the display: the statistics area, and the current map.
void Game::update_display(CreaturePtr current_player, MapPtr current_map, MapPtr fov_map)
{
  if (current_player && current_map)
  {
    MapDisplayArea display_area = display->get_map_display_area();

    DisplayStatistics display_stats = CreatureTranslator::create_display_statistics(current_player);
    display->display(display_stats);

    DisplayMap display_map = MapTranslator::create_display_map(current_map, fov_map, display_area);
    display->draw(display_map);    
  }
}

void Game::go()
{
  game_command_factory = make_shared<CommandFactory>();
  game_kb_command_map = make_shared<KeyboardCommandMap>();

  WorldTimeKeeperCoordinator time_coordinator;
  time_coordinator.setup_time_keeper(time_keeper);
  
  CreaturePtr current_player = get_current_player();
  string welcome_message = TextMessages::get_welcome_message(current_player->get_name());

  MessageManager* manager = MessageManager::instance();
  manager->add_new_message(welcome_message);
  manager->send();

  MapPtr current_map = get_current_map();

      FIXME_REMOVE_THIS_FUNCTION(current_player);
 
  string map_id = "";

  // Main game loop.
  while(keep_playing)
  {
    detect_creatures_if_necessary(current_player, map_id);
        
    current_map = get_current_map();
    map_id = current_map_id;

    map<string, CreaturePtr> map_creatures = current_map->get_creatures();

    ActionCoordinator ac;
    ac.set(map_creatures);

    Calendar& calendar = worlds[current_world_ix]->get_calendar();
    
    while (ac.has_actions())
    {      
      // Update the list of creatures after each action; otherwise, creatures that are killed
      // might persist.
      map_creatures = current_map->get_creatures();

      CreaturePtr current_creature;
      ActionCost next_action_cost = ac.get_next_action_cost();
      string creature_id = ac.get_next_creature_id_and_update_actions();      
      map<string, CreaturePtr>::iterator c_it = map_creatures.find(creature_id);

      if (c_it != map_creatures.end())
      {
        current_creature = c_it->second;
      }
      
      if (current_creature)
      {
        // If we shouldn't keep playing (player has quit, has been killed, etc), then break out of the 
        // game loop.
        if (!keep_playing) break;
        
        process_elapsed_time(calendar, next_action_cost);

        // Player may have been killed by some time-related effect.
        if (!keep_playing) break;
                
        ActionCost action_cost = process_action_for_creature(current_creature, current_map);
        ac.add(action_cost, current_creature->get_id());
        
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
        MapPtr view_map;
        MapPtr fov_map;

        Coordinate creature_coords = current_map->get_location(current_creature->get_id());
        view_map = ViewMapTranslator::create_view_map_around_tile(current_map, creature_coords, CreatureConstants::DEFAULT_CREATURE_LINE_OF_SIGHT_LENGTH /* FIXME */);
        
        FieldOfViewStrategyPtr fov_strategy = FieldOfViewStrategyFactory::create_field_of_view_strategy(current_creature->get_is_player());
        fov_map = fov_strategy->calculate(view_map, creature_coords, CreatureConstants::DEFAULT_CREATURE_LINE_OF_SIGHT_LENGTH /* FIXME */);

        if (current_creature->get_is_player())
        {
          update_display(current_creature, current_map, fov_map);
        }
        
        CommandPtr command = strategy->get_decision(current_creature->get_id(), game_command_factory, game_kb_command_map, view_map /* fov_map */);
        
        // Clear the stored messages if we're about to receive the player's action.
        // The player will already have had a chance to read the messages.
        if (current_creature->get_is_player())
        {
          MessageManager::instance()->clear_if_necessary();
        }

        action_cost = CommandProcessor::process(current_creature, command, display);
        advance = action_cost.get_turn_advanced();
      }
      
      // Update the current creature as well as its number of turns.
      CreatureCalculator::update_calculated_values(current_creature);
      current_creature->increment_turns();
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
MapPtr Game::get_current_map()
{
  return map_registry.get_map(current_map_id);
}

