#pragma once
#include "ReadStrategy.hpp"

class ScrollReadStrategy : public ReadStrategy
{
  public:
    ActionCostValue read(CreaturePtr creature, ActionManager * const am, ReadablePtr readable) override;

  protected:
    virtual std::pair<std::string, std::string> get_player_and_monster_read_sids() const override;
    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;
};
