#pragma once
#include "Creature.hpp"
#include "IActionManager.hpp"
#include "Readable.hpp"

class ActionManager;

class ReadAction : public IActionManager
{
  public:
    ActionCostValue read(CreaturePtr creature, ActionManager * const am);
    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:
    void read_item(CreaturePtr creature, ActionManager * const am, ReadablePtr readable);
    void add_read_message(CreaturePtr creature, ReadablePtr readable, const ItemIdentifier& item_id);
    bool check_on_world_map(CreaturePtr creature);
};

