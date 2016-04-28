#pragma once
#include "SkillProcessor.hpp"

class FishingSkillProcessor : public SkillProcessor
{
  public:
    virtual ActionCostValue process(CreaturePtr creature, MapPtr map) override;

  protected:
    bool check_for_fishing_equipment(CreaturePtr creature);
    bool check_for_adjacent_water_tile(CreaturePtr creature, MapPtr map);
};

