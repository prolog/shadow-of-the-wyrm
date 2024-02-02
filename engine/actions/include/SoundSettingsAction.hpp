#pragma once
#include "ToggleSettingsAction.hpp"

class SoundSettingsAction : public ToggleSettingsAction
{
  public:
    ActionCostValue sound_actions(CreaturePtr creature);
    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:
    std::vector<std::pair<std::string, std::string>> get_settings_to_display(CreaturePtr creature) const override;
};

