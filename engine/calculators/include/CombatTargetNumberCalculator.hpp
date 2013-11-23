#pragma once
#include <memory>
#include "AttackTypes.hpp"
#include "Creature.hpp"

class CombatTargetNumberCalculator
{
  public:
    CombatTargetNumberCalculator(const AttackType new_attack_type) : attack_type(new_attack_type) {};

    virtual int calculate(CreaturePtr attacking_creature, CreaturePtr attacked_creature) = 0;

  protected:
    AttackType attack_type;
};

typedef std::shared_ptr<CombatTargetNumberCalculator> CombatTargetNumberCalculatorPtr;
