#pragma once
#include "Creature.hpp"
#include "IActionManager.hpp"
#include "MapUtils.hpp"

class ChatAction : public IActionManager
{
  public:
    ActionCostValue chat(CreaturePtr creature) const;

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;
    ActionCostValue get_nochat_action_cost_value() const;

  protected:
    friend class ActionManager;
    ChatAction();

    bool chat_single_creature(CreaturePtr querying_creature, CreaturePtr speaking_creature) const;
    bool chat_multiple_options(CreaturePtr querying_creature, const CreatureDirectionMap& creature_map) const;
    void add_chat_message(CreaturePtr creature, const std::string& chat_text_sid) const;
};

