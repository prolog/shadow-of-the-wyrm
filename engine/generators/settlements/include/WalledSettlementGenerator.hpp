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
    
    virtual void generate_walled_settlement(MapPtr map);
    virtual void generate_walls(MapPtr map);
    virtual void generate_gate(MapPtr map);
    virtual void generate_inner_settlement(MapPtr map);

    int north_wall;
    int south_wall;
    int east_wall;
    int west_wall;
    int gate_row;
    int gate_col;
    CardinalDirection gate_wall;
};
