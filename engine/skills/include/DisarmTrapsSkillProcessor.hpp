#pragma once
#include "SkillProcessor.hpp"
#include "WaterTypes.hpp"
#include "MapUtils.hpp"

class DisarmTrapsSkillProcessor : public SkillProcessor
{
  public:
    virtual ActionCostValue process(CreaturePtr creature, MapPtr map) override;

  protected:
    bool has_known_trap(const TileDirectionMap& tdm);

    void add_no_nearby_trap_message(CreaturePtr creature);

    ActionCostValue get_default_skill_action_cost_value(CreaturePtr creature) const override;
};

