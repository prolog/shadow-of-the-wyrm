#pragma once
#include "Creature.hpp"
#include "RarityTypes.hpp"

class CreatureGenerationManager
{
  public:
    CreatureGenerationManager();
    
    CreaturePtr generate_creature(const TileType map_terrain_type, const int danger_level, const Rarity rarity);
};
