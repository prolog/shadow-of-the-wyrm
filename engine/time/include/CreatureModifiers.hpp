#pragma once
#include "ICreatureRegeneration.hpp"

class CreatureModifiers : public ICreatureRegeneration
{
  public:
    void tick(CreaturePtr creature, const ulonglong minutes_this_tick, const ulonglong total_minutes_elapsed) override;

  protected:
    void add_removal_message(CreaturePtr creature);
};
