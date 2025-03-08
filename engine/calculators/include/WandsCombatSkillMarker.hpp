#pragma once
#include "ISkillMarker.hpp"

class WandsCombatSkillMarker : public ISkillMarker
{
  public:
    virtual ~WandsCombatSkillMarker() = default;

    virtual std::vector<SkillType> get_marked_skills(CreaturePtr creature) const override;
};
