#pragma once
#include "ToggleSettingsAction.hpp"

class AutomaticActionsAction : public ToggleSettingsAction
{
  public:
    ActionCostValue automatic_actions(CreaturePtr creature);
    ActionCostValue get_action_cost_value(CreaturePtr) const override;

  protected:
    std::vector<std::pair<std::string, std::string>> get_settings_to_display(CreaturePtr creature) const;
    std::string get_autopickup_type_string(CreaturePtr creature) const;
    void process_setting_if_necessary(CreaturePtr creature, const std::string& setting_name, const bool new_set_value);
};

