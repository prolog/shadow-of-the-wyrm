#pragma once
#include "Creature.hpp"
#include "SkillTypes.hpp"

// Used for creating new items from a particular skill - Bowyer or Fletchery,
// currently.
class CreateItemCalculator
{
  public:
    int calc_potential_improvement_points(CreaturePtr creature, const SkillType create_skill, const ItemStatus item_status);
    uint calc_quantity(ItemPtr creation_item, ItemPtr component_item, CreaturePtr creature, const SkillType create_skill);
    uint calc_quantity(ItemPtr creation_item, ItemPtr component_item);

  protected:
    float get_quantity_multiplier(ItemPtr item);

    static const int PRIMARY_SKILL_DIVISOR;
    static const int CRAFTING_SKILL_DIVISOR;
};

