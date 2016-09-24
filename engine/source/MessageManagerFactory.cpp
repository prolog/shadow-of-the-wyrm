#include "Creature.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "MessageManagerFactory.hpp"

// If no creature is passed, always return the real message manager.
IMessageManager& MessageManagerFactory::instance()
{
  return mm_instance();
}

IMessageManager& MessageManagerFactory::instance(const MessageTransmit mt, CreaturePtr creature, bool player_is_affected)
{
  Game& game = Game::instance();

  if (player_is_affected)
  {
    return mm_instance();
  }

  if (mt == MessageTransmit::MAP)
  {
    return mm_instance();
  }

  if (mt == MessageTransmit::SELF && creature && creature->get_is_player())
  {
    return mm_instance();
  }

  if (player_is_affected || (mt == MessageTransmit::FOV && creature && (creature->get_is_player() || GameUtils::is_creature_in_player_view_map(game, creature->get_id()) || GameUtils::is_creature_adjacent(game, creature, game.get_current_player()))))
  {
    return mm_instance();
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

