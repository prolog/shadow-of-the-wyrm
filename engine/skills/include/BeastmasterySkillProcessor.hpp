#pragma once
#include "SkillProcessor.hpp"
#include "IMessageManager.hpp"
#include "Map.hpp"

class BeastmasterySkillProcessor : public SkillProcessor
{
  public:
    virtual ActionCostValue process(CreaturePtr creature, MapPtr map) override;
    virtual SkillProcessorPtr clone() override;

  protected:
    CreatureMap get_tameable_creatures(const CreatureMap& fov_creature_map);
    void tame_creatures(CreaturePtr taming_creature, const CreatureMap& tameable_creatures);

    void handle_tame(CreaturePtr taming_creature, CreaturePtr to_tame, IMessageManager& manager);
    void handle_anger(CreaturePtr taming_creature, const std::pair<std::string, CreaturePtr>& t_pair, MapPtr map, IMessageManager& manager);
};


