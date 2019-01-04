#pragma once
#include "ActionManager.hpp"
#include "Creature.hpp"
#include "RarityTypes.hpp"

class CreatureGenerationValues;

using CreatureGenerationMap = std::map<std::string, std::pair<std::shared_ptr<Creature>, CreatureGenerationValues>>;

class CreatureGenerationManager
{
  public:
    CreatureGenerationManager();
    
    CreatureGenerationMap generate_creature_generation_map(const TileType map_terrain_type, const bool permanent_map, const int min_danger_level, const int max_danger_level, const Rarity rarity, const std::map<std::string, std::string>& additional_properties);
    CreatureGenerationMap generate_ancient_beasts(const int max_danger_level, const TileType map_terrain_type);

    std::string select_creature_id_for_generation(ActionManager& am, CreatureGenerationMap& creature_generation_map);
    std::shared_ptr<Creature> generate_creature(ActionManager& am, CreatureGenerationMap& creature_generation_map, MapPtr map);
    
  protected:
    bool does_creature_match_generation_criteria(const CreatureGenerationValues& cgv, const TileType map_terrain_type, const bool permanent_map, const int min_danger_level, const int max_danger_level, const Rarity rarity, const bool ignore_level_checks, const std::string& required_race, const std::vector<std::string>& generator_filters, const std::vector<std::string>& preset_creature_ids);
};
