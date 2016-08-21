#include "AmmunitionCalculator.hpp"
#include "Conversion.hpp"
#include "ItemProperties.hpp"
#include "RNG.hpp"

using namespace std;

// 2% chance of breakage, always, unless the item is an artifact.
const int AmmunitionCalculator::BASE_PCT_CHANCE_BREAKAGE = 2;
const int AmmunitionCalculator::BASE_PCT_CHANCE_SURVIVAL = 40;
const int AmmunitionCalculator::ARCHERY_SKILL_SURVIVAL_DIVISOR = 2;
const int AmmunitionCalculator::ITEM_WEIGHT_SURVIVAL_DIVISOR = 6;
const map<Weight, pair<int, int>> AmmunitionCalculator::AMMUNITION_STACK_RANGES = 
{{Weight(0), {1, 50}},
 {Weight(2, 0), {1, 20}},
 {Weight(8, 0), {1, 8}},
 {Weight(100, 0), {1, 3}}};

// Whether or not ammunition survives is determined by:
//
// - Base 40% chance
// - +1 for every 6oz. in weight
// - +1 for every 2 pts of Archery
bool AmmunitionCalculator::survives(CreaturePtr creature, ItemPtr ammunition)
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
                         + (creature->get_skills().get_skill(SkillType::SKILL_GENERAL_ARCHERY)->get_value() / ARCHERY_SKILL_SURVIVAL_DIVISOR)
                         + (ammunition->get_weight().get_weight() / ITEM_WEIGHT_SURVIVAL_DIVISOR);

      string item_destruction_s = ammunition->get_additional_property(ItemProperties::ITEM_PROPERTIES_DESTRUCTION_PCT_CHANCE);
      int item_destruction_pct = String::to_int(item_destruction_s);

      // The item destruction pct is a hard override, and doesn't consider
      // any skills, etc.
      if (RNG::percent_chance(item_destruction_pct))
      {
        survive = false;
      }

      if (rand > chance_survive)
      {
        survive = false;
      }
    }
  }

  return survive;
}

pair<int, int> AmmunitionCalculator::calculate_stack_size(ItemPtr ammo)
{
  pair<int, int> stack_size(1, 1);

  if (ammo != nullptr)
  {
    Weight weight = ammo->get_weight();
    
    for (const auto& weight_pair : AMMUNITION_STACK_RANGES)
    {
      if (weight > weight_pair.first)
      {
        stack_size = weight_pair.second;
      }
      else
      {
        break;
      }
    }
  }

  return stack_size;
}