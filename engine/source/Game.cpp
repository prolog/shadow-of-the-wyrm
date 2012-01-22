#include "global_prototypes.hpp"
#include "Conversion.hpp"
#include "Game.hpp"
#include "CommandProcessor.hpp"
#include "CreatureTranslator.hpp"
#include "Log.hpp"
#include "WorldGenerator.hpp"
#include "MapTranslator.hpp"
#include "DisplayStatistics.hpp"
#include "MessageManager.hpp"

using namespace std;

Game* Game::game_instance = NULL;

// JCD FIXME: These items don't appear to be in the map.  Investigate!
// Once this is working, make sure there's a function that can "copy"
// items from their template versions.
void Game::FIXME_REMOVE_THIS_FUNCTION(CreaturePtr player)
{
  ItemMap::iterator item_it = items.find("cap");

  if (item_it != items.end())
  {
    actions.handle_item(player, ITEM_ACTION_EQUIP, item_it->second);
  }
  
  item_it = items.find("dagger");

  if (item_it != items.end())
  {
    actions.handle_item(player, ITEM_ACTION_EQUIP, item_it->second);
  }
  
  item_it = items.find("dirt");

  if (item_it != items.end())
  {
    actions.handle_item(player, ITEM_ACTION_PICK_UP, item_it->second);
  }
}

Game::Game()
: keep_playing(true), current_world_ix(0)
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
      current_world->add_or_update_location(WorldMapLocationTextKeys::CURRENT_PLAYER_LOCATION, c); // JCD FIXME: Can I delete CURRENT_PLAYER_LOCATION
      current_world->add_or_update_location(Uuid::to_string(creature->get_id()), c);
    }
  }
  else
  {
    Log::instance()->log("Couldn't get player's initial starting location!");
  }
}

void Game::go()
{
  MessageManager* manager = MessageManager::instance();
  CreaturePtr current_player = get_current_player();
  string welcome_message = TextMessages::get_welcome_message(current_player->get_name());
  manager->add_new_message(welcome_message);

  manager->send();

  WorldPtr current_world = worlds.at(current_world_ix);
  current_map = current_world->get_world();
  actions.set_current_map(current_map);


      FIXME_REMOVE_THIS_FUNCTION(current_player);
      
      
  // Main game loop.
  while(keep_playing)
  {
    vector<CreaturePtr> creatures = current_map->get_creatures();

    // JCD FIXME: Eventually, refactor this into a separate method.
    MapDisplayArea display_area = display->get_map_display_area();

    DisplayStatistics display_stats = CreatureTranslator::create_display_statistics(current_player);
    display->display(display_stats);

    DisplayMap display_map = MapTranslator::create_display_map(current_map, display_area);
    display->draw(display_map);

    // FIXME: Right now, I just get the actions of each creature, in order.  This doesn't follow the ultimate
    // model of action costs, etc.
    for (vector<CreaturePtr>::const_iterator c_it = creatures.begin(); c_it != creatures.end(); c_it++)
    {
      CreaturePtr current_creature = *c_it;

      if (current_creature)
      {
        DecisionStrategyPtr strategy = current_creature->get_decision_strategy();

        if (strategy)
        {
          CommandPtr command = strategy->get_decision();
          CommandProcessor::process(current_creature, command);
        }
      }
    }
  }
}

void Game::quit()
{
  keep_playing = false;
}
