#include "Creature.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "MessageManagerFactory.hpp"

// If no creature is passed, always return the real message manager.
IMessageManager& MessageManagerFactory::instance()
{
  return mm_instance();
}

// If the creature passed is the player, return the message manager;
// otherwise, return the null message manager.
//
// This is the message manager factory function that should be used for
// messages that "only the creature itself cares about" - messages that
// would only be known to it, and have no effect on the outside world.
IMessageManager& MessageManagerFactory::instance(CreaturePtr creature)
{
  if (creature && creature->get_is_player())
  {
    return mm_instance();
  }
  else
  {
    return nmm_instance();
  }
}

// Select the correct message manager based on whether the creature is
// the player, or at least present within the player's view map.
IMessageManager& MessageManagerFactory::instance(CreaturePtr creature, bool player_is_affected)
{
  Game& game = Game::instance();

  if (player_is_affected)
  {
    return mm_instance();
  }

  if (creature)
  {
    if (creature->get_is_player() || GameUtils::is_creature_in_player_view_map(game, creature->get_id()) || GameUtils::is_creature_adjacent(game, creature, game.get_current_player()))
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

