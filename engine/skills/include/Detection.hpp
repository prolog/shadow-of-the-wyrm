#pragma once
#include "Creature.hpp"
#include "Map.hpp"
#include "ISkillProcessor.hpp"

class Detection : public ISkillProcessor
{
  public:
    virtual ActionCostValue process(CreaturePtr player, MapPtr map) override;
};
