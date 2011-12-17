#include "Game.hpp"
#include "CreatureTranslator.hpp"
#include "WorldGenerator.hpp"
#include "MapTranslator.hpp"
#include "DisplayStatistics.hpp"
#include "MessageManager.hpp"

// JCD FIXME hack!
#include <ncurses.h>
// JCD FIXME

using namespace std;

Game* Game::game_instance = NULL;

Game::Game() : current_world_ix(0)
{
}

Game::~Game()
{
}

Game* Game::get_instance()
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

void Game::create_new_world(CreaturePtr creature) // pass in the player
{
  WorldGenerator world_generator;
  MapPtr current_world = world_generator.generate();
  WorldPtr world(new World(current_world));
  worlds.push_back(world);
  current_world_ix = (worlds.size() - 1);

  players.push_back(creature);

  // JCD FIXME: Refactor
  TilePtr tile = current_world->get_tile_at_location(WorldMapLocationTextKeys::STARTING_LOCATION);

  if (tile)
  {
    tile->set_creature(creature);

    // Set the starting location.
    if (creature->get_is_player())
    {
      Coordinate c = current_world->get_location(WorldMapLocationTextKeys::STARTING_LOCATION);
      current_world->add_location(WorldMapLocationTextKeys::CURRENT_PLAYER_LOCATION, c);
    }
  }
  else
  {
    // FIXME: Logging would be useful to add, soon.
  }
}

void Game::go()
{
  bool keep_playing = true;

  MessageManager* manager = MessageManager::get_instance();
  CreaturePtr current_player = get_current_player();
  string welcome_message = TextMessages::get_welcome_message(current_player->get_name());
  manager->add_new_message(welcome_message);

  // Main game loop.
  while(keep_playing)
  {
    // JCD FIXME: Eventually, refactor this into a separate method.
    manager->send();

    WorldPtr current_world = worlds.at(current_world_ix);
    current_map = current_world->get_world();

    MapDisplayArea display_area = display->get_map_display_area();

    DisplayStatistics display_stats = CreatureTranslator::create_display_statistics(current_player);
    display->display(display_stats);

    DisplayMap display_map = MapTranslator::create_display_map(current_map, display_area);
    display->draw(display_map);

    // FIXME: Ncurses specific, and horrifying.
    keep_playing = (getch() != 'q');
  }
}
