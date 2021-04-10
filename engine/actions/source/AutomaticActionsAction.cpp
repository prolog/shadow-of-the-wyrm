#include "AutomaticActionsAction.hpp"
#include "Game.hpp"
#include "OptionScreen.hpp"
#include "ScreenTitleTextKeys.hpp"
#include "SettingTextKeys.hpp"
#include "Setting.hpp"
#include "TextMessages.hpp"

using namespace std;

map<int, pair<string, string>> AutomaticActionsAction::get_auto_action_settings() const
{
  map<int, pair<string, string>> settings = { { 0, { Setting::AUTOPICKUP, StringTable::get(SettingTextKeys::SETTING_AUTOPICKUP) } },
                                              { 1, { Setting::AUTOPICKUP_IGNORE_CORPSES, StringTable::get(SettingTextKeys::SETTING_AUTOPICKUP_EXCLUDE_CORPSES) } },
                                              { 2, { Setting::AUTOMELEE, StringTable::get(SettingTextKeys::SETTING_AUTOMELEE_AT_RANGE) } } };
  return settings;
}

ActionCostValue AutomaticActionsAction::automatic_actions() const
{
  Game& game = Game::instance();
  Settings& set = game.get_settings_ref();
  auto do_aa = true;

  while (do_aa)
  {
    auto settings = get_auto_action_settings();
    vector<string> options;

    for (const auto& aa_pair : settings)
    {
      options.push_back(aa_pair.second.first + "=" + aa_pair.second.second + ": " + StringTable::get(TextMessages::get_bool_sid(game.get_settings_ref().get_setting_as_bool(aa_pair.second.first))));
    }

    OptionScreen os(game.get_display(), ScreenTitleTextKeys::SCREEN_TITLE_AUTO_ACTIONS, {}, options);
    string display_s = os.display();
    int idx = -1;

    if (!display_s.empty())
    {
      idx = display_s[0] - 'a';
    }

    if (idx >= 0 && idx < static_cast<int>(settings.size()))
    {
      auto s_it = settings.find(idx);
      set.set_setting(s_it->second.first, std::to_string(!set.get_setting_as_bool(s_it->second.first)));
    }
    else
    {
      do_aa = false;
    }
  }

  // Display the Automatic Actions screen, which allows toggling autopickup,
  // automelee, etc.
  return get_action_cost_value(nullptr);
}

ActionCostValue AutomaticActionsAction::get_action_cost_value(CreaturePtr c) const
{
  return ActionCostConstants::NO_ACTION;
}
