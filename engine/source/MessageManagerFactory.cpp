#include "Creature.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "MessageManagerFactory.hpp"

// If no creature is passed, always return the real message manager.
IMessageManager& MessageManagerFactory::instance()
{
  return mm_instance();
}

// Select the correct message manager based on whether the creature is
// the player, or at least present within the player's view map.
IMessageManager& MessageManagerFactory::instance(CreaturePtr creature)
{
  Game& game = Game::instance();

  if (creature)
  {
    if (creature->get_is_player() || GameUtils::is_creature_in_player_view_map(game, creature->get_id()))
    {
      return mm_instance();
    }
  }

  return nmm_instance();

}

MessageManager& MessageManagerFactory::mm_instance()
{
  static MessageManager mm;
  return mm;
}

NullMessageManager& MessageManagerFactory::nmm_instance()
{
  static NullMessageManager nmm;
  return nmm;
}

