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
    virtual ~ISkillMarker() = default;

    virtual std::vector<SkillType> get_marked_skills(CreaturePtr creature) const = 0;
};

using ISkillMarkerPtr = std::unique_ptr<ISkillMarker>;
