#pragma once
#include "DigChances.hpp"
#include "ClassIdentifiers.hpp"

class DigChancesFactory
{
  public:
    static std::pair<bool, DigChances> create_feature_dig_chances(const ClassIdentifier ci);

  protected:
    DigChancesFactory();
    ~DigChancesFactory();
};

