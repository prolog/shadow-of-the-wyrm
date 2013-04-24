#pragma once
#include <vector>
#include <boost/shared_ptr.hpp>
#include "Creature.hpp"
#include "SkillTypes.hpp"

// Interface to get the skills trained by a particular successful combat
// action.
class ISkillMarker
{
  public:
    virtual std::vector<SkillType> get_marked_skills(CreaturePtr creature) const = 0;
};

typedef boost::shared_ptr<ISkillMarker> ISkillMarkerPtr;
