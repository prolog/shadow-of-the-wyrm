#pragma once
#include "ICreatureRegeneration.hpp"

class CreatureModifiers : public ICreatureRegeneration
{
  public:
    void tick(CreaturePtr creature, const ulonglong minutes_this_tick, const ulonglong total_minutes_elapsed) override;

  protected:
    void process_current_modifiers(CreaturePtr creature, const std::vector<std::pair<std::string, Modifier>>& current_modifiers);
    void add_removal_message(CreaturePtr creature, const std::string& spell_id);
};
