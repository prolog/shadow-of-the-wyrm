#include "ItemPietyCalculator.hpp"
#include "ConsumableConstants.hpp"
#include "Consumable.hpp"
#include "Conversion.hpp"
#include "CreatureFeatures.hpp"

const int ItemPietyCalculator::MINIMUM_PIETY = 10;
const int ItemPietyCalculator::MINIMUM_NUTRITION_FOR_PIETY = 1000;
const int ItemPietyCalculator::BASE_DIVISOR = 10;
const int ItemPietyCalculator::CORPSE_DIVISOR = 3;
const int ItemPietyCalculator::CURRENCY_DIVISOR = 3;
const int ItemPietyCalculator::ARTIFACT_DIVISOR = 2;
const float ItemPietyCalculator::CORPSE_PIETY_BASE_MULTIPLIER = 0.25f;
std::map<ItemType, int> ItemPietyCalculator::ITEM_TYPE_PIETY_DIVISORS = {};

ItemPietyCalculator::ItemPietyCalculator()
{
  if (ITEM_TYPE_PIETY_DIVISORS.empty())
  {
    init_item_type_pieties();
  }
}

void ItemPietyCalculator::init_item_type_pieties()
{
  ITEM_TYPE_PIETY_DIVISORS = { {ItemType::ITEM_TYPE_CURRENCY, 3} };
}

// Calculate the piety granted for the sacrifice of a particular item.
// - If the item's piety is less than the minimum piety, a piety of 0
//   is returned instead.
int ItemPietyCalculator::calculate_piety(ItemPtr item)
{
  int piety = 0;
  int item_piety = 0;
  int divisor = get_base_divisor(item);
  int base_value = get_base_value(item);
  float level_multiplier = get_corpse_level_multiplier(item);

  if (item)
  {
    // Since a stack of items can be sacrificed, ensure that this is properly
    // accounted for in the piety.
    item_piety = base_value;
    item_piety *= item->get_quantity();
    item_piety /= divisor;
    item_piety = static_cast<int>(static_cast<float>(item_piety) * level_multiplier);
  }

  if (item_piety > MINIMUM_PIETY)
  {
    piety = item_piety;
  }

  return piety;
}

int ItemPietyCalculator::get_item_type_piety_divisor(ItemPtr item)
{
  int divisor = BASE_DIVISOR;

  if (item != nullptr)
  {
    auto d_it = ITEM_TYPE_PIETY_DIVISORS.find(item->get_type());

    if (d_it != ITEM_TYPE_PIETY_DIVISORS.end())
    {
      divisor = d_it->second;
    }
  }

  return divisor;
}

float ItemPietyCalculator::get_corpse_level_multiplier(ItemPtr item)
{
  float mult = 1.0f;

  if (item != nullptr)
  {
    // If a corpse level property has been set, adjust the piety based on the level
    // of the corpse. Weenie creatures like imps and kestrels generate minimal
    // piety, whereas dragons etc generate a lot.
    // 
    // In practice, level 1 creatures give 27% of normal piety; level 50,
    // 125%
    std::string cl_s = item->get_additional_property(ConsumableConstants::CORPSE_LEVEL);
    if (!cl_s.empty())
    {
      float max_level = static_cast<float>(CreatureConstants::MAX_CREATURE_LEVEL);
      float corpse_level = String::to_float(cl_s);

      if (corpse_level > 0 && max_level > 0)
      {
        mult = CORPSE_PIETY_BASE_MULTIPLIER;
        mult += corpse_level / max_level;
      }
    }

  }

  return mult;
}

// Get the base value of an item.  For items that are not food, this is just
// the value of the item.  But because deities enjoy cereal offerings, the
// base value for food (whether apples, food rations, corpses, etc) is the
// nutritional value.
int ItemPietyCalculator::get_base_value(ItemPtr item)
{
  int base_value = 0;

  if (item)
  {
    if (item->get_type() == ItemType::ITEM_TYPE_FOOD || item->get_type() == ItemType::ITEM_TYPE_PLANT)
    {
      ConsumablePtr consumable = std::dynamic_pointer_cast<Consumable>(item);

      if (consumable)
      {
        // Base nutrition is used here, not calculated nutrition - the divine aren't
        // influenced by an item's status.
        int nutrition = consumable->get_nutrition();

        if (nutrition >= MINIMUM_NUTRITION_FOR_PIETY || consumable->get_effect_type() != EffectType::EFFECT_TYPE_NULL)
        {
          base_value = nutrition;
        }
      }
    }
    else
    {
      base_value = item->get_value();
    }
  }

  return base_value;
}

// Deities appreciate corpses more than anything else, so the divisor for
// corpses is much lower than for any other item.
int ItemPietyCalculator::get_base_divisor(ItemPtr item)
{
  int divisor = get_item_type_piety_divisor(item);

  if (item)
  {
    if (item->has_additional_property(ConsumableConstants::CORPSE_RACE_ID))
    {
      divisor = CORPSE_DIVISOR;
    }

    if (item->get_artifact())
    {
      divisor /= ARTIFACT_DIVISOR;
    }
  }

  return divisor;
}

#ifdef UNIT_TESTS
#include "unit_tests/ItemPietyCalculator_test.cpp"
#endif