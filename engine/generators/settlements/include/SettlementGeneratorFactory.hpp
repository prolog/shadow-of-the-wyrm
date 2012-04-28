#pragma once
#include "SettlementTypes.hpp"
#include "Generator.hpp"

// Generate a particular type of settlement
class SettlementGeneratorFactory
{
  public:
    static GeneratorPtr create_settlement_generator(const SettlementType settlement_type, MapPtr base_map);

  protected:
    SettlementGeneratorFactory();
    ~SettlementGeneratorFactory();
};
