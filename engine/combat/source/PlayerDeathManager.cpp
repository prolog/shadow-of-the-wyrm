#include "Game.hpp"
#include "MessageManagerFactory.hpp"
#include "PlayerDeathManager.hpp"
#include "ReligionManager.hpp"
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
  if (map && dead_creature)
  {
    ReligionManager rm;
    IMessageManager& manager = MessageManagerFactory::instance(dead_creature, true /* It IS the player death manager... */);

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
