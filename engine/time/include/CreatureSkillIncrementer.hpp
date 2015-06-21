#pragma once
#include "ICreatureRegeneration.hpp"
#include "IMessageManager.hpp"

class CreatureSkillIncrementer : public ICreatureRegeneration
{
  public:
    CreatureSkillIncrementer();
    CreatureSkillIncrementer(const uint new_minutes_interval);

    void tick(CreaturePtr creature, TilePtr tile, const ulonglong minutes_this_tick, const ulonglong total_minutes_elapsed) override;

  protected:
    bool update_skill_if_necessary(CreaturePtr creature, SkillPtr skill, IMessageManager& manager);

    int minutes_interval;
};
