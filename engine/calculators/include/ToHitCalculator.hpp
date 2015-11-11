#pragma once
#include "AttackTypes.hpp"
#include "Creature.hpp"

class ToHitCalculator
{
  public:
    ToHitCalculator();
    ToHitCalculator(const AttackType new_attack_type);
    
    virtual int calculate(CreaturePtr creature) = 0;
    
  protected:
    virtual int get_level_bonus(CreaturePtr creature);
    virtual int get_weapon_bonus(CreaturePtr creature);
    virtual int get_modifier_bonus(CreaturePtr creature);
    
    AttackType attack_type;
    static const int NWP_SKILL_BONUS_DIVISOR;
};

using ToHitCalculatorPtr = std::shared_ptr<ToHitCalculator>;
