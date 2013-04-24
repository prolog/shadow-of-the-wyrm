#pragma once
#include "AttackTypes.hpp"
#include "ISkillMarker.hpp"

class SkillMarkerFactory
{
  public:
    static ISkillMarkerPtr create_skill_marker(const AttackType attack_type);

  protected:
    SkillMarkerFactory();
    ~SkillMarkerFactory();
};
