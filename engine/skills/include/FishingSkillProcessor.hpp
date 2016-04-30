#pragma once
#include "SkillProcessor.hpp"
#include "WaterTypes.hpp"

class FishingSkillProcessor : public SkillProcessor
{
  public:
    FishingSkillProcessor();

    virtual ActionCostValue process(CreaturePtr creature, MapPtr map) override;

  protected:
    bool check_for_fishing_equipment(CreaturePtr creature);
    std::pair<bool, WaterType> check_for_adjacent_water_tile(CreaturePtr creature, MapPtr map);
    void fish(CreaturePtr creature, MapPtr map, const WaterType water_type);

    ActionCostValue get_default_skill_action_cost_value(CreaturePtr creature) const override;
    std::map<WaterType, std::vector<std::string>> fish_types;
};

