#pragma once
#include "SkillProcessor.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"

class ThieverySkillProcessor : public SkillProcessor
{
  public:
    ThieverySkillProcessor();

    virtual ActionCostValue process(CreaturePtr creature, MapPtr map) override;

  protected:
    std::pair<bool, TileDirectionMap> check_for_adjacent_creatures(CreaturePtr creature, MapPtr map);
    ActionCostValue process_steal(CreaturePtr stealing_creature, CreaturePtr steal_creature);
    CreaturePtr get_steal_creature(const TileDirectionMap& tdm, CreaturePtr stealing_creature, MapPtr map);

    bool is_stealing_from_self(CreaturePtr stealing_creature, CreaturePtr steal_creature, IMessageManager& manager);
    bool is_already_stolen_from(CreaturePtr stealing_creature, CreaturePtr steal_creature, IMessageManager& manager);
    bool has_pockets(CreaturePtr stealing_creature, CreaturePtr steal_creature, IMessageManager& manager);
    bool confirm_steal(CreaturePtr stealing_creature, CreaturePtr steal_creature, IMessageManager& manager);

    ActionCostValue get_default_skill_action_cost_value(CreaturePtr creature) const override;
};

