#pragma once
#include <map>
#include "Creature.hpp"
#include "Screen.hpp"
#include "Display.hpp"

class SkillsScreen : public Screen
{
  public:
    SkillsScreen(DisplayPtr display, CreaturePtr creature, const SkillCategory category);

  protected:
    void initialize() override;

    CreaturePtr creature;
    SkillCategory category;
    std::map<SkillCategory, std::string> screen_titles;
    std::map<SkillCategory, std::pair<SkillType, SkillType>> skills_for_category;
};
