#pragma once
#include "Directions.hpp"
#include "BaseSettlementGenerator.hpp"

class SettlementGenerator : public BaseSettlementGenerator
{
  public:
    SettlementGenerator(MapPtr new_base_map);
    SettlementGenerator(MapPtr new_base_map, const int growth_rate);

    virtual MapPtr generate();
    virtual MapPtr generate(const Dimensions& dim);

  protected:
     MapPtr generate_roads_and_buildings(MapPtr map);
     MapPtr generate_settlement_with_square_and_cardinal_roads(MapPtr map);
     MapPtr generate_settlement_with_winding_road(MapPtr map);
     MapPtr populate_settlement(MapPtr map);

     MapPtr generate_square(MapPtr map, const int start_row, const int start_col, const int square_size);
};

typedef boost::shared_ptr<SettlementGenerator> SettlementGeneratorPtr;
