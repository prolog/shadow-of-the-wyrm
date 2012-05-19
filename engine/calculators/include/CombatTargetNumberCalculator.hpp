#pragma once
#include <boost/shared_ptr.hpp>
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

typedef boost::shared_ptr<CombatTargetNumberCalculator> CombatTargetNumberCalculatorPtr;
