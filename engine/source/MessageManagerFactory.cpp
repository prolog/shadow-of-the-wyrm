#include "Creature.hpp"
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
  if (creature && creature->get_is_player())
  {
    return mm_instance();
  }
  else
  {
    return nmm_instance();
  }
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

