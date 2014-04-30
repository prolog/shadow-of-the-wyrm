#pragma once
#include "ICryptLayoutStrategy.hpp"
#include "CryptLayoutTypes.hpp"

class CryptLayoutStrategyFactory
{
  public:
    static ICryptLayoutStrategyPtr create_layout_strategy(const CryptLayoutType layout_type);
};
