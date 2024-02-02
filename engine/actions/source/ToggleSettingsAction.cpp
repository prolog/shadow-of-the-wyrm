#include "Game.hpp"
#include "OptionScreen.hpp"
#include "ToggleSettingsAction.hpp"

using namespace std;

void ToggleSettingsAction::show_settings(CreaturePtr creature, const string& screen_title_sid)
{
  Game& game = Game::instance();
  Settings& set = game.get_settings_ref();
  bool do_settings = true;

  while (creature != nullptr && do_settings)
  {
    auto settings = get_settings_to_display();
    vector<string> options;

    for (const auto& s : settings)
    {
      options.push_back(s.second);
    }

    OptionScreen os(game.get_display(), screen_title_sid, {}, options);
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

      process_setting_if_necessary(creature, setting_id, new_set_value);
    }
    else
    {
      do_settings = false;
    }
  }
}

void ToggleSettingsAction::process_setting_if_necessary(CreaturePtr creature, const string& setting_name, const bool new_set_value)
{
}
