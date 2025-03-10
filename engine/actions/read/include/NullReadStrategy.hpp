#pragma once
#include "ReadStrategy.hpp"

class NullReadStrategy : public ReadStrategy
{
  public:
    ActionCostValue read(CreaturePtr creature, ReadablePtr readable) override;

  protected:
    std::pair<std::string, std::string> get_player_and_monster_read_sids() const override;
    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;
};
