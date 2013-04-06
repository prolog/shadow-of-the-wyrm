#pragma once
#include <string>

class RangedCombatTextKeys
{
  public:
    static const std::string RANGED_COMBAT_UNAVAILABLE_ON_WORLD_MAP;
    static const std::string RANGED_COMBAT_WEAPON_NOT_EQUIPPED;
    static const std::string RANGED_COMBAT_AMMUNITION_NOT_EQUIPPED;
    static const std::string RANGED_COMBAT_WEAPON_AMMUNITION_MISMATCH;
    static const std::string RANGED_COMBAT_AMMUNITION_REQUIRES_RANGED_WEAPON;
    
  protected:
    RangedCombatTextKeys();
    ~RangedCombatTextKeys();
};
