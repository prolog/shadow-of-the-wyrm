#pragma once
#include "SkillProcessor.hpp"

class BeastmasterySkillProcessor : public SkillProcessor
{
  public:
    virtual ActionCostValue process(CreaturePtr creature, MapPtr map) override;
    virtual SkillProcessorPtr clone() override;

  protected:
    CreatureMap get_tameable_creatures(const CreatureMap& fov_creature_map);
    void tame_creatures(CreaturePtr taming_creature, const CreatureMap& tameable_creatures);
};


