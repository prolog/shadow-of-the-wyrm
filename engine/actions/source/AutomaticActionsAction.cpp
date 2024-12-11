#include "AutomaticActionsAction.hpp"
#include "DisplayItemTypeFactory.hpp"
#include "Game.hpp"
#include "OptionScreen.hpp"
#include "ScreenTitleTextKeys.hpp"
#include "SettingTextKeys.hpp"
#include "Setting.hpp"
#include "TextMessages.hpp"

using namespace std;

ActionCostValue AutomaticActionsAction::automatic_actions(CreaturePtr creature)
{
  show_settings(creature, ScreenTitleTextKeys::SCREEN_TITLE_AUTO_ACTIONS);

  // Display the Automatic Actions screen, which allows toggling autopickup,
  // automelee, etc.
  return get_action_cost_value(nullptr);
}

vector<pair<string, string>> AutomaticActionsAction::get_settings_to_display(CreaturePtr c) const
{
  Settings& settings = Game::instance().get_settings_ref();
  string weight_limit = settings.get_setting(Setting::AUTOPICKUP_IGNORE_ITEMS_OVER_WEIGHT_LBS);

  vector<pair<string, string>> action_set = { { Setting::AUTOPICKUP, Setting::AUTOPICKUP + "=" + StringTable::get(SettingTextKeys::SETTING_AUTOPICKUP) + " " + get_autopickup_type_string(c) + ": " + StringTable::get(TextMessages::get_bool_sid(c->get_decision_strategy()->get_autopickup())) },
                                              { Setting::AUTOPICKUP_IGNORE_CORPSES, Setting::AUTOPICKUP_IGNORE_CORPSES + "=" + StringTable::get(SettingTextKeys::SETTING_AUTOPICKUP_EXCLUDE_CORPSES) + ": " + StringTable::get(TextMessages::get_bool_sid(settings.get_setting_as_bool(Setting::AUTOPICKUP_IGNORE_CORPSES))) },
                                              { Setting::AUTOPICKUP_IGNORE_UNPAID, Setting::AUTOPICKUP_IGNORE_UNPAID + "=" + StringTable::get(SettingTextKeys::SETTING_AUTOPICKUP_EXCLUDE_UNPAID) + ": " + StringTable::get(TextMessages::get_bool_sid(settings.get_setting_as_bool(Setting::AUTOPICKUP_IGNORE_UNPAID))) },
                                              { Setting::AUTOPICKUP_IGNORE_ITEMS_OVER_WEIGHT, Setting::AUTOPICKUP_IGNORE_ITEMS_OVER_WEIGHT + "=" + SettingTextKeys::get_autopickup_exclude_over_weight_message(weight_limit) + ": " + StringTable::get(TextMessages::get_bool_sid(settings.get_setting_as_bool(Setting::AUTOPICKUP_IGNORE_ITEMS_OVER_WEIGHT))) },
                                              { Setting::AUTOMELEE, Setting::AUTOMELEE + "=" + StringTable::get(SettingTextKeys::SETTING_AUTOMELEE_AT_RANGE) + ": " + StringTable::get(TextMessages::get_bool_sid(c->get_decision_strategy()->get_automelee())) },
                                              { Setting::AUTOMOVE_ALWAYS_STOP_ON_ITEMS, Setting::AUTOMOVE_ALWAYS_STOP_ON_ITEMS + "=" + StringTable::get(SettingTextKeys::SETTING_AUTOMOVE_ALWAYS_STOP_ON_ITEMS) + ": " + StringTable::get(TextMessages::get_bool_sid(settings.get_setting_as_bool(Setting::AUTOMOVE_ALWAYS_STOP_ON_ITEMS))) } };
  return action_set;
}

string AutomaticActionsAction::get_autopickup_type_string(CreaturePtr creature) const
{
  ostringstream ss;

  if (creature != nullptr)
  {
    set<ItemType> autopickup_types = creature->get_decision_strategy()->get_autopickup_types();

    if (autopickup_types.empty())
    {
      ss << "-";
    }
    else
    {
      for (auto s_it = autopickup_types.begin(); s_it != autopickup_types.end(); s_it++)
      {
        DisplayItemTypePtr dit = DisplayItemTypeFactory::create(*s_it);

        if (dit != nullptr)
        {
          ss << dit->get_symbol();
        }
      }
    }
  }

  return ss.str();
}

void AutomaticActionsAction::process_setting_if_necessary(CreaturePtr creature, const string& setting_name, const bool new_set_val)
{
  if (setting_name == Setting::AUTOPICKUP)
  {
    creature->get_decision_strategy()->set_autopickup(new_set_val);
  }
  else if (setting_name == Setting::AUTOMELEE)
  {
    creature->get_decision_strategy()->set_automelee(new_set_val);
  }
}
ActionCostValue AutomaticActionsAction::get_action_cost_value(CreaturePtr) const
{
  return ActionCostConstants::NO_ACTION;
}
