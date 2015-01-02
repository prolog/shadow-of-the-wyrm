#pragma once

#include "common.hpp"
#include "Map.hpp"

enum struct RuinsType
{
  RUINS_TYPE_SETTLEMENT = 0,
  RUINS_TYPE_KEEP = 1
};

// JCD FIXME: Refactor this into SettlementRuinsGenerator and KeepRuinsGenerator.
class RuinsGenerator
{
  public:
    static MapPtr generate(MapPtr map, const RuinsType& = RUINS_TYPE_SETTLEMENT);

  protected:
    static MapPtr generate_ruined_settlement(MapPtr map);
    static MapPtr generate_ruined_keep(MapPtr map);

    // Helper functions
    static void create_keep(MapPtr map, const int start_row, const int start_col, const int height, const int width);
    static void populate_keep(MapPtr map, const int start_row, const int start_col, const int height, const int width);
    static void create_entrance(MapPtr map, const int start_row, const int start_col, const int height, const int width);
};
