#include "ItemEnchantmentCalculator.hpp"
#include "Random.hpp"
#include "RNG.hpp"

// Poisson distributions must have a non-zero mean (1, 2, etc).  Because of
// this, Poisson is only used when the danger level gets to a point where
// danger/6 is 1 or greater.  Before that, there is a chance for an
// enchantment based on the uniform random distribution.
int ItemEnchantmentCalculator::calculate_enchantments(const int danger_level)
{
  int enchants = RNG::range(0, danger_level / 4);

  if (danger_level >= 8)
  {
    PoissonDistribution pd(danger_level / 8);
    enchants = pd.next();
  }

  return enchants;
}
