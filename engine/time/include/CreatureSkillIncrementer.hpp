#pragma once
#include "ICreatureRegeneration.hpp"

class CreatureSkillIncrementer : public ICreatureRegeneration
{
  public:
    CreatureSkillIncrementer();
    CreatureSkillIncrementer(const uint new_minutes_interval);

    void tick(CreaturePtr creature, const ulonglong minutes_this_tick, const ulonglong total_minutes_elapsed) override;

  protected:
    int minutes_interval;
};
