#pragma once
#include "ISkillProcessor.hpp"

class DefaultSkillProcessor : public ISkillProcessor
{
  public:
    DefaultSkillProcessor();

    virtual ActionCostValue process(CreaturePtr creature, MapPtr map);
};

