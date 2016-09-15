#pragma once
#include "SkillProcessor.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"

class ThieverySkillProcessor : public SkillProcessor
{
  public:
    ThieverySkillProcessor();

    virtual ActionCostValue process(CreaturePtr creature, MapPtr map) override;
    virtual bool already_stolen_from(CreaturePtr creature);

  protected:
    std::pair<bool, TileDirectionMap> check_for_adjacent_creatures(CreaturePtr creature, MapPtr map);
    ActionCostValue process_steal(CreaturePtr stealing_creature, CreaturePtr steal_creature, IMessageManager& manager);

    ActionCostValue get_default_skill_action_cost_value(CreaturePtr creature) const override;
};

