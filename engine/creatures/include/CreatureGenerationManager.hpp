#pragma once
#include "ActionManager.hpp"
#include "Creature.hpp"
#include "CreatureGenerationIndex.hpp"
#include "RarityTypes.hpp"

enum struct FollowerType
{
  FOLLOWER_TYPE_HIRELING = 0,
  FOLLOWER_TYPE_ADVENTURER = 1
};

class CreatureGenerationManager
{
  public:
    CreatureGenerationManager();
    
    CreatureGenerationIndex generate_creature_generation_map(const TileType map_terrain_type, const bool permanent_map, const int min_danger_level, const int max_danger_level, const Rarity rarity, const std::map<std::string, std::string>& additional_properties);
    CreatureGenerationIndex generate_ancient_beasts(const int max_danger_level, const MapType map_type, const TileType map_terrain_type);

    std::string select_creature_id_for_generation(ActionManager& am, CreatureGenerationList& creature_generation_list);

    std::shared_ptr<Creature> generate_creature(ActionManager& am, CreatureGenerationList& creature_generation_list, MapPtr map);

    std::shared_ptr<Creature> generate_follower(ActionManager& am, MapPtr map, const FollowerType ft, const int level);
    
    static const int ANCIENT_BEASTS_MIN_DANGER_LEVEL;
    static const int ADVENTURER_DEFAULT_LEVEL;
    static const int HIRELING_MIN_LEVEL;
    static const int HIRELING_MAX_LEVEL;

  protected:
    std::shared_ptr<Creature> generate_hireling(ActionManager& am, MapPtr map, const int level);
    std::shared_ptr<Creature> generate_adventurer(ActionManager& am, MapPtr map, const int level);

    bool does_creature_match_generation_criteria(const CreatureGenerationValues& cgv, const TileType map_terrain_type, const bool permanent_map, const int min_danger_level, const int max_danger_level, const Rarity rarity, const bool ignore_level_checks, const std::string& required_race, const std::vector<std::string>& generator_filters, const std::vector<std::string>& preset_creature_ids);
};
