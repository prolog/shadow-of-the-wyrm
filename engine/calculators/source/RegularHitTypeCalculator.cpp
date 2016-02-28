#include <algorithm>
#include "RegularHitTypeCalculator.hpp"
#include "RNG.hpp"

using namespace std;

// A regular hit doesn't alter a creature's soak at all.
float RegularHitTypeCalculator::get_soak_multiplier() const
{
  return 1.0f;
}

// Regular hits don't have additional combat messages.
string RegularHitTypeCalculator::get_combat_message() const
{
  string no_message;
  return no_message;
}

// The base damage for a regular hit is just the damage roll
int RegularHitTypeCalculator::get_base_damage(const Damage& damage) const
{
  return std::max(1, RNG::dice(damage));
}

