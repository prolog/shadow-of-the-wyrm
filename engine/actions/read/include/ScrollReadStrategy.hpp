#pragma once
#include "ReadStrategy.hpp"

class ScrollReadStrategy : public ReadStrategy
{
  public:
    ActionCostValue read(CreaturePtr creature, ReadablePtr readable) override;

  protected:
    virtual std::pair<std::string, std::string> get_player_and_monster_read_sids() const override;
};
