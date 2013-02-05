#pragma once
#include "Creature.hpp"
#include "IActionManager.hpp"
#include "MapUtils.hpp"

class ChatManager : public IActionManager
{
  public:
    ActionCostValue chat(CreaturePtr creature) const;

  protected:
    friend class ActionManager;
    ChatManager();

    bool chat_single_creature(CreaturePtr querying_creature, CreaturePtr speaking_creature) const;
    bool chat_multiple_options(CreaturePtr querying_creature, const CreatureDirectionMap& creature_map) const;
    void add_chat_message(const std::string& chat_text_sid) const;

    ActionCostValue get_action_cost_value() const;
    ActionCostValue get_nochat_action_cost_value() const;
};

