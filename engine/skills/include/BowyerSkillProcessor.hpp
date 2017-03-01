#pragma once
#include "SkillProcessor.hpp"

class BowyerSkillProcessor : public SkillProcessor
{
  public:
    virtual ActionCostValue process(CreaturePtr creature, MapPtr map) override;

  protected:
    bool check_for_bough(CreaturePtr creature);
    void create_bowyer_item(const std::string& item_base_id, CreaturePtr creature, MapPtr map);
};


