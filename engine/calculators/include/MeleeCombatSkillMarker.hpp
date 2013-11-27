#pragma once
#include "AttackTypes.hpp"
#include "ISkillMarker.hpp"

class MeleeCombatSkillMarker : public ISkillMarker
{
  public:
    MeleeCombatSkillMarker(const AttackType at);
    virtual std::vector<SkillType> get_marked_skills(CreaturePtr creature) const override;

  protected:
    AttackType attack_type;
};

