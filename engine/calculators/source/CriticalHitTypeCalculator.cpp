#include "CombatTextKeys.hpp"
#include "CriticalHitTypeCalculator.hpp"
#include "RNG.hpp"
#include "StringTable.hpp"

using namespace std;

// Critical blows do max damage, with 50% soak.
float CriticalHitTypeCalculator::get_soak_multiplier() const
{
  return 0.50f;
}

string CriticalHitTypeCalculator::get_combat_message() const
{
  string message = StringTable::get(CombatTextKeys::COMBAT_CRITICAL_HIT_MESSAGE);
  return message;
}

// Critical hits do max damage.
int CriticalHitTypeCalculator::get_base_damage(const Damage& damage) const
{
  return std::max(1, damage.max());
}

