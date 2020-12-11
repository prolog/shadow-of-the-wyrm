#pragma once
#include "BaseSettlementGenerator.hpp"

class WalledSettlementGenerator : public BaseSettlementGenerator
{
  public:
    WalledSettlementGenerator(MapPtr new_base_map);
    WalledSettlementGenerator(MapPtr new_base_map, const int new_growth_rate);

    virtual MapPtr generate(const Dimensions& dim) override;
    virtual MapPtr generate() override;

  protected:
    virtual void initialize();

    std::vector<std::shared_ptr<SectorFeature>> get_sector_features() override;
    
    virtual void generate_walled_settlement(MapPtr map);
    virtual void generate_walls(MapPtr map);
    virtual void generate_barracks(MapPtr map, const int north_wall, const int south_wall, const int east_wall, const int west_wall);
    virtual void generate_gate(MapPtr map);
    virtual void generate_inner_settlement(MapPtr map);
    virtual void generate_guards(MapPtr map, const int north_wall, const int south_wall, const int east_wall, const int west_wall);

    TileType wall_tile_type;
    int north_wall;
    int south_wall;
    int east_wall;
    int west_wall;
    int gate_row;
    int gate_col;
    CardinalDirection gate_wall;

    static const int MAX_NUM_GUARDS;
};
