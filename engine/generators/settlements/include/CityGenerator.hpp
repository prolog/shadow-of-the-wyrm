#pragma once
#include "BaseSettlementGenerator.hpp"

// At some point, I will look at the source for this class, and die a little.
class CityGenerator : public BaseSettlementGenerator
{
  public:
    CityGenerator(MapPtr new_base_map);
    CityGenerator(MapPtr new_base_map, const int growth_rate);

    MapPtr generate(const Dimensions& dim) override;
    MapPtr generate() override;

  protected:
    virtual int get_pct_chance_shop() const override;
    void initialize();
};
