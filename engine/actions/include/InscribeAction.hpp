#pragma once
#include "IActionManager.hpp"

class InscribeAction : public IActionManager
{
  public:
    ActionCostValue inscribe(CreaturePtr creature) const;

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:
    InscribeAction();

    void add_inscribe_on_world_map_message() const;
    void add_invalid_tile_super_type_message(const TileSuperType tst) const;

    std::map<TileSuperType, std::string> invalid_ts_messages;
    friend class ActionManager;
};
