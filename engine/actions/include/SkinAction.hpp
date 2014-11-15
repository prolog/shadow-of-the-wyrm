#pragma once
#include "IActionManager.hpp"

class SkinAction : public IActionManager
{
  public:
    ActionCostValue skin(CreaturePtr creature, const ActionManager * const am);
    
  protected:
    friend class ActionManager;
    SkinAction();

    void add_skin_world_map_message(CreaturePtr creature);
    void add_no_corpses_message(CreaturePtr creature);

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;
};
