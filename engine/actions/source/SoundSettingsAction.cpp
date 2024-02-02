#include "SoundSettingsAction.hpp"
#include "DisplayItemTypeFactory.hpp"
#include "Game.hpp"
#include "ScreenTitleTextKeys.hpp"
#include "SettingTextKeys.hpp"
#include "Setting.hpp"
#include "TextMessages.hpp"

using namespace std;

ActionCostValue SoundSettingsAction::sound_actions(CreaturePtr creature)
{
  show_settings(creature, ScreenTitleTextKeys::SCREEN_TITLE_SOUND_ACTIONS);

  return get_action_cost_value(nullptr);
}

vector<pair<string, string>> SoundSettingsAction::get_settings_to_display() const
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
