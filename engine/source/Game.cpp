#include "global_prototypes.hpp"
#include "Conversion.hpp"
#include "CreatureCalculator.hpp"
#include "Game.hpp"
#include "CommandProcessor.hpp"
#include "CreatureTranslator.hpp"
#include "Log.hpp"
#include "MapUtils.hpp"
#include "WorldGenerator.hpp"
#include "MapTranslator.hpp"
#include "DisplayStatistics.hpp"
#include "MessageManager.hpp"

using namespace std;

Game* Game::game_instance = NULL;

void Game::FIXME_REMOVE_THIS_FUNCTION(CreaturePtr player)
{
  actions.handle_item(player, ITEM_ACTION_EQUIP, ItemManager::create_item("cap"));
  actions.handle_item(player, ITEM_ACTION_EQUIP, ItemManager::create_item("dagger"));
  actions.handle_item(player, ITEM_ACTION_PICK_UP, ItemManager::create_item("dirt"));
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
void Game::update_display(CreaturePtr current_player, MapPtr current_map)
{
  if (current_player && current_map)
  {
    MapDisplayArea display_area = display->get_map_display_area();

    DisplayStatistics display_stats = CreatureTranslator::create_display_statistics(current_player);
    display->display(display_stats);

    DisplayMap display_map = MapTranslator::create_display_map(current_map, display_area);
    display->draw(display_map);    
  }
}

void Game::go()
{
  CommandFactoryPtr game_command_factory = CommandFactoryPtr(new CommandFactory());
  KeyboardCommandMapPtr game_kb_command_map = KeyboardCommandMapPtr(new KeyboardCommandMap());
  
  MessageManager* manager = MessageManager::instance();
  CreaturePtr current_player = get_current_player();
  string welcome_message = TextMessages::get_welcome_message(current_player->get_name());
  manager->add_new_message(welcome_message);

  manager->send();

  MapPtr current_map = get_current_map();

      FIXME_REMOVE_THIS_FUNCTION(current_player);
      
  // Main game loop.
  while(keep_playing)
  {
    current_map = get_current_map();
    vector<CreaturePtr> map_creatures = current_map->get_creatures();

    // FIXME: Right now, I just get the actions of each creature, in order.  This doesn't follow the ultimate
    // model of action costs, etc.
    for (vector<CreaturePtr>::const_iterator c_it = map_creatures.begin(); c_it != map_creatures.end(); c_it++)
    {
      CreaturePtr current_creature = *c_it;

      if (current_creature)
      {        
        DecisionStrategyPtr strategy = current_creature->get_decision_strategy();

        if (strategy)
        {
          bool advance = false;
          
          while (!advance)
          {
            if (current_creature->get_is_player())
            {
              // Update the display with the result of the last round of actions.
              update_display(current_player, current_map);
            }
            
            CommandPtr command = strategy->get_decision(game_command_factory, game_kb_command_map);
            
            // Clear the stored messages if we're about to receive the player's action
            if (current_creature->get_is_player())
            {
              manager->clear_if_necessary();            
            }

            advance = CommandProcessor::process(current_creature, command, display);            
          }
          
          // Update the current creature
          CreatureCalculator::update_calculated_values(current_creature);
        }        
      }
      
      if (reload_game_loop)
      {
        reload_game_loop = false;
        break;
      }
    }
  }
}

void Game::quit()
{
  keep_playing = false;
}

void Game::reload_map()
{
  reload_game_loop = true;
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

