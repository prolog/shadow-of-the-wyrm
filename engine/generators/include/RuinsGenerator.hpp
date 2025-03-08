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
    using SOTW::Generator::generate;

    RuinsGenerator(const std::string& map_exit_id, const TileType tile_type, const RuinsType new_rt);
    virtual ~RuinsGenerator() = default;

    // MapTester version:
    MapPtr generate(MapPtr map, const RuinsType& = RuinsType::RUINS_TYPE_SETTLEMENT);
    // "real" version:
    MapPtr generate(const Dimensions& dim);

  protected:
    virtual bool get_permanence_default() const override;
    MapPtr generate_ruined_settlement(MapPtr map);

    RuinsType rt;
};
