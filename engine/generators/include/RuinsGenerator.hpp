#pragma once
#include "common.hpp"
#include "Generator.hpp"
#include "Map.hpp"

enum struct RuinsType
{
  RUINS_TYPE_SETTLEMENT = 0,
  RUINS_TYPE_KEEP = 1
};

// JCD FIXME: Refactor this into SettlementRuinsGenerator and KeepRuinsGenerator.
class RuinsGenerator : public SOTW::Generator
{
  public:
    RuinsGenerator(const std::string& map_exit_id, const TileType tile_type, const RuinsType new_rt);

    // MapTester version:
    MapPtr generate(MapPtr map, const RuinsType& = RuinsType::RUINS_TYPE_SETTLEMENT);
    // "real" version:
    MapPtr generate(const Dimensions& dim);

  protected:
    virtual bool get_permanence_default() const override;

    MapPtr generate_ruined_settlement(MapPtr map);
    MapPtr generate_ruined_keep(MapPtr map);

    // Helper functions
    void create_keep(MapPtr map, const int start_row, const int start_col, const int height, const int width);
    void populate_keep(MapPtr map, const int start_row, const int start_col, const int height, const int width);
    void create_entrance(MapPtr map, const int start_row, const int start_col, const int height, const int width);

    RuinsType rt;
};
