#pragma once
#include "SkillProcessor.hpp"
#include "WaterTypes.hpp"
#include "MapUtils.hpp"

class DisarmTrapsSkillProcessor : public SkillProcessor
{
  public:
    virtual ActionCostValue process(CreaturePtr creature, MapPtr map) override;

  protected:
    // Returns a count of the number of known traps, and a sparse direction
    // map containing only the directions and associated tiles that have
    // traps.
    std::pair<int, TileDirectionMap> count_known_traps(const TileDirectionMap& tdm);

    bool disarm_trap(const std::pair<int, TileDirectionMap>& known_traps, CreaturePtr creature, MapPtr map);
    void add_no_nearby_trap_message(CreaturePtr creature);

    ActionCostValue get_default_skill_action_cost_value(CreaturePtr creature) const override;
};

