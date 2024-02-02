#pragma once
#include <string>
#include <utility>
#include <vector>
#include "IActionManager.hpp"

class SoundSettingsAction : public IActionManager
{
  public:
    std::vector<std::pair<std::string, std::string>> get_sound_settings(CreaturePtr creature) const;
    ActionCostValue sound_actions(CreaturePtr creature) const;
    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:
    std::vector<std::pair<std::string, std::string>> get_sound_settings() const;
    std::string get_autopickup_type_string(CreaturePtr creature) const;
};

