#include "CombatConstants.hpp"
#include "HitTypes.hpp"

HitTypeEnum HitTypeEnumConverter::from_successful_to_hit_roll(const int to_hit_roll)
{
  if (to_hit_roll >= CombatConstants::CRITICAL_DIFFICULTY)
  {
    return HitTypeEnum::HIT_TYPE_CRITICAL;
  }
  else if (to_hit_roll < CombatConstants::CRITICAL_DIFFICULTY && to_hit_roll >= CombatConstants::MIGHTY_BLOW_DIFFICULTY)
  {
    return HitTypeEnum::HIT_TYPE_MIGHTY;
  }
  else
  {
    return HitTypeEnum::HIT_TYPE_REGULAR;
  }
}

HitTypeEnumConverter::HitTypeEnumConverter()
{
}

#ifdef UNIT_TESTS
#include "unit_tests/HitTypes_test.cpp"
#endif