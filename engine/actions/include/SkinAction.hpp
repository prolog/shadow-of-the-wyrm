#pragma once
#include "IActionManager.hpp"
#include "Item.hpp"

class SkinAction : public IActionManager
{
  public:
    ActionCostValue skin(CreaturePtr creature, ActionManager * const am);
    
    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:
    friend class ActionManager;
    SkinAction();

    void add_skin_world_map_message(CreaturePtr creature);
    void add_no_corpses_message(CreaturePtr creature);
    void add_skin_successful_message(CreaturePtr creature);
    void add_mangled_corpse_skin_message(CreaturePtr creature);

    ActionCostValue attempt_skin(CreaturePtr creature, ItemPtr corpse, TilePtr tile);
    void create_skin_and_add_to_tile(CreaturePtr creature, ItemPtr corpse, TilePtr tile);
};
