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
    
    CreatureGenerationIndex generate_creature_generation_map(const std::set<TileType>& map_terrain_types, const bool permanent_map, const bool islet, const MapType map_type, const int min_danger_level, const int max_danger_level, const Rarity rarity, const std::map<std::string, std::string>& additional_properties);
    CreatureGenerationIndex generate_ancient_beasts(const int max_danger_level, const MapType map_type, const TileType map_terrain_type);

    std::vector<std::string> get_creature_ids_with_property(const std::string& property_name);
    std::string select_creature_id_for_generation(ActionManager& am, const CreatureGenerationList& creature_generation_list);

    std::shared_ptr<Creature> generate_creature(ActionManager& am, const CreatureGenerationList& creature_generation_list, MapPtr map);

    std::shared_ptr<Creature> generate_follower(ActionManager& am, MapPtr map, const FollowerType ft, const int level, const std::string& race_id = "", const std::string& class_id = "");
    
    static const int ANCIENT_BEASTS_MIN_DANGER_LEVEL;
    static const int ADVENTURER_DEFAULT_LEVEL;
    static const int HIRELING_MIN_LEVEL;
    static const int HIRELING_MAX_LEVEL;

  protected:
    std::shared_ptr<Creature> generate_hireling(ActionManager& am, MapPtr map, const int level, const std::string& race_id, const std::string& class_id);
    std::shared_ptr<Creature> generate_adventurer(ActionManager& am, MapPtr map, const int level, const std::string& race_id, const std::string& class_id);
    void generate_follower_bestiary(CreaturePtr creature, const FollowerType ft);

    bool does_creature_match_generation_criteria(const CreatureGenerationValues& cgv, const std::set<TileType>& map_terrain_types, const bool permanent_map, const bool islet, const MapType map_type, const int min_danger_level, const int max_danger_level, const Rarity rarity, const bool ignore_level_checks, const std::string& required_race, const std::vector<std::string>& generator_filters, const std::vector<std::string>& preset_creature_ids);
};
