#pragma once
#include "SkillProcessor.hpp"

class FletcherySkillProcessor : public SkillProcessor
{
  public:
    virtual ActionCostValue process(CreaturePtr creature, MapPtr map) override;
    virtual SkillProcessorPtr clone() override;

  protected:
    bool check_for_branch(CreaturePtr creature);
    void create_projectiles(const std::string& item_base_id, CreaturePtr creature, MapPtr map);
};


