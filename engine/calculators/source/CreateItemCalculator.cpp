#include "CreateItemCalculator.hpp"
#include "Creature.hpp"
#include "RNG.hpp"

const int CreateItemCalculator::PRIMARY_SKILL_DIVISOR = 6;
const int CreateItemCalculator::CRAFTING_SKILL_DIVISOR = 15;

int CreateItemCalculator::calc_potential_improvement_points(CreaturePtr creature, const SkillType create_skill)
{
  int improve_points = 0;

  if (creature != nullptr)
  {
    Skills& skills = creature->get_skills();

    improve_points += (skills.get_value_incr_marks(create_skill) / PRIMARY_SKILL_DIVISOR);
    improve_points += (skills.get_value_incr_marks(SkillType::SKILL_GENERAL_CRAFTING) / CRAFTING_SKILL_DIVISOR);
  }

  return improve_points;
}

// Determine a base quantity, plus a bonus based on the creation skill.
uint CreateItemCalculator::calc_quantity(ItemPtr creation_item, ItemPtr component_item, CreaturePtr creature, const SkillType creation_skill)
{
  int quantity = calc_quantity(creation_item, component_item);

  if (quantity > 0 && creature != nullptr)
  {
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

#ifdef UNIT_TESTS
#include "unit_tests/CreateItemCalculator_test.cpp"
#endif


