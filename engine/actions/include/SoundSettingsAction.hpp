#pragma once
#include "ToggleSettingsAction.hpp"

class SoundSettingsAction : public ToggleSettingsAction
{
  public:
    ActionCostValue sound_actions(CreaturePtr creature);
    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:
    std::vector<std::pair<std::string, std::string>> get_settings_to_display(CreaturePtr creature) const override;
    void process_setting_if_necessary(CreaturePtr creature, const std::string& setting_name, const bool new_set_val) override;
};

