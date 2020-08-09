#include "CombatTextKeys.hpp"
#include "CreatureUtils.hpp"
#include "Game.hpp"
#include "MessageManagerFactory.hpp"
#include "PlayerDeathManager.hpp"
#include "ReligionManager.hpp"
#include "Setting.hpp"
#include "TextMessages.hpp"

using std::string;

PlayerDeathManager::PlayerDeathManager(CreaturePtr attack, CreaturePtr dead, MapPtr current_map)
: DeathManager(attack, dead, current_map)
{
}

PlayerDeathManager::~PlayerDeathManager()
{
}

void PlayerDeathManager::die() const
{
  Game& game = Game::instance();
  Settings& settings = game.get_settings_ref();
  bool narrative_mode = settings.get_setting_as_bool(Setting::NARRATIVE_MODE);
  IMessageManager& manager = MM::instance();

  if (narrative_mode && dead_creature != nullptr)
  {
    CreatureUtils::remove_negative_statuses_from_creature(dead_creature);
    Statistic hp = dead_creature->get_hit_points();
    Statistic ap = dead_creature->get_arcana_points();

    hp.set_current(hp.get_base());
    ap.set_current(ap.get_base());

    dead_creature->set_hit_points(hp);
    dead_creature->set_arcana_points(ap);

    manager.add_new_message(StringTable::get(CombatTextKeys::COMBAT_REVIVE));
    manager.send();
  }
  else
  {
    if (map && dead_creature)
    {
      ReligionManager rm;

      // Update the screen so that the player can see their final statistics 
      // (otherwise, it will just show the start-of-turn values).
      game.update_display(dead_creature, game.get_current_map(), dead_creature->get_decision_strategy()->get_fov_map(), false);
      game.get_display()->redraw();

      // Display death message with -- more --
      string deity_message_sid = rm.get_death_message_sid(dead_creature->get_religion().get_active_deity_id());
      string death_message = TextMessages::get_death_message(deity_message_sid);
      manager.add_new_message(death_message);

      // Run any death scripts.
      run_death_event(dead_creature, attacking_creature, map);

      manager.send_and_halt();

      // Signal to the game that it is time to quit.
      game.stop_playing(dead_creature, true, true);
    }
  }
}
