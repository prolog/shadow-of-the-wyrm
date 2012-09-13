#pragma once
#include "Creature.hpp"
#include "IActionManager.hpp"
#include "Readable.hpp"

class ActionManager;

class ReadManager : public IActionManager
{
  public:
    ActionCostValue read(CreaturePtr creature, ActionManager * const am);

  protected:
    void read_item(CreaturePtr creature, ReadablePtr readable);
    void add_read_message(CreaturePtr creature, ReadablePtr readable, const ItemIdentifier& item_id);
    
    ActionCostValue get_action_cost_value() const;
};

