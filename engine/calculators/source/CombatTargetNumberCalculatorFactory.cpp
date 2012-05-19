#include <boost/make_shared.hpp>
#include "CombatTargetNumberCalculatorFactory.hpp"
#include "MagicalCombatTargetNumberCalculator.hpp"
#include "MeleeAndRangedCombatTargetNumberCalculator.hpp"
using boost::make_shared;

CombatTargetNumberCalculatorFactory::CombatTargetNumberCalculatorFactory()
{
}

CombatTargetNumberCalculatorFactory::~CombatTargetNumberCalculatorFactory()
{
}

// Create a combat target number calculator based on the attack type
// provided.
CombatTargetNumberCalculatorPtr CombatTargetNumberCalculatorFactory::create_target_number_calculator(const AttackType attack_type)
{
  CombatTargetNumberCalculatorPtr tn_calc;

  switch(attack_type)
  {
    case ATTACK_TYPE_MELEE_PRIMARY:
    case ATTACK_TYPE_MELEE_SECONDARY:
    case ATTACK_TYPE_RANGED:
      tn_calc = make_shared<MeleeAndRangedCombatTargetNumberCalculator>(attack_type);
      break;
    case ATTACK_TYPE_MAGICAL:
      tn_calc = make_shared<MagicalCombatTargetNumberCalculator>();
      break;
    default:
      break;
  }

  return tn_calc;
}
