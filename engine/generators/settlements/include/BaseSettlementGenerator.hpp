#pragma once
#include <vector>
#include "Generator.hpp"
#include "Building.hpp"
#include "BuildingGenerationParameters.hpp"
#include "GardenTypes.hpp"
#include "SectorFeature.hpp"

class BaseSettlementGenerator : public SOTW::Generator
{
  public:
    using SOTW::Generator::generate;

    BaseSettlementGenerator(MapPtr new_base_map);
    BaseSettlementGenerator(MapPtr new_base_map, const int growth_rate);
    
    virtual MapPtr generate(const Dimensions& dim)  override = 0;
    virtual MapPtr generate() override = 0;

  protected:
    virtual bool get_permanence_default() const override;

    virtual std::vector<std::shared_ptr<SectorFeature>> get_sector_features();

    void generate_road_north(MapPtr map, const int start_row, const int start_col, const int road_length, const int probability, const int block_size_modifier = 0, bool recurse = true);
    void generate_road_south(MapPtr map, const int start_row, const int start_col, const int road_length, const int probability, const int block_size_modifier = 0, bool recurse = true);
    void generate_road_east(MapPtr map, const int start_row, const int start_col, const int road_length, const int probability, const int block_size_modifier = 0, bool recurse = true);
    void generate_road_west(MapPtr map, const int start_row, const int start_col, const int road_length, const int probability, const int block_size_modifier = 0, bool recurse = true);
    void generate_wells(MapPtr map);
    void generate_special_inhabitants(MapPtr map);

    bool get_ignore_creature_generation_level_checks() const override;

    MapPtr base_map;
    int growth_rate;
    int pct_chance_sector_feature;

    const int PROBABILITY_DECREMENT;
    const int WORKSHOP_PROBABILITY;
    const int BUILDING_PROBABILITY;
    const int MIN_BLOCK_SIZE;
    const int BLOCK_SIZE;
    const int NS_DIVISOR;
    const int EW_DIVISOR;
    const int WELLS_MIN;
    const int WELLS_MAX;
    const int HIRELING_PROBABILITY;

    std::vector<Building> buildings;
};
