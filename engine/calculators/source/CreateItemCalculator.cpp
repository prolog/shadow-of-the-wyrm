#include "CreateItemCalculator.hpp"
#include "Creature.hpp"
#include "RNG.hpp"

const int CreateItemCalculator::PRIMARY_SKILL_DIVISOR = 6;
const int CreateItemCalculator::CRAFTING_SKILL_DIVISOR = 15;

int CreateItemCalculator::calc_potential_improvement_points(CreaturePtr creature, const SkillType create_skill, const ItemStatus item_status)
{
  int improve_points = 0;

  if (creature != nullptr)
  {
    Skills& skills = creature->get_skills();

    improve_points += (skills.get_value_incr_marks(create_skill) / PRIMARY_SKILL_DIVISOR);
    improve_points += (skills.get_value_incr_marks(SkillType::SKILL_GENERAL_CRAFTING) / CRAFTING_SKILL_DIVISOR);

    if (item_status == ItemStatus::ITEM_STATUS_BLESSED)
    {
      improve_points += 2;
    }
    else if (item_status == ItemStatus::ITEM_STATUS_CURSED)
    {
      improve_points -= 2;
    }
  }

  return std::max<int>(improve_points, 0);
}

// Determine a base quantity, plus a bonus based on the creation skill.
uint CreateItemCalculator::calc_quantity(ItemPtr creation_item, ItemPtr component_item, CreaturePtr creature, const SkillType creation_skill)
{
  int quantity = calc_quantity(creation_item, component_item);

  if (quantity > 0 && creature != nullptr)
  {
    quantity = static_cast<int>(quantity * get_quantity_multiplier(component_item));

    int skill_val = creature->get_skills().get_value(creation_skill);

    if (skill_val > 0)
    {
      quantity += RNG::range(1, std::max<int>(1, skill_val / 10));
    }
  }

  return quantity;
}

// Determine how many items can be created, by dividing the weight of the
// component item by the weight of the creation item.
uint CreateItemCalculator::calc_quantity(ItemPtr creation_item, ItemPtr component_item)
{
  int quantity = 0;

  if (creation_item != nullptr && component_item != nullptr)
  {
    uint creation_weight_oz = creation_item->get_weight().get_weight();
    uint component_weight_oz = component_item->get_weight().get_weight();
    quantity = (component_weight_oz / creation_weight_oz);
    quantity = std::max<uint>(1, quantity);
  }

  return quantity;
}

float CreateItemCalculator::get_quantity_multiplier(ItemPtr item)
{
  float multiplier = 1.0f;

  if (item != nullptr)
  {
    switch (item->get_status())
    {
      case ItemStatus::ITEM_STATUS_CURSED:
        multiplier = 0.50f;
        break;
      case ItemStatus::ITEM_STATUS_BLESSED:
        multiplier = 1.25f;
        break;
      case ItemStatus::ITEM_STATUS_UNCURSED:
      default:
        break;
    }
  }

  return multiplier;
}

#ifdef UNIT_TESTS
#include "unit_tests/CreateItemCalculator_test.cpp"
#endif


