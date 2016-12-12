#include "CombatTextKeys.hpp"
#include "MightyHitTypeCalculator.hpp"
#include "RNG.hpp"
#include "StringTable.hpp"

using namespace std;

// Mighty blows allow 75% of soak.
float MightyHitTypeCalculator::get_soak_multiplier() const
{
  return 0.75f;
}

string MightyHitTypeCalculator::get_combat_message() const
{
  string message = StringTable::get(CombatTextKeys::COMBAT_MIGHTY_BLOW_MESSAGE);
  return message;
}

// Mighty blows use 80% of the max damage.
int MightyHitTypeCalculator::get_base_damage(const Damage& damage) const
{
  return std::max(1, static_cast<int>(damage.max() * 0.80));
}

