#include "CombatTargetNumberCalculatorFactory.hpp"
#include "MagicalCombatTargetNumberCalculator.hpp"
#include "MeleeAndRangedCombatTargetNumberCalculator.hpp"
#include "WandsCombatTargetNumberCalculator.hpp"

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
    case AttackType::ATTACK_TYPE_MELEE_PRIMARY:
    case AttackType::ATTACK_TYPE_MELEE_SECONDARY:
    case AttackType::ATTACK_TYPE_MELEE_TERTIARY_UNARMED:
    case AttackType::ATTACK_TYPE_RANGED:
      tn_calc = std::make_unique<MeleeAndRangedCombatTargetNumberCalculator>(attack_type);
      break;
    case AttackType::ATTACK_TYPE_MAGICAL:
      tn_calc = std::make_unique<MagicalCombatTargetNumberCalculator>();
      break;
    case AttackType::ATTACK_TYPE_MAGICAL_WANDS:
      tn_calc = std::make_unique<WandsCombatTargetNumberCalculator>();
      break;
    default:
      break;
  }

  return tn_calc;
}
