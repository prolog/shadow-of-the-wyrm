#include "CreatureGenerationManager.hpp"
#include "Game.hpp"

CreatureGenerationManager::CreatureGenerationManager()
{
}

CreaturePtr CreatureGenerationManager::generate_creature(const TileType map_terrain_type, const int danger_level, const Rarity rarity)
{
  CreaturePtr creature;
  
  Game* game = Game::instance();
  
  if (game)
  {
  }
  
  return creature;
}
