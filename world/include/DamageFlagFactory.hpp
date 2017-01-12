#pragma once
#include <map>
#include "DamageFlag.hpp"

class DamageFlagFactory
{
  public:
    DamageFlagFactory();

    DamageFlag create_damage_flag(const DamageFlagType dft);

  protected:
    std::map<DamageFlagType, std::string> description_sids;
};

