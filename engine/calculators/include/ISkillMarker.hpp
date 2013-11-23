#pragma once
#include <vector>
#include <memory>
#include "Creature.hpp"
#include "SkillTypes.hpp"

// Interface to get the skills trained by a particular successful combat
// action.
class ISkillMarker
{
  public:
    virtual std::vector<SkillType> get_marked_skills(CreaturePtr creature) const = 0;
};

typedef std::shared_ptr<ISkillMarker> ISkillMarkerPtr;
