#include "Game.hpp"
#include "MessageManager.hpp"
#include "PlayerDeathManager.hpp"
#include "ReligionManager.hpp"
#include "TextMessages.hpp"

using std::string;

PlayerDeathManager::PlayerDeathManager(CreaturePtr attacked_creature, MapPtr current_map)
: DeathManager(attacked_creature, current_map)
{
}

PlayerDeathManager::~PlayerDeathManager()
{
}

void PlayerDeathManager::die()
{
  Game& game = Game::instance();
  if (map && creature)
  {
    ReligionManager rm;
    MessageManager& manager = MessageManager::instance();
    
    // Display death message with -- more --
    string deity_message_sid = rm.get_death_message_sid(creature->get_religion().get_active_deity_id());
    string death_message = TextMessages::get_death_message(deity_message_sid);
    manager.add_new_message(death_message);
    manager.send_and_halt();
    
    // Signal to the game that it is time to quit.
    game.stop_playing();
  }
}
