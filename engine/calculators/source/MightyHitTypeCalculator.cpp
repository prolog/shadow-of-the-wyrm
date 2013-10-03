#include "CombatTextKeys.hpp"
#include "MightyHitTypeCalculator.hpp"
#include "RNG.hpp"
#include "StringTable.hpp"

using namespace std;

// Mighty blows do max damage, regular soak.
float MightyHitTypeCalculator::get_soak_multiplier() const
{
  return 1.0f;
}

string MightyHitTypeCalculator::get_combat_message() const
{
  string message = StringTable::get(CombatTextKeys::COMBAT_MIGHTY_BLOW_MESSAGE);
  return message;
}

// Mighty blows use the max damage.
int MightyHitTypeCalculator::get_base_damage(const Damage& damage) const
{
  return damage.max();
}

