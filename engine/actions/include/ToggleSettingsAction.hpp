#pragma once
#include <string>
#include <utility>
#include <vector>
#include "IActionManager.hpp"

class ToggleSettingsAction : public IActionManager
{
	public:
		void show_settings(CreaturePtr creature, const std::string& screen_title_sid);
		virtual ActionCostValue get_action_cost_value(CreaturePtr creature) const override = 0;

	protected:
		virtual std::vector<std::pair<std::string, std::string>> get_settings_to_display() const = 0;
		virtual void process_setting_if_necessary(CreaturePtr creature, const std::string& setting_name, const bool new_set_value);
};
