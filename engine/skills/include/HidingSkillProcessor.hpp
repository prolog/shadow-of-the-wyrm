#pragma once
#include "SkillProcessor.hpp"

class HidingSkillProcessor : public SkillProcessor
{
  public:
    ActionCostValue process(CreaturePtr creature, MapPtr map);

  protected:
    void add_already_hidden_message(CreaturePtr creature);
};

