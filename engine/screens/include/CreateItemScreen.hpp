#pragma once
#include "Screen.hpp"
#include "Item.hpp"
#include "SkillTypes.hpp"

class CreateItemScreen : public Screen
{
  public:
    CreateItemScreen(DisplayPtr display, const SkillType skill);

  protected:
    void initialize() override;

    // Get a list of craftable items based on the creation_skill property and
    // the current filter skill.
    std::vector<ItemPtr> get_craftable_items();

    SkillType filter_skill;
};
