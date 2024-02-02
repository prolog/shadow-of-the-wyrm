#include "SoundSettingsAction.hpp"
#include "DisplayItemTypeFactory.hpp"
#include "Game.hpp"
#include "OptionScreen.hpp"
#include "ScreenTitleTextKeys.hpp"
#include "SettingTextKeys.hpp"
#include "Setting.hpp"
#include "TextMessages.hpp"

using namespace std;

ActionCostValue SoundSettingsAction::sound_actions(CreaturePtr creature) const
{
  Game& game = Game::instance();
  Settings& set = game.get_settings_ref();
  bool do_ssa = true;

  while (creature != nullptr && do_ssa)
  {
    auto settings = get_sound_settings();
    vector<string> options;

    for (const auto& s : settings)
    {
      options.push_back(s.second);
    }

    OptionScreen os(game.get_display(), ScreenTitleTextKeys::SCREEN_TITLE_SOUND_ACTIONS, {}, options);
    string display_s = os.display();
    int idx = -1;

    if (!display_s.empty())
    {
      idx = display_s[0] - 'a';
    }

    if (idx >= 0 && idx < static_cast<int>(settings.size()))
    {
      auto s_val = settings[idx];

      string setting_id = s_val.first;
      bool new_set_value = !set.get_setting_as_bool(setting_id);
      set.set_setting(setting_id, std::to_string(new_set_value));

      /*
      if (setting_id == Setting::SOUND_ENABLED)
      {
        creature->get_decision_strategy()->set_autopickup(new_set_value);
      }
      else if (setting_id == Setting::AUTOMELEE)
      {
        creature->get_decision_strategy()->set_automelee(new_set_value);
      }*/
    }
    else
    {
      do_ssa = false;
    }
  }

  return get_action_cost_value(nullptr);
}

vector<pair<string, string>> SoundSettingsAction::get_sound_settings() const
{
  const Settings& settings = Game::instance().get_settings_ref();

  vector<pair<string, string>> sound_settings = { { Setting::SOUND_ENABLED, Setting::SOUND_ENABLED  + "=" + StringTable::get(SettingTextKeys::SETTING_SOUND_ENABLED) + ": " + StringTable::get(TextMessages::get_bool_sid(settings.get_setting_as_bool(Setting::SOUND_ENABLED)))},
                                                  { Setting::SOUND_EFFECTS_ENABLED, Setting::SOUND_EFFECTS_ENABLED + "=" + StringTable::get(SettingTextKeys::SETTING_SOUND_EFFECTS_ENABLED) + ": " + StringTable::get(TextMessages::get_bool_sid(settings.get_setting_as_bool(Setting::SOUND_EFFECTS_ENABLED))) } };

  return sound_settings;
}

ActionCostValue SoundSettingsAction::get_action_cost_value(CreaturePtr c) const
{
  return ActionCostConstants::NO_ACTION;
}
