#pragma once
#include "ISkillMarker.hpp"

class RangedCombatSkillMarker : public ISkillMarker
{
  public:
    virtual ~RangedCombatSkillMarker() = default;

    virtual std::vector<SkillType> get_marked_skills(CreaturePtr creature) const override;
};
