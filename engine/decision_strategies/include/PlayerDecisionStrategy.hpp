#pragma once
#include "Controller.hpp"
#include "DecisionStrategy.hpp"

class PlayerDecisionStrategy : public DecisionStrategy
{
  public:
    PlayerDecisionStrategy(ControllerPtr new_controller);
    virtual ~PlayerDecisionStrategy() = default;

    CommandPtr get_decision(const bool reprompt_on_cmd_not_found, const std::string& creature_id, CommandFactory* command_factory, KeyboardCommandMap* keyboard_commands, MapPtr view_map = nullptr, int* key_p = 0);
    CommandPtr get_nonmap_decision(const bool reprompt_on_cmd_not_found, const std::string& creature_id, CommandFactory* command_factory, KeyboardCommandMap* keyboard_commands, int* key_p = 0, const bool refresh_window = true);

    uint get_count(const uint max_count);
    bool get_confirmation(const bool confirmation_default_value = false, const bool require_proper_selection = false) override;
    bool get_attack_confirmation(CreaturePtr creature);

    DecisionStrategy* copy();

private:
    virtual ClassIdentifier internal_class_identifier() const override;
};
