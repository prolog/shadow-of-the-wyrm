#pragma once
#include "Creature.hpp"
#include "RarityTypes.hpp"

class CreatureGenerationValues;

class CreatureGenerationManager
{
  public:
    CreatureGenerationManager();
    
    CreaturePtr generate_creature(const TileType map_terrain_type, const uint danger_level, const Rarity rarity);
    
  protected:
    bool does_creature_match_generation_criteria(const CreatureGenerationValues& cgv, const TileType map_terrain_type, const uint danger_level, const Rarity rarity);
};
