#pragma once
#include "Creature.hpp"
#include "Map.hpp"
#include "SkillProcessor.hpp"

class DetectionSkillProcessor : public SkillProcessor
{
  public:
    virtual ActionCostValue process(CreaturePtr player, MapPtr map) override;
};
