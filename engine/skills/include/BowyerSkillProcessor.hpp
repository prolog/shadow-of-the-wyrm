#pragma once
#include "SkillProcessor.hpp"

class BowyerSkillProcessor : public SkillProcessor
{
  public:
    virtual ActionCostValue process(CreaturePtr creature, MapPtr map) override;

  protected:
    bool check_for_bough(CreaturePtr creature);
};

