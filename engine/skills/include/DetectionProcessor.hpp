#pragma once
#include "Creature.hpp"
#include "Map.hpp"
#include "SkillProcessor.hpp"

class DetectionProcessor : public SkillProcessor
{
  public:
    virtual ActionCostValue process(CreaturePtr player, MapPtr map) override;
};
