#pragma once
#include <string>

class SkillsCommandKeys
{
  public:
    static const std::string GENERAL_SKILLS;
    static const std::string MELEE_WEAPON_SKILLS;
    static const std::string RANGED_WEAPON_SKILLS;
    static const std::string MAGIC_SKILLS;
    static const std::string SELECT_SKILL;
    static const std::string EXIT_SKILLS;

  protected:
    SkillsCommandKeys();
    ~SkillsCommandKeys();
};
