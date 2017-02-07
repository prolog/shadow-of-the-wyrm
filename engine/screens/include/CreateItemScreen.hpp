#pragma once
#include "Screen.hpp"
#include "SkillTypes.hpp"

class CreateItemScreen : public Screen
{
  public:
    CreateItemScreen(DisplayPtr display, const SkillType skill);

  protected:
    void initialize() override;

    SkillType filter_skill;
};
