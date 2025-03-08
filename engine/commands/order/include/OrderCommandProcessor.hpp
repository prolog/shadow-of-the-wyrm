#pragma once
#include "ActionCost.hpp"
#include "Creature.hpp"

class OrderCommandProcessor
{
  public:
    static ActionCostValue process(CreaturePtr creature, Command* command, const std::string& follower_ids);

  protected:
    OrderCommandProcessor();
    ~OrderCommandProcessor();
};
