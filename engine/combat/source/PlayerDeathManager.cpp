#include "Game.hpp"
#include "MessageManager.hpp"
#include "PlayerDeathManager.hpp"

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
  Game* game = Game::instance();
  if (game && map && creature)
  {
    MessageManager* manager = MessageManager::instance();
    
    // Display death message with -- more --
    string death_message = TextMessages::get_death_message(creature->get_name());
    manager->add_new_message(death_message);
    manager->send();
    
    // JCD FIXME: need functionality to add -- more --...
    
    // Signal to the game that it is time to quit.
    game->quit();
  }
}
