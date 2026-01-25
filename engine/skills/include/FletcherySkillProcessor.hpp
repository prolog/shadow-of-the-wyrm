#pragma once
#include "SkillProcessor.hpp"
#include "ItemTypes.hpp"

class FletcherySkillProcessor : public SkillProcessor
{
  public:
    virtual ActionCostValue process(CreaturePtr creature, MapPtr map) override;
    virtual SkillProcessorPtr clone() override;

  protected:
    std::pair<bool, ItemStatus> check_for_branch(CreaturePtr creature);
    void create_projectiles(const std::string& item_base_id, const ItemStatus item_status, CreaturePtr creature, MapPtr map);
};


