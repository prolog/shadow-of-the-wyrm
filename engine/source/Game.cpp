#include "Game.hpp"

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
// get_classes
