#include "ItemEnchantmentCalculator.hpp"
#include "Conversion.hpp"
#include "ItemProperties.hpp"
#include "Random.hpp"
#include "RNG.hpp"

const int ItemEnchantmentCalculator::BASE_CHANCE_BRAND = 15;

// Poisson distributions must have a non-zero mean (1, 2, etc).  Because of
// this, Poisson is only used when the danger level gets to a point where
// danger/6 is 1 or greater.  Before that, there is a chance for an
// enchantment based on the uniform random distribution.
int ItemEnchantmentCalculator::calculate_enchantments(const int danger_level) const
{
  int enchants = RNG::range(0, danger_level / 4);

  if (danger_level >= 8)
  {
    PoissonDistribution pd(danger_level / 8);
    enchants = pd.next();
  }

  return enchants;
}

int ItemEnchantmentCalculator::calculate_pct_chance_brand(const float pct_chance_multiplier, ItemPtr item) const
{
  int chance = 0;
  
  if (item != nullptr)
  {
    chance = static_cast<int>(BASE_CHANCE_BRAND * pct_chance_multiplier);

    chance = std::max<int>(chance, 0);
    chance = std::min<int>(chance, 100);

    bool brandable = String::to_bool(item->get_additional_property(ItemProperties::ITEM_PROPERTIES_BRANDABLE));
    bool already_branded = String::to_bool(item->get_additional_property(ItemProperties::ITEM_PROPERTIES_BRANDED));
    bool artifact = item->get_artifact();

    if (!brandable || artifact || already_branded)
    {
      chance = 0;
    }
  }

  return chance;
}

#ifdef UNIT_TESTS
#include "unit_tests/ItemEnchantmentCalculator_test.cpp"
#endif
