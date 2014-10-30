#pragma once
#include "ActionManager.hpp"
#include "Creature.hpp"
#include "RarityTypes.hpp"

class CreatureGenerationValues;

typedef std::map<std::string, std::pair<std::shared_ptr<Creature>, CreatureGenerationValues>> CreatureGenerationMap;

class CreatureGenerationManager
{
  public:
    CreatureGenerationManager();
    
    CreatureGenerationMap generate_creature_generation_map(const TileType map_terrain_type, const int min_danger_level, const int max_danger_level, const Rarity rarity);
    std::shared_ptr<Creature> generate_creature(ActionManager& am, CreatureGenerationMap& creature_generation_map);
    
  protected:
    bool does_creature_match_generation_criteria(const CreatureGenerationValues& cgv, const TileType map_terrain_type, const int min_danger_level, const int max_danger_level, const Rarity rarity);
};
