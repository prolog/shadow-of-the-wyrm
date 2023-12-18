#include "SoundActionsAction.hpp"
#include "DisplayItemTypeFactory.hpp"
#include "Game.hpp"
#include "OptionScreen.hpp"
#include "ScreenTitleTextKeys.hpp"
#include "SettingTextKeys.hpp"
#include "Setting.hpp"
#include "TextMessages.hpp"

using namespace std;

ActionCostValue SoundActionsAction::sound_actions(CreaturePtr creature) const
{
  Game& game = Game::instance();
  Settings& set = game.get_settings_ref();
  auto do_aa = true;

  vector<string> options;
  OptionScreen os(game.get_display(), ScreenTitleTextKeys::SCREEN_TITLE_SOUND_ACTIONS, {}, options);
  os.display();

  return get_action_cost_value(nullptr);
}

ActionCostValue SoundActionsAction::get_action_cost_value(CreaturePtr c) const
{
  return ActionCostConstants::NO_ACTION;
}
