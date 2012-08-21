#include "AmmunitionSurvivalCalculator.hpp"
#include "RNG.hpp"

// 2% chance of breakage, always, unless the item is an artifact.
const int AmmunitionSurvivalCalculator::BASE_PCT_CHANCE_BREAKAGE = 2;
const int AmmunitionSurvivalCalculator::BASE_PCT_CHANCE_SURVIVAL = 40;
const int AmmunitionSurvivalCalculator::ARCHERY_SKILL_SURVIVAL_DIVISOR = 2;
const int AmmunitionSurvivalCalculator::ITEM_WEIGHT_SURVIVAL_DIVISOR = 6;

// Whether or not ammunition survives is determined by:
//
// - Base 40% chance
// - +1 for every 6oz. in weight
// - +1 for every 2 pts of Archery
bool AmmunitionSurvivalCalculator::survives(CreaturePtr creature, ItemPtr ammunition)
{
  bool survive = true;

  if (creature && ammunition && !ammunition->get_artifact())
  {
    int rand = RNG::range(1, 100);

    // There's always a chance of breakage, unless the item is an artifact, which has
    // already been checked above.
    if (rand <= BASE_PCT_CHANCE_BREAKAGE)
    {
      survive = false;
    }
    else
    {
      // The chance for an item to survive is based on a base survival percentage, plus modifiers
      // due to skill in archery and how heavy the item is.
      int chance_survive = BASE_PCT_CHANCE_SURVIVAL
                         + (creature->get_skills().get_skill(SKILL_GENERAL_ARCHERY)->get_value() / ARCHERY_SKILL_SURVIVAL_DIVISOR)
                         + (ammunition->get_weight().get_weight() / ITEM_WEIGHT_SURVIVAL_DIVISOR);
                         
      if (rand > chance_survive)
      {
        survive = false;
      }
    }
  }

  return survive;
}
