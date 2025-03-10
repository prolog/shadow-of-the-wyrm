#pragma once
#include "ISkillMarker.hpp"

class MagicalCombatSkillMarker : public ISkillMarker
{
  public:
    virtual ~MagicalCombatSkillMarker() = default;

    virtual std::vector<SkillType> get_marked_skills(CreaturePtr creature) const override;
};
