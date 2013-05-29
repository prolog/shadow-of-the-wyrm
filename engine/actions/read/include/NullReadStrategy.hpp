#pragma once
#include "ReadStrategy.hpp"

class NullReadStrategy : public ReadStrategy
{
  public:
    ActionCostValue read(CreaturePtr creature, ActionManager * const am, ReadablePtr readable);

  protected:
    std::pair<std::string, std::string> get_player_and_monster_read_sids() const;
    ActionCostValue get_action_cost_value() const;
};
