#pragma once
#include <string>
#include "DamageTypes.hpp"

class DamageFlag
{
  public:
    DamageFlag(const DamageFlagType dft, const std::string& desc_sid);

    DamageFlagType get_flag() const;
    std::string get_description_sid() const;

  protected:
    DamageFlagType flag;
    std::string description_sid;
};

