#include "Game.hpp"
#include "WorldGenerator.hpp"
#include "MapTranslator.hpp"

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

void Game::create_new_world(CreaturePtr creature) // pass in the player
{
  WorldGenerator world_generator;
  MapPtr current_world = world_generator.generate();
  WorldPtr world(new World(current_world));
  worlds.push_back(world);
  current_world_ix = (worlds.size() - 1);

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
  // Main game loop goes here...
  // while(keep_playing)
  // {
  WorldPtr current_world = worlds.at(current_world_ix);
  current_map = current_world->get_world();

  MapDisplayArea display_area = display->get_map_display_area();

  DisplayMap display_map = MapTranslator::create_display_map(current_map, display_area);
  display->draw(display_map);
  // }
}
