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

vector<pair<string, string>> SoundSettingsAction::get_settings_to_display(CreaturePtr creature) const
{
  const Settings& settings = Game::instance().get_settings_ref();

  vector<pair<string, string>> sound_settings = { { Setting::SOUND_ENABLED, Setting::SOUND_ENABLED  + "=" + StringTable::get(SettingTextKeys::SETTING_SOUND_ENABLED) + ": " + StringTable::get(TextMessages::get_bool_sid(settings.get_setting_as_bool(Setting::SOUND_ENABLED)))},
                                                  { Setting::SOUND_EFFECTS_ENABLED, Setting::SOUND_EFFECTS_ENABLED + "=" + StringTable::get(SettingTextKeys::SETTING_SOUND_EFFECTS_ENABLED) + ": " + StringTable::get(TextMessages::get_bool_sid(settings.get_setting_as_bool(Setting::SOUND_EFFECTS_ENABLED))) },
                                                  { Setting::MUSIC_ENABLED, Setting::MUSIC_ENABLED + "=" + StringTable::get(SettingTextKeys::SETTING_MUSIC_ENABLED) + ": " + StringTable::get(TextMessages::get_bool_sid(settings.get_setting_as_bool(Setting::MUSIC_ENABLED))) }  };

  return sound_settings;
}

ActionCostValue SoundSettingsAction::get_action_cost_value(CreaturePtr c) const
{
  return ActionCostConstants::NO_ACTION;
}

void SoundSettingsAction::process_setting_if_necessary(CreaturePtr creature, const string& setting_name, const bool new_set_val)
{
  SoundPtr sound = Game::instance().get_sound();

  if (sound != nullptr)
  {
    if (setting_name == Setting::SOUND_ENABLED)
    {
      sound->set_enable_sound(new_set_val);
    }
    else if (setting_name == Setting::SOUND_EFFECTS_ENABLED)
    {
      sound->set_enable_sound_effects(new_set_val);
    }
    else if (setting_name == Setting::MUSIC_ENABLED)
    {
      if (new_set_val)
      {
        MapPtr map = Game::instance().get_current_map();
        sound->play_music(map);
      }
      else
      {
        sound->stop_music();
      }

      sound->set_enable_music(new_set_val);
    }
  }
}