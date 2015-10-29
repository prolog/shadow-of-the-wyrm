#include "DamageCalculator.hpp"

DamageCalculator::DamageCalculator(const AttackType new_attack_type, const PhaseOfMoonType new_pom_type)
: attack_type(new_attack_type), pom_type(new_pom_type)
{
}

DamageCalculator::~DamageCalculator()
{
}

double DamageCalculator::get_phase_of_moon_multiplier(const DamageType dt, const PhaseOfMoonType pom) const
{
  double mult = 1.0;

  if (dt == DamageType::DAMAGE_TYPE_HEAT || dt == DamageType::DAMAGE_TYPE_COLD || dt == DamageType::DAMAGE_TYPE_LIGHTNING || dt == DamageType::DAMAGE_TYPE_HOLY)
  {
    if (pom == PhaseOfMoonType::PHASE_OF_MOON_WAXING)
    {
      mult = 1.1;
    }
    else if (pom == PhaseOfMoonType::PHASE_OF_MOON_FULL)
    {
      mult = 1.2;
    }
  }
  else if (dt == DamageType::DAMAGE_TYPE_ACID || dt == DamageType::DAMAGE_TYPE_POISON || dt == DamageType::DAMAGE_TYPE_SHADOW || dt == DamageType::DAMAGE_TYPE_ARCANE)
  {
    if (pom == PhaseOfMoonType::PHASE_OF_MOON_WANING)
    {
      mult = 1.1;
    }
    else if (pom == PhaseOfMoonType::PHASE_OF_MOON_NEW)
    {
      mult = 1.2;
    }
  }

  return mult;
}
