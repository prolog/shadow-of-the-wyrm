#pragma once
#include "MessageManager.hpp"
#include "NullMessageManager.hpp"

class Creature;

// MessageManagerFactory returns the correct instance of the
// MessageManager.  If the creature is the player, this is the real 
// message manager, which outputs the messages on screen, etc.  If the
// creature is not the player, then the message manager is selected based
// on whether the creature is within the player's view map.  If it is,
// then the real message manager is selected.  Otherwise, the null
// message manager is selected.  This ensures that creatures across the
// map don't have their messages broadcast.
class MessageManagerFactory
{
  public:
    static IMessageManager& instance();

    // The player is affected if the calling function says so, or if a valid
    // CreaturePtr is provided and that creature is in the player's LOS.
    static IMessageManager& instance(std::shared_ptr<Creature> creature, bool player_is_affected);

  protected:
    static MessageManager& mm_instance();
    static NullMessageManager& nmm_instance();
};

