#include "Game.hpp"
#include "WorldGenerator.hpp"

using namespace std;

Game* Game::game_instance = NULL;

Game::Game()
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

void Game::set_tile_info(const vector<DisplayTile>& game_tiles)
{
  tile_info = game_tiles;
}

const vector<DisplayTile>& Game::get_tile_info_ref() const
{
  return tile_info;
}

void Game::create_new_world(CreaturePtr creature) // pass in the player
{
  WorldGenerator world_generator;
  MapPtr current_world = world_generator.generate();
  WorldPtr world(new World(current_world));
  worlds.push_back(world);

  // FIXME: Add creature to starting location.  There are a lot of steps here...fix this up.
  TilePtr tile = current_world->get_tile_at_location(WorldMapLocationTextKeys::STARTING_LOCATION);

  if (tile)
  {
    tile->set_creature(creature);
  }
  else
  {
    // FIXME: Logging would be useful to add, soon.
  }
}

void Game::go()
{
  // Main game loop goes here...
}
