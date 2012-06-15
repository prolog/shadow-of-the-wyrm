#pragma once
#include "IActionManager.hpp"
#include "Creature.hpp"

class SearchActionManager : public IActionManager
{
  public:
    bool search(CreaturePtr creature);

  protected:
    virtual uint get_current_action_cost() const;
};
