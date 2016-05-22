#pragma once
#include <map>
#include "Creature.hpp"
#include "Screen.hpp"
#include "Display.hpp"

enum struct SkillsScreenMode
{
  SKILLS_SCREEN_MODE_SELECT_SKILL = 0,
  SKILLS_SCREEN_MODE_IMPROVE_SKILL = 1
};

class SkillsScreen : public Screen
{
  public:
    SkillsScreen(DisplayPtr display, CreaturePtr creature, const SkillCategory category, const SkillsScreenMode ssm);
    SkillType get_selected_skill(const char selection) const;

  protected:
    void initialize() override;

    CreaturePtr creature;
    SkillCategory category;
    SkillsScreenMode mode;
    std::map<SkillCategory, std::map<SkillsScreenMode, std::string>> screen_titles;
    std::map<SkillCategory, std::pair<SkillType, SkillType>> skills_for_category;
    std::vector<std::map<char, SkillType>> screen_selection_to_skill_map;
};
