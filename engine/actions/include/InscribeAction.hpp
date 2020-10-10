#pragma once
#include "IActionManager.hpp"

class InscribeAction : public IActionManager
{
  public:
    ActionCostValue inscribe(CreaturePtr creature) const;

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:
    InscribeAction();

    ActionCostValue create_inscription(CreaturePtr creature, TilePtr tile, const bool is_world_map) const;
    void add_inscription_super_type_message(const TileSuperType tst) const;

    static const size_t MAX_INSCRIPTION_LENGTH;
    std::map<TileSuperType, std::string> inscription_messages;
    friend class ActionManager;
};
